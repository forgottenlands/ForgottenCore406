/*
 * Copyright (C) 2005 - 2011 MaNGOS <http://www.getmangos.org/>
 *
 * Copyright (C) 2008 - 2011 TrinityCore <http://www.trinitycore.org/>
 *
 * Copyright (C) 2011 - 2012 ArkCORE <http://www.arkania.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

 /*
 Made By: Jenova
 Project: Atlantiss Core
 SDName: boss_rajh
 SD%Complete: 75%
 SDComment:
 SDCategory: Halls Of Origination

 Known Bugs:

 TODO:
 1. Needs Testing
 2. Missing ScriptTexts
 3. Check Timers
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptPCH.h"
#include "halls_of_origination.h"

enum Spells
{
    //Rajh
    SPELL_SUN_STRIKE           = 73872,
    SPELL_INFERNO_LEAP         = 87647, //Value: 32375 to 37625
    SPELL_INFERNO_LEAP_2       = 89876, //Value: 120250 to 139750
    SPELL_SUMMON_SUN_ORB       = 80352,
    SPELL_BLESSING_OF_THE_SUN  = 76352,
    SPELL_SUMMON_SOLAR_WIND    = 89127,

    //Solar Wind
    SPELL_SOLAR_WIND           = 89130,
    SPELL_SOLAR_FIRE           = 89131
};

enum Texts
{
    SAY_AGGRO    = 0,
    SAY_KILL     = 1,
    SAY_DEATH    = 2,
    SAY_ENERGIZE = 3
};

enum Events
{
    EVENT_SUN_STRIKE           = 1,
    EVENT_INFERNO_LEAP         = 2,
    EVENT_BLESSING_OF_THE_SUN  = 3,
    EVENT_SUMMON_SUN_ORB       = 4,
    EVENT_SUMMON_SOLAR_WIND    = 5
};

class boss_rajh : public CreatureScript
{
    public:
        boss_rajh() : CreatureScript("boss_rajh") { }

        struct boss_rajhAI : public BossAI
        {
            boss_rajhAI(Creature* creature) : BossAI(creature, DATA_RAJH_EVENT), Summons(me)
            {
                instance = me->GetInstanceScript();
            }

            InstanceScript* instance;
            SummonList Summons;

            void Reset()
            {
                if (instance)
                    instance->SetData(DATA_RAJH_EVENT, NOT_STARTED);

                me->setPowerType(POWER_ENERGY);
                me->SetPower(POWER_ENERGY, me->GetMaxPower(POWER_ENERGY));
                Summons.DespawnAll();
            }

            void EnterCombat(Unit* /*who*/)
            {
                //DoScriptText(SAY_AGGRO, me);

                if (instance)
                    instance->SetData(DATA_RAJH_EVENT, IN_PROGRESS);

                me->SetPower(POWER_ENERGY, me->GetMaxPower(POWER_ENERGY));

                events.ScheduleEvent(EVENT_SUN_STRIKE, urand(8000, 10000));
                // events.ScheduleEvent(EVENT_INFERNO_LEAP, 15000);
                events.ScheduleEvent(EVENT_BLESSING_OF_THE_SUN, 1000);
                events.ScheduleEvent(EVENT_SUMMON_SUN_ORB, 25000);
                events.ScheduleEvent(EVENT_SUMMON_SOLAR_WIND, 20000);

                DoZoneInCombat();
            }

            void JustSummoned(Creature* summon)
            {
                if (summon->GetEntry() == 39635)
                {
                    summon->AddAura(74109, summon);
                    summon->AddAura(74107, summon);
                    summon->SetSpeed(MOVE_WALK, 0.5f, true);
                    summon->SetSpeed(MOVE_RUN, 0.5f, true);
                    summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    me->GetMotionMaster()->MoveRandom(20.0f);
                }

                Summons.Summon(summon);
            }

            void EnergizeSun()
            {
                DoCastAOE(SPELL_BLESSING_OF_THE_SUN);
            }

            void UpdateAI(uint32 const diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STAT_CASTING))
                    return;
                
                if (me->HasAura(SPELL_BLESSING_OF_THE_SUN))
                    return;
    
                events.Update(diff);

                while(uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_SUN_STRIKE:
                            DoCast(me->getVictim(), SPELL_SUN_STRIKE);
                            events.ScheduleEvent(EVENT_SUN_STRIKE, urand(8000, 10000));
                            break;
                        case EVENT_INFERNO_LEAP:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, true))
                                DoCast(target, SPELL_INFERNO_LEAP);
                            events.ScheduleEvent(EVENT_INFERNO_LEAP, urand(15000, 22000));
                            break;
                        case EVENT_BLESSING_OF_THE_SUN:
                            if (me->GetPower(POWER_ENERGY) == 0)
                                EnergizeSun();
                            events.ScheduleEvent(EVENT_BLESSING_OF_THE_SUN, 1000);
                            break;
                        case EVENT_SUMMON_SUN_ORB:
                            DoCast(SPELL_SUMMON_SUN_ORB);
                            events.ScheduleEvent(EVENT_SUMMON_SUN_ORB, 25000);
                            break;
                        case EVENT_SUMMON_SOLAR_WIND:
                            DoCast(SPELL_SUMMON_SOLAR_WIND);
                            events.ScheduleEvent(EVENT_SUMMON_SOLAR_WIND, 30000);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }

            void JustDied(Unit* /*who*/)
            {
                //DoScriptText(SAY_DEATH, me);

                if (instance)
                    instance->SetData(DATA_RAJH_EVENT, DONE);

                Summons.DespawnAll();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_rajhAI(creature);
        }
};

