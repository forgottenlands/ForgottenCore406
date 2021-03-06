/*
* Copyright (C) 2005 - 2012 MaNGOS <http://www.getmangos.org/>
*
* Copyright (C) 2008 - 2012 TrinityCore <http://www.trinitycore.org/>
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

#include "ScriptPCH.h"
#include "blackwing_descent.h"

enum Spells
{
    SPELL_MAGMA_SPIT                    = 78068,
    SPELL_LAVA_SPEW                     = 77690,
    SPELL_BERSERK                       = 26662,
    SPELL_MOLTEN_TANTRUM                = 78403,

    SPELL_SWELTERING_ARMOR              = 78199,

    SPELL_MASSIVE_CRASH                 = 91921,

    // Pillar of Flame
    SPELL_PILLAR_OF_FLAME               = 78006,
    SPELL_PARASITE_SPAWN                = 77970, 
    SPELL_LAVA_EFFECT                   = 91918,

    SPELL_PARASITIC_INFECTION           = 78941,

    // Ignition
    SPELL_IGNITION_AURA                 = 92131,
    SPELL_IGNITION_TRIGGER_SPAWN        = 92121,

    // Magmas Head
    SPELL_POINT_OF_VULNERABILITY        = 79011,
    SPELL_RIDE_VEHICLE                  = 78360, 

    SPELL_LAUNCH_HOOK                   = 77917,

    SPELL_CUSTOM_STATE_05               = 45799,
    SPELL_COSMETIC_CHAINS               = 65612,
    SPELL_LAVA_ERRUPT_EMOTE             = 79461,

};

enum Events
{
    EVENT_MAGMA_SPIT = 1,
    EVENT_PILLAR_OF_FLAME,
    EVENT_LAVA_SPEW,
    EVENT_IN_RANGE_CHECK,
    EVENT_MANGLE,
    EVENT_MASSIVE_CRASH,
    EVENT_LEAVE_HEAD_PHASE,
    EVENT_LEAVE_GROUND_PHASE,

    EVENT_BERSERK,
};

enum Actions
{
    ACTION_START_GROUND_PHASE,
};

Position const IgnitionPositions[2][21] =
{
    { // Left Side
        {-355.258f, -66.156f, 215.363f, 3.32963f},
        {-349.104f, -57.5792f, 214.837f, 3.35319f},
        {-355.983f, -79.9935f, 213.749f, 3.91082f},
        {-348.35f, -71.9141f, 213.26f, 3.96973f},
        {-341.228f, -63.2021f, 212.833f, 3.96973f},
        {-335.636f, -53.1296f, 212.332f, 5.80755f},
        {-344.959f, -47.9226f, 212.061f, 6.07851f},
        {-354.565f, -47.2949f, 213.04f, 3.04373f},
        {-350.721f, -88.5883f, 213.92f, 3.97443f},
        {-342.783f, -80.5202f, 213.868f, 3.93124f},
        {-335.879f, -72.941f, 212.87f, 4.06083f},
        {-330.037f, -64.3112f, 212.393f, 4.14329f},
        {-324.021f, -54.4161f, 211.863f, 4.19434f},
        {-317.603f, -44.6127f, 211.952f, 0.96793f},
        {-329.399f, -43.7365f, 211.748f, 6.02982f},
        {-341.139f, -38.8838f, 211.426f, 6.12014f},
        {-350.813f, -26.2997f, 211.345f, 2.15388f},
        {-352.253f, -37.0172f, 211.603f, 2.95734f},
        {-338.237f, -27.1878f, 211.154f, 3.06337f},
        {-327.528f, -32.3648f, 211.394f, 3.06337f},
        {-316.344f, -33.1654f, 211.428f, 3.17725f},
    },
    {  // Right Side
        {-313.627f, -72.6881f, 213.266f, 1.00637f},
        {-319.881f, -82.0775f, 213.552f, 4.27756f},
        {-306.833f, -83.4444f, 213.633f, 4.36788f},
        {-302.725f, -74.0836f, 213.345f, 4.69382f},
        {-304.055f, -63.3109f, 212.826f, 4.57601f},
        {-300.848f, -54.0836f, 212.39f, 4.18332f},
        {-308.972f, -52.744f, 212.326f, 5.62846f},
        {-315.607f, -58.0178f, 212.578f, 1.02995f},
        {-320.357f, -65.927f, 212.802f, 1.0378f},
        {-326.56f, -74.2884f, 213.145f, 0.841454f},
        {-333.371f, -83.2f, 213.706f, 0.566564f},
        {-343.042f, -91.8511f, 213.916f, 3.12304f},
        {-334.444f, -92.7097f, 213.903f, 3.06413f},
        {-324.424f, -93.0766f, 213.909f, 2.98166f},
        {-315.574f, -93.3725f, 213.924f, 3.12696f},
        {-304.845f, -93.5295f, 213.919f, 3.10733f},
        {-296.142f, -88.6009f, 214.03f, 4.72919f},
        {-292.752f, -78.8147f, 213.567f, 4.71348f},
        {-295.368f, -68.4218f, 213.065f, 4.71741f},
        {-293.046f, -56.9843f, 212.531f, 4.62709f},
        {-295.83f, -46.4565f, 212.04f, 1.27344f},
    }
};

Position const HeroicPositions[1] =
{
    {-302.969055f, -7.754232f, 245.336243f, 4.261655f}, // Nefarians Position
};

class boss_magmaw : public CreatureScript
{
public:
    boss_magmaw() : CreatureScript("boss_magmaw") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_magmawAI (creature);
    }

    struct boss_magmawAI : public BossAI
    {
        boss_magmawAI(Creature* creature) : BossAI(creature, DATA_MAGMAW)
        {
            instance = creature->GetInstanceScript();
            creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
        }

        InstanceScript* instance;
        EventMap events;
        bool isInManglePhase;
        uint32 emoteTimer;

        void Reset()
        {
            events.Reset();
            isInManglePhase = false;
            DespawnMinions();
            emoteTimer = 20000;

            me->SetReactState(REACT_PASSIVE);

            if(Creature* head = ObjectAccessor::GetCreature(*me, instance->GetData64(NPC_MAGMAWS_HEAD)))
            {
                if(head->isDead())
                    head->Respawn();

                if(!me->GetVehicleKit()->GetPassenger(0))
                    head->EnterVehicle(me, 0);

                head->GetVehicleKit()->RemoveAllPassengers();
            }

			instance->SetData(DATA_MAGMAW, NOT_STARTED);
            _Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
			DoZoneInCombat();
            if(Creature* head = ObjectAccessor::GetCreature(*me, instance->GetData64(NPC_MAGMAWS_HEAD)))
                head->AI()->DoZoneInCombat(head);

            events.ScheduleEvent(EVENT_MAGMA_SPIT, urand(11000,13000));
            events.ScheduleEvent(EVENT_LAVA_SPEW, urand(7000,9000));
            events.ScheduleEvent(EVENT_PILLAR_OF_FLAME, 30000);

            events.ScheduleEvent(EVENT_IN_RANGE_CHECK, 5000);
            events.ScheduleEvent(EVENT_MANGLE, 45000);
            events.ScheduleEvent(EVENT_BERSERK, 600000); // 10 Min

            if(me->GetMap()->IsHeroic())
            {
                if (Creature* nefarian = me->SummonCreature(NPC_NEFARIAN_HELPER_HEROIC, HeroicPositions[0], TEMPSUMMON_MANUAL_DESPAWN))
                    nefarian->AI()->DoZoneInCombat();
            }
			instance->SetData(DATA_MAGMAW, IN_PROGRESS);
            _EnterCombat();
        }

        void UpdateAI(const uint32 diff)
        {
            if(!me->isInCombat())
            {
                if (emoteTimer <= diff) 
                {
                    DoCast(me, SPELL_LAVA_ERRUPT_EMOTE, true);

                    emoteTimer = 30000;
                } else
                    emoteTimer -= diff;
            }

            if (!UpdateVictim())
                return;

            events.Update(diff);
            _DoAggroPulse(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_MAGMA_SPIT:
                        // Maybe we have to cast the spell on all Players
                        if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 200.0f, true))
                            DoCast(target, SPELL_MAGMA_SPIT);

                        events.ScheduleEvent(EVENT_MAGMA_SPIT, urand(15000,17000));
                        break;
                    case EVENT_LAVA_SPEW:
                        if (!me->IsWithinMeleeRange(me->getVictim()))
                            DoCastAOE(SPELL_LAVA_SPEW);

                        events.ScheduleEvent(EVENT_LAVA_SPEW, urand(7000,9000));
                        break;
                    case EVENT_IN_RANGE_CHECK:
                        if (me->getVictim())
                            if (me->GetDistance(me->getVictim()) > 10.0f)
                                DoCast(me, SPELL_MOLTEN_TANTRUM);

                        events.ScheduleEvent(EVENT_IN_RANGE_CHECK, 5000);
                        break;
                    case EVENT_PILLAR_OF_FLAME:
                        if(Unit* target = SelectTarget(SELECT_TARGET_FARTHEST, 0, 500.0f, true))
                            me->SummonCreature(NPC_PILLAR_OF_FLAME_TRIGGER, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN);		

                        events.ScheduleEvent(EVENT_PILLAR_OF_FLAME, 30000);
                        break;
                    case EVENT_BERSERK:
                        DoCast(me, SPELL_BERSERK);
                        break;
                    case EVENT_MANGLE:
                        me->AddAura(SPELL_SWELTERING_ARMOR, me->getVictim());

                        events.ScheduleEvent(EVENT_MASSIVE_CRASH, 12000);
                        events.ScheduleEvent(EVENT_MANGLE, 90000);
                        break;
                    case EVENT_MASSIVE_CRASH:
                        me->AttackStop();
                        me->SetReactState(REACT_PASSIVE);
                        DoCastAOE(SPELL_MASSIVE_CRASH);
                        me->AddAura(SPELL_CUSTOM_STATE_05, me);

                        me->CastSpell(me, SPELL_POINT_OF_VULNERABILITY, true);

                        events.CancelEvent(EVENT_MAGMA_SPIT);
                        events.CancelEvent(EVENT_LAVA_SPEW);
                        events.CancelEvent(EVENT_IN_RANGE_CHECK);
                        events.CancelEvent(EVENT_PILLAR_OF_FLAME);

                        events.ScheduleEvent(EVENT_LEAVE_GROUND_PHASE, 20000);
                        break;
                    case EVENT_LEAVE_GROUND_PHASE:
                        me->SetReactState(REACT_AGGRESSIVE);
                        me->RemoveAura(SPELL_CUSTOM_STATE_05);
                        me->RemoveAura(SPELL_POINT_OF_VULNERABILITY);

                        events.ScheduleEvent(EVENT_MAGMA_SPIT, urand(11000, 13000));
                        events.ScheduleEvent(EVENT_LAVA_SPEW, urand(7000, 9000));
                        events.ScheduleEvent(EVENT_PILLAR_OF_FLAME, 30000);

                        events.ScheduleEvent(EVENT_IN_RANGE_CHECK, 5000);
                        break;
                }
            }

            if(!me->HasAura(SPELL_CUSTOM_STATE_05))
                DoMeleeAttackIfReady();
        }

        void JustSummoned(Creature *summon)
        {
            if(summon->GetEntry() == NPC_IGNITION_TRIGGER)
            {
                summon->SetReactState(REACT_PASSIVE);
                summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
            }
            else if (summon->GetEntry() != NPC_PILLAR_OF_FLAME_TRIGGER)
            {
                summon->setActive(true);
                summon->AI()->DoZoneInCombat(summon);
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            if(Creature* head = ObjectAccessor::GetCreature(*me, instance->GetData64(NPC_MAGMAWS_HEAD)))
                head->DisappearAndDie();

            DespawnMinions();
			instance->SetData(DATA_MAGMAW, DONE);
            _JustDied();
        }

        void DamageTaken(Unit* who, uint32& damage)
        {
            if(me->HasReactState(REACT_PASSIVE))
                me->SetReactState(REACT_AGGRESSIVE);
        }

        private:
            inline void CastIgnition()
            {
                uint8 side = urand(0,1);

                for(uint8 i=0; i<21 ; i++)
                    me->CastSpell(IgnitionPositions[side][i].GetPositionX(),IgnitionPositions[side][i].GetPositionY(),IgnitionPositions[side][i].GetPositionZ(),SPELL_IGNITION_TRIGGER_SPAWN,true);
            }

            inline void DespawnMinions()
            {
                DespawnCreatures(NPC_IGNITION_TRIGGER);
                DespawnCreatures(NPC_LAVA_PARASITE);

                DespawnCreatures(NPC_NEFARIAN_HELPER_HEROIC);
                DespawnCreatures(NPC_BLAZING_BONE_CONSTRUCT);
                DespawnCreatures(NPC_PILLAR_OF_FLAME_TRIGGER);
            }

            void DespawnCreatures(uint32 entry)
            {
                std::list<Creature*> creatures;
                GetCreatureListWithEntryInGrid(creatures, me, entry, 1000.0f);

                if (creatures.empty())
                    return;

                for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                    (*iter)->DespawnOrUnsummon();
            }
    };
};

class mob_magmaws_head : public CreatureScript
{
public:
    mob_magmaws_head() : CreatureScript("mob_magmaws_head") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_magmaws_headAI (creature);
    }

    struct mob_magmaws_headAI : public ScriptedAI
    {
        mob_magmaws_headAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            creature->SetReactState(REACT_PASSIVE);
        }

        InstanceScript* instance;

        void Reset()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
        }

        void DamageTaken(Unit* /*who*/, uint32& damage)
        {
        }
    };
};

