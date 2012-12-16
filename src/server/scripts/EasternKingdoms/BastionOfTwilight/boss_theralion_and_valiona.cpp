/*
 * Copyright (C) 2012 - 2013 ForgottenLands <http://www.forgottenlands.eu/>
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

#include "bastion_of_twilight.h"
#include "SpellScript.h"
#include "SpellAuras.h"
#include "SpellAuraEffects.h"
#include "ScriptPCH.h"

#define MAX_DAZZLIN_DESTRUCTION 6

enum BossPhases
{
    PHASE_NONE                                    = 0,
    PHASE_VALIONA_LAND                            = 1,
    PHASE_VALIONA_FLY                             = 2,
    PHASE_TERALION_LAND                           = 3,
    PHASE_TERALION_FLY                            = 4
};

enum BossActions
{
    ACTION_0                                      = 0,
    ACTION_VALIONA_LAND                           = 1,
    ACTION_VALIONA_FLY                            = 2,
    ACTION_THERALION_LAND                         = 3,
    ACTION_THERALION_FLY                          = 4
};

enum Points
{
    POINT_THERALION_HOME                          = 50,
    POINT_VALIONA_HOME                            = 51,
};

enum valionaEvents
{
    EVENT_NONE                                    = 0,
    EVENT_BLACKOUT,
    EVENT_DEVOURING_FLAMES,
    EVENT_TWILIGHT_SHIFT,
};

enum theralionEvents
{
    EVENT_0                                       = 0,
};

class boss_theralion : public CreatureScript
{
    public:
        boss_theralion() : CreatureScript("boss_theralion") {}

        struct boss_theralionAI : public BossAI
        {
            boss_theralionAI(Creature * creature) : BossAI(creature, DATA_THERALION), summons(me)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            SummonList summons;
            uint32 phase;

            void SetFlyState(bool fly)
            {
                me->SetFlying(fly);
                if (fly)
                    me->AddUnitMovementFlag(MOVEMENTFLAG_LEVITATING);
                else
                    me->RemoveUnitMovementFlag(MOVEMENTFLAG_LEVITATING);
            }

            void Reset()
            {
                events.Reset();
                phase = PHASE_NONE;
    
                me->SetHealth(me->GetMaxHealth());
                me->GetMotionMaster()->MovePoint(POINT_THERALION_HOME, me->GetHomePosition());

                if (instance)
                {
                    instance->SetData(DATA_VALIONA_TERALION_HP, me->GetMaxHealth());
                    instance->SetData(DATA_THERALION, NOT_STARTED);
                }
            }

            void JustReachedHome()
            {
                SetFlyState(false);
            }

            void MovementInform(uint32 type, uint32 point)
            {
                if (type != POINT_MOTION_TYPE)
                    return;

                switch (point)
                {
                    case POINT_THERALION_HOME:
                        SetFlyState(false);
                        break;
                }
            }

            void DoAction(const int32 actionId)
            {
                switch (actionId)
                {
                    case ACTION_THERALION_LAND:
                        phase = PHASE_TERALION_LAND;
                        break;
                    case ACTION_THERALION_FLY:
                        phase = PHASE_TERALION_FLY;
                        me->SetReactState(REACT_PASSIVE);
                        SetFlyState(true);
                        me->GetMotionMaster()->MovePoint(0, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() + 20.0f);
                        break;
                }
            }

            void DamageTaken(Unit* who, uint32 &damage)
            {
                if (!me || !me->isAlive())
                    return;
                
                if (instance)
                    instance->SetData(DATA_VALIONA_TERALION_HP, me->GetHealth() >= damage ? me->GetHealth() - damage : 0);
            }

            void UpdateAI(const uint32 diff)
            {
                if (instance->GetData(DATA_VALIONA_TERALION_HP) != 0)
                    me->SetHealth(instance->GetData(DATA_VALIONA_TERALION_HP));
                else
                    me->SetHealth(1);

                if (!UpdateVictim() && phase != PHASE_TERALION_FLY)
                    return;

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_theralionAI(creature);
        }
};

class boss_valiona : public CreatureScript
{
    public:
        boss_valiona() : CreatureScript("boss_valiona") { }

        struct boss_valionaAI : public BossAI
        {
            boss_valionaAI(Creature * creature) : BossAI(creature, DATA_VALIONA), summons(me)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            SummonList summons;
            uint32 phase;

            void Reset()
            {
                events.Reset();
                phase = PHASE_NONE;

                if (instance)
                {
                    instance->SetData(DATA_VALIONA_TERALION_HP, me->GetMaxHealth());
                    instance->SetData(DATA_VALIONA, NOT_STARTED);
                }
            }
            
            void DamageTaken(Unit* who, uint32 &damage)
            {
                if (!me || !me->isAlive())
                    return;
                
                if (instance)
                    instance->SetData(DATA_VALIONA_TERALION_HP, me->GetHealth() >= damage ? me->GetHealth() - damage : 0);
            }

            void UpdateAI(const uint32 diff)
            {
                if (instance->GetData(DATA_VALIONA_TERALION_HP) != 0)
                    me->SetHealth(instance->GetData(DATA_VALIONA_TERALION_HP));
                else
                    me->SetHealth(1);
               
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                while (uint32 eventid = events.ExecuteEvent())
                {
                    switch (eventid)
                    {
                        case EVENT_BLACKOUT:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                                me->CastSpell(target, SPELL_BLACKOUT, true);
                            
                            events.ScheduleEvent(EVENT_BLACKOUT, 45000, 0, 0);
                            break;
                        case EVENT_DEVOURING_FLAMES:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                            {
                                if (Creature* spTarget = me->SummonCreature(46588, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), target->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 8040))
                                {
                                    spTarget->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                                    spTarget->setFaction(target->getFaction());
                                    me->Attack(spTarget, true);
                                    me->AddThreat(spTarget, 100000.0f, SPELL_SCHOOL_MASK_NORMAL);
                                    spTarget->AddThreat(me, 100000.0f, SPELL_SCHOOL_MASK_NORMAL);
                                    spTarget->Attack(me, false);
                                    me->CastSpell(spTarget, SPELL_DEVOURING_FLAMES, true);
                                    me->SetFacingToObject(spTarget);
                                }
                            }
                            events.ScheduleEvent(EVENT_DEVOURING_FLAMES, urand(40000, 45000), 0, 0);
                            break;
                        case EVENT_TWILIGHT_SHIFT:
                            me->CastSpell(me->getVictim(), SPELL_TWILIGHT_SHIFT, true);

                            if (me->getVictim()->HasAura(SPELL_TWILIGHT_SHIFT) && me->getVictim()->GetAura(SPELL_TWILIGHT_SHIFT)->GetStackAmount() >= 5)
                            {
                                me->getVictim()->CastCustomSpell(me->getVictim(), SPELL_SHIFTING_REALITY, NULL, NULL, NULL, true, 0, 0 , me->GetGUID());
                                me->getVictim()->RemoveAura(SPELL_TWILIGHT_SHIFT);
                            }

                            events.ScheduleEvent(EVENT_TWILIGHT_SHIFT, urand(20000, 25000), 0, 0);
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }

            void DoAction(const int32 actionId)
            {
                switch (actionId)
                {
                    case ACTION_VALIONA_LAND:
                        phase = PHASE_VALIONA_LAND;
                        // Schedule events.

                        events.ScheduleEvent(EVENT_BLACKOUT, 45000, 0, 0);
                        events.ScheduleEvent(EVENT_DEVOURING_FLAMES, urand(40000, 55000), 0, 0);
                        events.ScheduleEvent(EVENT_TWILIGHT_SHIFT, urand(20000, 25000), 0, 0);
                        break;
                }
            }

            void EnterCombat(Unit* victim)
            {
                DoZoneInCombat(me);

                if (Creature* theralion = me->GetCreature(*me, instance->GetData64(DATA_THERALION)))
                {
                    theralion->Attack(victim, false);
                    DoZoneInCombat(theralion);
                    theralion->AttackStop();

                    if (theralion->AI())
                        theralion->AI()->DoAction(ACTION_THERALION_FLY);
                }

                me->AI()->DoAction(ACTION_VALIONA_LAND);
            }
        };

        CreatureAI * GetAI(Creature * creature) const
        {
            return new boss_valionaAI(creature);
        }
};

class spell_dazzling_destruction : public SpellScriptLoader
{
    public:
        spell_dazzling_destruction() : SpellScriptLoader("spell_dazzling_destruction") { }

        class spell_dazzling_destructionSpellScript : public SpellScript
        {
            int32 spell_trigger;
            PrepareSpellScript(spell_dazzling_destructionSpellScript);
            bool Validate(SpellEntry const * spellEntry)
            {
                if (!sSpellStore.LookupEntry(spellEntry->Id))
                    return false;
                return true;
            }

            bool Load()
            {
                spell_trigger = GetSpellInfo()->EffectBasePoints[0];
                return true;
            }

            void HandleDummy(SpellEffIndex effIndex)
            {
                GetCaster()->CastSpell(GetTargetUnit(),spell_trigger,false);
            }

            void HandleOnHit()
            {
                std::list<Unit*> players;
                std::list<Unit*>::const_iterator itr;
                GetTargetUnit()->GetRaidMember(players,5.0f);
                for (itr=players.begin();itr!=players.end();++itr)
                {
                    if ((*itr)->GetTypeId() == TYPEID_PLAYER)
                    {
                        GetCaster()->CastSpell((*itr),SPELL_DESTRUCTION_PROCS,false);
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_dazzling_destructionSpellScript::HandleDummy,EFFECT_0,SPELL_EFFECT_DUMMY);
                OnHit += SpellHitFn(spell_dazzling_destructionSpellScript::HandleOnHit);
            }
        };

        SpellScript * GetSpellScript() const
        {
            return new spell_dazzling_destructionSpellScript();
        }
};

class spell_blackout : public SpellScriptLoader {
public:
	spell_blackout() : SpellScriptLoader("spell_blackout") 
    {    }

	class spell_blackout_AuraScript: public AuraScript 
    {
		PrepareAuraScript(spell_blackout_AuraScript);

        void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (!GetCaster() || !GetUnitOwner())
                return;
            
            GetUnitOwner()->CastCustomSpell(GetUnitOwner(), SPELL_BLACKOUT_DMG, NULL, NULL, NULL, true, 0, 0, GetCaster()->GetGUID());
        }

		void Register() 
        {
            OnEffectRemove += AuraEffectRemoveFn(spell_blackout_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_SCHOOL_HEAL_ABSORB, AURA_EFFECT_HANDLE_REAL);
		}
	};

	AuraScript *GetAuraScript() const 
    {
		return new spell_blackout_AuraScript();
	}
};

class spell_devouring_flame : public SpellScriptLoader
{
    public:
        spell_devouring_flame() : SpellScriptLoader("spell_devouring_flame") { }

        class spell_devouring_flame_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_devouring_flame_AuraScript);

            void PeriodicTick(AuraEffect const* aurEff)
            {
                PreventDefaultAction();
                if (GetCaster())
                    GetCaster()->CastSpell(GetCaster(), SPELL_DEVOURING_FLAMES_TRG, true); 
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_devouring_flame_AuraScript::PeriodicTick, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_devouring_flame_AuraScript();
        }
};

void AddSC_boss_theralion()
{
    new boss_theralion();
    new boss_valiona();
    new spell_dazzling_destruction();
    new spell_blackout();
    new spell_devouring_flame();
}