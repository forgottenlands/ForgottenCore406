/*
 * Copyright (C) 2005 - 2011 MaNGOS <http://www.getmangos.org/>
 *
 * Copyright (C) 2008 - 2011 TrinityCore <http://www.trinitycore.org/>
 *
 * Copyright (C) 2011 - 2012 ArkCORE <http://www.arkania.net/>
 *
 * Copyright (C) 2012 Forgotten Lands <http://www.forgottenlands.eu/>
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

#include "throne_of_the_four_winds.h"

#define MAX_ENERGY 90
#define RATE_ENERGY 1

/*
############
### Boss Anshal
############ 
*/

enum anshalEvents
{
    EVENT_WINTERING_WINDS = 1,
    EVENT_ANSHAL_REGEN_ENERGY,
};

class boss_anshal: public CreatureScript
{
    public:
        boss_anshal() : CreatureScript("boss_anshal") { }

    struct boss_anshalAI: public BossAI
    {
        boss_anshalAI(Creature* creature) : BossAI(creature, DATA_ANSHAL_EVENT), summons(me) 
        {
            instance = me->GetInstanceScript();
        }

        SummonList summons;
        InstanceScript* instance;
        bool pauseRegen;

        void Reset()
        {
            me->setPowerType(POWER_ENERGY);
            me->SetMaxPower(POWER_ENERGY, MAX_ENERGY);
            me->SetPower(POWER_ENERGY, 0);
            pauseRegen = false;
            events.Reset();
        }   

        void EnterCombat(Unit* who)
        {
            events.ScheduleEvent(EVENT_ANSHAL_REGEN_ENERGY, 1000, 0, 0);
            if (instance)
            {
                instance->SetData(DATA_ANSHAL_EVENT, IN_PROGRESS);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ADD, me);
            }
        }

        void JustDied(Unit* killer)
        {
            summons.DespawnAll();
            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_REMOVE, me);
        }

        void JustSummoned(Creature* summoned)
        {
            summons.Summon(summoned);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STAT_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_WINTERING_WINDS:
                        break;
                    case EVENT_ANSHAL_REGEN_ENERGY:
                        RegenerateEnergy();
                        events.ScheduleEvent(EVENT_ANSHAL_REGEN_ENERGY, 1000, 0, 0);
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void DoAction(int32 const action)
        {
            switch (action)
            {
                case ACTION_ANSHAL_ENTER_IN_COMBAT:
                    if (Player* target = me->FindNearestPlayer(70.0f, true))
                        me->Attack(target, true);
                    break;
            }
        }

        void RegenerateEnergy()
        {
            if (pauseRegen)
                return;

            me->SetPower(POWER_ENERGY, me->GetPower(POWER_ENERGY) + RATE_ENERGY );
        }
     };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_anshalAI(creature);
    }
};

/*
############
### Boss Nezir
############ 
*/

enum nezirEvents
{
    EVENT_CHILLING_WINDS = 1,
    EVENT_ICE_PATCH,
    EVENT_PERMAFROST,
    EVENT_WIND_CHILL,
    EVENT_SLEET_STORM,
    EVENT_CHECK_ENERGY,
    EVENT_RESET_ENERGY,
};

enum nezirSpells
{
    SPELL_ICE_PATCH_VISUAL                        = 86107,
    SPELL_ICE_PATCH_SUMMON                        = 86122,
    SPELL_PERMAFROST                              = 86082, // Target self!
    SPELL_WIND_CHILL                              = 84645,
    SPELL_SLEET_STORM                             = 84644,
};

class boss_nezir: public CreatureScript
{
    public:
        boss_nezir() : CreatureScript("boss_nezir") { }

    struct boss_nezirAI: public BossAI
    {
        boss_nezirAI(Creature* creature) : BossAI(creature, DATA_NEZIR_EVENT), summons(me)
        {
            instance = me->GetInstanceScript();
        }
        
        SummonList summons;
        InstanceScript* instance;

        bool castingSpecial;
        bool pauseRegen;

        uint32 energyRegenTimer;

        void Reset()
        {
            me->setPowerType(POWER_RUNIC_POWER);
            me->SetMaxPower(POWER_RUNIC_POWER, MAX_ENERGY*10); // runic power go ten by ten
            me->SetPower(POWER_RUNIC_POWER, 0);
            pauseRegen = false;
            castingSpecial = false;
            events.Reset();
            energyRegenTimer = 1000;
            summons.DespawnAll();
        }   

        void EnterCombat(Unit* who)
        {
            events.ScheduleEvent(EVENT_CHECK_ENERGY, 500, 0, 0);
            events.ScheduleEvent(EVENT_ICE_PATCH, urand(20000, 25000), 0, 0); // Not sure
            events.ScheduleEvent(EVENT_PERMAFROST, urand(10000, 12000), 0, 0); // Offylike
            events.ScheduleEvent(EVENT_WIND_CHILL, 10000, 0, 0); // Offylike

            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ADD, me);
        }