class mob_pillar_of_flame_trigger : public CreatureScript
{
public:
    mob_pillar_of_flame_trigger() : CreatureScript("mob_pillar_of_flame_trigger") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_pillar_of_flame_triggerAI (creature);
    }

    struct mob_pillar_of_flame_triggerAI : public ScriptedAI
    {
        mob_pillar_of_flame_triggerAI(Creature* creature) : ScriptedAI(creature),Intialized(false) { }

        uint32 uiErruptTime;
        uint32 uiSpawnTime;
        bool Intialized;

        void Reset()
        {
            uiErruptTime = 8000;
            uiSpawnTime = 3000;
            Intialized = false;
        }

        void IsSummonedBy(Unit* summoner)
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NOT_SELECTABLE);
            me->SetSpeed(MOVE_WALK, 0.0f, true);
            me->SetSpeed(MOVE_RUN, 0.0f, true);

            DoCastAOE(SPELL_PILLAR_OF_FLAME, true); // This is only for DBM warnings etc...

            uiErruptTime = 8000;
            uiSpawnTime = 3000;
            Intialized = true;
        }

        void UpdateAI(const uint32 diff)
        {
            if(!Intialized)
                return;

            if (uiErruptTime <= diff)
            {
                me->DespawnOrUnsummon();

            } else uiErruptTime -= diff;

            if (uiSpawnTime <= diff)
            {
                DoCastAOE(SPELL_PARASITE_SPAWN, true);
                uiSpawnTime = 5000000;
            } else
                uiSpawnTime -= diff;
        }

        void JustSummoned(Creature *summon)
        {
            summon->setActive(true);
            summon->AI()->DoZoneInCombat(summon);
            summon->SetSpeed(MOVE_WALK, 0.8f, true);
            summon->SetSpeed(MOVE_RUN, 0.8f, true);
        }
    };
};

class spell_parasitic_infection : public SpellScriptLoader
{
public:
    spell_parasitic_infection() : SpellScriptLoader("spell_parasitic_infection") { }

    class spell_parasitic_infection_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_parasitic_infection_AuraScript);

        void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if(Unit * caster = GetCaster())
                caster->CastSpell(caster, 77973, true);
        }

        void Register()
        {
            OnEffectRemove += AuraEffectRemoveFn(spell_parasitic_infection_AuraScript::OnRemove, EFFECT_2, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_DEFAULT);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_parasitic_infection_AuraScript();
    }
};

void AddSC_boss_magmaw()
{
    new boss_magmaw();
    new mob_magmaws_head();
    new mob_pillar_of_flame_trigger();
    new spell_parasitic_infection();
}