class mob_solar_wind : public CreatureScript
{
public:
    mob_solar_wind() : CreatureScript("mob_solar_wind") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_solar_windAI(creature);
    }

    struct mob_solar_windAI : public ScriptedAI
    {
        mob_solar_windAI(Creature* creature) : ScriptedAI(creature)
        {
            m_pInstance = (InstanceScript*)creature->GetInstanceScript();
            Reset();
        }

        InstanceScript* m_pInstance;

        void EnterCombat(Unit* /*who*/)
        {
            me->StopMoving();
            me->AttackStop();
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
            DoCast(me, SPELL_SOLAR_FIRE);
        }

        void JustDied(Unit* /*killer*/)
        {
            // used to despawn corpse immediately
            me->DespawnOrUnsummon();

            std::list<Creature*> pCreatureList;
            Trinity::AllCreaturesOfEntryInRange checker(me, 47922, 100.0f);
            Trinity::CreatureListSearcher<Trinity::AllCreaturesOfEntryInRange> searcher(me, pCreatureList, checker);
            me->VisitNearbyObject(100.0f, searcher);
            if(pCreatureList.empty())
                return;

            std::list<Creature*>::iterator itr = pCreatureList.begin();
            uint32 count = pCreatureList.size();
            for(std::list<Creature*>::iterator iter = pCreatureList.begin(); iter != pCreatureList.end(); ++iter)
            {
                (*iter)->ForcedDespawn();
            }
        }
    };
};

class mob_solar_wind_v : public CreatureScript
{
public:
    mob_solar_wind_v() : CreatureScript("mob_solar_wind_v") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_solar_wind_vAI(creature);
    }

    struct mob_solar_wind_vAI : public ScriptedAI
    {
        mob_solar_wind_vAI(Creature* creature) : ScriptedAI(creature), Summons(me)
        {}

        SummonList Summons;

        void EnterCombat(Unit* /*who*/)
        {
            me->GetMotionMaster()->MoveRandom(20.0f);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }

        void JustSummoned(Creature* summon)
        {
            Summons.Summon(summon);
        }

        void Reset()
        {
            me->GetMotionMaster()->MoveRandom(20.0f);
            me->AddAura(74109, me);
            me->AddAura(74107, me);
            me->SetSpeed(MOVE_WALK, 0.5f, true);
            me->SetSpeed(MOVE_RUN, 0.5f, true);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }

        void JustDied(Unit* /*killer*/)
        {
            // used to despawn corpse immediately
            me->DespawnOrUnsummon();
            Summons.DespawnAll();

            if (me->GetMap()->IsHeroic())
           {
               if (!me->GetMap()->GetPlayers().isEmpty())
               {
                   for (Map::PlayerList::const_iterator i = me->GetMap()->GetPlayers().begin(); i != me->GetMap()->GetPlayers().end(); ++i)
                   {
                       i->getSource()->KilledMonsterCredit(39378, 0);
                   }
               }
           }
        }
    };
};

void AddSC_boss_rajh()
{
    new boss_rajh;
    new mob_solar_wind;
    new mob_solar_wind_v;
}