        void JustDied(Unit* killer)
        {
            summons.DespawnAll();
            if (instance)
            {
                instance->SetData(DATA_NEZIR_EVENT, IN_PROGRESS);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_REMOVE, me);
            }
        }

        void JustSummoned(Creature* summoned)
        {
            summons.Summon(summoned);
            
            switch (summoned->GetEntry())
            {
                case NPC_ICE_PATCH:
                    summoned->CastSpell(summoned, SPELL_ICE_PATCH_VISUAL, true);
                    // summoned->SetReactState(REACT_PASSIVE);
                    break;
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (energyRegenTimer <= diff)
            {
                RegenerateEnergy();
                energyRegenTimer = 1000;
            }
            else
                energyRegenTimer -= diff;            

            events.Update(diff);

            if (me->HasUnitState(UNIT_STAT_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_CHILLING_WINDS:
                        break;
                    case EVENT_ICE_PATCH:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 80.0f, true, 0))
                            me->CastSpell(target, SPELL_ICE_PATCH_SUMMON, true);

                        events.ScheduleEvent(EVENT_ICE_PATCH, urand(20000, 25000), 0, 0);
                        break;
                    case EVENT_PERMAFROST:
                        me->CastSpell(me, SPELL_PERMAFROST, true);
                        events.ScheduleEvent(EVENT_PERMAFROST, urand(10000, 12000), 0, 0);
                        break;
                    case EVENT_WIND_CHILL:
                        me->CastSpell(me, SPELL_WIND_CHILL, true);
                        events.ScheduleEvent(EVENT_WIND_CHILL, 10000, 0, 0);
                        break;
                    case EVENT_CHECK_ENERGY:
                        if (me->GetPower(POWER_RUNIC_POWER) >= MAX_ENERGY * 10 && !castingSpecial)
                        {
                            castingSpecial = true;
                            events.ScheduleEvent(EVENT_SLEET_STORM, 1000, 0, 0);
                        }
                        events.ScheduleEvent(EVENT_CHECK_ENERGY, 500, 0, 0);
                        break;
                    case EVENT_SLEET_STORM:
                        castingSpecial = true;  
                        pauseRegen = true;
                        float homeX, homeY, homeZ, homeO;
                        me->GetHomePosition(homeX, homeY, homeZ, homeO);
                        me->SetPosition(homeX, homeY, homeZ, homeO, true);
                        me->SetPower(POWER_RUNIC_POWER, 0);
                        me->CastSpell(me->getVictim(), SPELL_SLEET_STORM, true);
                        events.ScheduleEvent(EVENT_RESET_ENERGY, 1000, 0, 0);
                        events.DelayEvents(5800);
                        break;
                    case EVENT_RESET_ENERGY:
                        pauseRegen = false;
                        castingSpecial = false;
                        break;

                }
            }

            DoMeleeAttackIfReady();
        }

        void DoAction(int32 const action)
        {
            switch (action)
            {
                case ACTION_NEZIR_ENTER_IN_COMBAT:
                    if (Player* target = me->FindNearestPlayer(70.0f, true))
                        me->Attack(target, true);
                    break;
            }
        }
        
        void RegenerateEnergy()
        {
            if (pauseRegen)
                return;

            me->SetPower(POWER_RUNIC_POWER, me->GetPower(POWER_RUNIC_POWER) + RATE_ENERGY*10 );
        }
     };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_nezirAI(creature);
    }
};

/*
############
### Boss Rohash
############ 
*/

enum rohashEvents
{
    EVENT_DEAFENING_WINDS = 1,
    EVENT_ROHASH_REGEN_ENERGY,
};


class boss_rohash: public CreatureScript
{
    public:
        boss_rohash() : CreatureScript("boss_rohash") { }

    struct boss_rohashAI: public BossAI
    {
        boss_rohashAI(Creature* creature) : BossAI(creature, DATA_ROHASH_EVENT), summons(me)       {
            instance = me->GetInstanceScript();
        }
        
        SummonList summons;
        InstanceScript* instance;

        bool pauseRegen;

        void Reset()
        {
            me->setPowerType(POWER_ENERGY);
            me->SetMaxPower(POWER_ENERGY, MAX_ENERGY);
            me->SetPower(POWER_ENERGY, 0);
            pauseRegen = false;
            events.Reset();
        }   

        void EnterCombat(Unit* who)
        {
            events.ScheduleEvent(EVENT_ROHASH_REGEN_ENERGY, 1000, 0, 0);

            if (instance)
            {
                instance->SetData(DATA_ROHASH_EVENT, IN_PROGRESS);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ADD, me);
            }
        }

        void JustDied(Unit* killer)
        {
            summons.DespawnAll();

            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_REMOVE, me);
        }

        void JustSummoned(Creature* summoned)
        {
            summons.Summon(summoned);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STAT_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_DEAFENING_WINDS:
                        break;
                    case EVENT_ROHASH_REGEN_ENERGY:
                        RegenerateEnergy();
                        events.ScheduleEvent(EVENT_ROHASH_REGEN_ENERGY, 1000, 0, 0);
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void DoAction(int32 const action)
        {
            switch (action)
            {
                case ACTION_ROHASH_ENTER_IN_COMBAT:
                    if (Player* target = me->FindNearestPlayer(70.0f, true))
                        me->Attack(target, true);
                    break;
            }
        }

        void RegenerateEnergy()
        {
            if (pauseRegen)
                return;

            me->SetPower(POWER_ENERGY, me->GetPower(POWER_ENERGY) + RATE_ENERGY);
        }
     };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_rohashAI(creature);
    }
};

void AddSC_boss_conclave_of_wind()
{
    new boss_anshal();
    new boss_nezir();
    new boss_rohash();
}