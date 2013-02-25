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
    PHASE_THERALION_FLY                           = 4
};

enum BossActions
{
    ACTION_0                                      = 0,
    ACTION_VALIONA_LAND                           = 1,
    ACTION_VALIONA_FLY                            = 2,
    ACTION_THERALION_LAND                         = 3,
    ACTION_THERALION_FLY                          = 4,
    ACTION_VALIONA_LAND_MOVE                      = 5,
};

enum Points
{
    POINT_THERALION_HOME                          = 50,
    POINT_VALIONA_HOME                            = 51,

    POINT_VALIONA_ABOVE_HOME                      = 52,

    POINT_CENTER_ROOM                             = 53,
    POINT_THERALION_ABOVE_HOME                    = 54,
};

enum valionaEvents
{
    EVENT_NONE                                    = 0,
    EVENT_BLACKOUT,
    EVENT_DEVOURING_FLAMES,
    EVENT_TWILIGHT_SHIFT,
    EVENT_DAZZLING_DESTRUCTION,
    EVENT_THERALION_LAND,
    EVENT_THERALION_TWILIGHT_BLASE,
};

enum theralionEvents
{
    EVENT_0                                       = 0,
    EVENT_ENGULFING_MAGIC,
    EVENT_TWILIGHT_SHIFT_THERALION,
    EVENT_FABULOUS_FLAMES,
    EVENT_VALIONA_LAND,
    EVENT_VALIONA_TWILIGHT_METEORITE,
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
                {
                    me->SetReactState(REACT_PASSIVE);
                    me->AddUnitMovementFlag(MOVEMENTFLAG_LEVITATING);
                }
                else
                {
                    me->SetReactState(REACT_AGGRESSIVE);
                    me->RemoveUnitMovementFlag(MOVEMENTFLAG_LEVITATING);
                }
            }

            void JustSummoned(Creature* summon)
            {
                if (summon->GetEntry() ==  NPC_FABOLOUS_FLAME)
                {
                    summon->CastSpell(summon, SPELL_FABOLOUS_FLAME_VISUAL, true);
                    DoZoneInCombat(summon);
                    summon->SetReactState(REACT_PASSIVE);
                    summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    summon->AttackStop();
                    summon->StopMoving();
                }

                summons.Summon(summon);
            }

            void Reset()
            {
                events.Reset();
                phase = PHASE_NONE;
                summons.DespawnAll();
    
                me->SetHealth(me->GetMaxHealth());
                me->GetMotionMaster()->MovePoint(POINT_THERALION_HOME, me->GetHomePosition());

                if (instance)
                {
                    instance->SetData(DATA_VALIONA_TERALION_HP, me->GetMaxHealth());
                    instance->SetData(DATA_VALIONA_THERALION_EVENT, NOT_STARTED);
                }
            }

            void JustReachedHome()
            {
                SetFlyState(false);
                me->SetOrientation(me->GetHomePosition().GetOrientation());
            }

            void MovementInform(uint32 type, uint32 point)
            {
                if (type != POINT_MOTION_TYPE)
                    return;

                switch (point)
                {
                    case POINT_CENTER_ROOM:
                        // Schedule Events
                        me->Attack(me->getVictim(), true);
                        me->AI()->AttackStart(me->getVictim());
                        SetFlyState(false);
                        me->GetMotionMaster()->MoveChase(me->getVictim(), 1.0f, 1.0f);
                        events.ScheduleEvent(EVENT_ENGULFING_MAGIC, urand(15000, 20000), 0, 0);
                        events.ScheduleEvent(EVENT_TWILIGHT_SHIFT_THERALION, 6000, 0, 0);
                        events.ScheduleEvent(EVENT_FABULOUS_FLAMES, urand(10000, 15000), 0, 0);
                        events.ScheduleEvent(EVENT_VALIONA_LAND, 95000, 0, 0);
                        events.ScheduleEvent(EVENT_VALIONA_TWILIGHT_METEORITE, urand(5000, 8000), 0, 0);
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
                        me->GetMotionMaster()->MovePoint(POINT_CENTER_ROOM, -741.23f, -686.75, 831.88f);
                        break;
                    case ACTION_THERALION_FLY:
                        events.CancelEvent(EVENT_FABULOUS_FLAMES);
                        events.CancelEvent(EVENT_TWILIGHT_SHIFT_THERALION);
                        events.CancelEvent(EVENT_ENGULFING_MAGIC);
                        events.CancelEvent(EVENT_VALIONA_LAND);
                        events.CancelEvent(EVENT_VALIONA_TWILIGHT_METEORITE);

                        phase = PHASE_THERALION_FLY;
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

            void EnterCombat(Unit* victim)
            {
                DoZoneInCombat(me);

                if (Creature* valiona = me->GetCreature(*me, instance->GetData64(DATA_VALIONA)))
                {
                    if (!valiona->isInCombat())
                    {
                        valiona->Attack(victim, false);
                        DoZoneInCombat(valiona);
                        valiona->AttackStop();

                        if (valiona->AI())
                            valiona->AI()->DoAction(ACTION_VALIONA_FLY);
                    }
                }

                instance->SetData(DATA_VALIONA_THERALION_EVENT, IN_PROGRESS);

                events.ScheduleEvent(EVENT_ENGULFING_MAGIC, 35000, 0, 0);
                events.ScheduleEvent(EVENT_TWILIGHT_SHIFT_THERALION, 20000, 0, 0);
                events.ScheduleEvent(EVENT_FABULOUS_FLAMES, urand(10000, 16000), 0, 0);
                events.ScheduleEvent(EVENT_VALIONA_LAND, 95000, 0, 0);
                events.ScheduleEvent(EVENT_VALIONA_TWILIGHT_METEORITE, urand(5000, 8000), 0, 0);
            }

            void JustDied(Unit* killer)
            {
                summons.DespawnAll();

                if (me->GetMap()->GetDifficulty() == RAID_DIFFICULTY_25MAN_NORMAL)
                    killer->SummonGameObject(8000015, -741.23f, -686.75, 831.88f, 1.593f, 0.0f, 0.0f, 0.0f, 0.0f, 100000000);
                else if (me->GetMap()->GetDifficulty() == RAID_DIFFICULTY_25MAN_HEROIC)
                    killer->SummonGameObject(8000018, -741.23f, -686.75, 831.88f, 1.593f, 0.0f, 0.0f, 0.0f, 0.0f, 100000000);
                else if (me->GetMap()->GetDifficulty() == RAID_DIFFICULTY_10MAN_HEROIC)
                    killer->SummonGameObject(8000017, -741.23f, -686.75, 831.88f, 1.593f, 0.0f, 0.0f, 0.0f, 0.0f, 100000000);
                else 
                    killer->SummonGameObject(8000016, -741.23f, -686.75, 831.88f, 1.593f, 0.0f, 0.0f, 0.0f, 0.0f, 100000000);

                me->LowerPlayerDamageReq(me->GetMaxHealth());

                if (instance->GetData(DATA_FIEND_KILLS) >= 6)
                    instance->DoCompleteAchievement(4852);

                if (!me->GetMap()->GetPlayers().isEmpty())
                {
                   for (Map::PlayerList::const_iterator i = me->GetMap()->GetPlayers().begin(); i != me->GetMap()->GetPlayers().end(); ++i)
                   {
                       i->getSource()->ModifyCurrency(396, 105 * PLAYER_CURRENCY_PRECISION);
                   }
                }
                instance->SetData(DATA_VALIONA_THERALION_EVENT, DONE);
            }

            void UpdateAI(const uint32 diff)
            {
                if (instance->GetData(DATA_VALIONA_TERALION_HP) != 0)
                    me->SetHealth(instance->GetData(DATA_VALIONA_TERALION_HP));
                else
                    me->SetHealth(1);

                if (!UpdateVictim() && phase != PHASE_THERALION_FLY)
                    return;

                events.Update(diff);

                while (uint32 eventid = events.ExecuteEvent())
                {
                    switch (eventid)
                    {
                        case EVENT_ENGULFING_MAGIC:
                            for (int8 i = 0; i < RAID_MODE(1, 3, 1, 3); i++)
                            {
                                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                                    me->AddAura(SPELL_ENGULFING_MAGIC, target);
                            }
                            events.ScheduleEvent(EVENT_ENGULFING_MAGIC, 35000, 0, 0);
                            break;
                        case EVENT_TWILIGHT_SHIFT_THERALION:
                            me->CastSpell(me->getVictim(), SPELL_TWILIGHT_SHIFT, true);

                            if (me->getVictim()->HasAura(SPELL_TWILIGHT_SHIFT) && me->getVictim()->GetAura(SPELL_TWILIGHT_SHIFT)->GetStackAmount() >= 5)
                            {
                                me->getVictim()->CastCustomSpell(me->getVictim(), SPELL_SHIFTING_REALITY, NULL, NULL, NULL, true, 0, 0 , me->GetGUID());
                                me->getVictim()->RemoveAura(SPELL_TWILIGHT_SHIFT);
                            }

                            events.ScheduleEvent(EVENT_TWILIGHT_SHIFT_THERALION, urand(20000, 25000), 0, 0);
                            break;
                        case EVENT_FABULOUS_FLAMES:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                                me->CastSpell(target, SPELL_FABOLOUS_FLAMES, true);
                            
                            events.ScheduleEvent(EVENT_FABULOUS_FLAMES, urand(20000, 30000), 0, 0);
                        break; 
                        case EVENT_VALIONA_LAND:
                            events.CancelEvent(EVENT_FABULOUS_FLAMES);
                            events.CancelEvent(EVENT_TWILIGHT_SHIFT_THERALION);
                            events.CancelEvent(EVENT_ENGULFING_MAGIC);
                            events.CancelEvent(EVENT_VALIONA_TWILIGHT_METEORITE);
                            phase = PHASE_THERALION_FLY;
                            SetFlyState(true);
                            me->GetMotionMaster()->MovePoint(POINT_THERALION_ABOVE_HOME, me->GetHomePosition().m_positionX, me->GetHomePosition().m_positionY, me->GetHomePosition().m_positionZ + 20.0f);

                            if (Creature* valiona = me->GetCreature(*me, instance->GetData64(DATA_VALIONA)))
                            {
                                if (valiona->AI())
                                    valiona->AI()->DoAction(ACTION_VALIONA_LAND_MOVE);
                            }
                            break;
                        case EVENT_VALIONA_TWILIGHT_METEORITE:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                            {
                                if (Creature* valiona = me->GetCreature(*me, instance->GetData64(DATA_VALIONA)))
                                {
                                    valiona->AddAura(SPELL_TWILIGHT_METEORITE_TARGET, target);
                                    valiona->CastSpell(target, SPELL_TWILIGHT_METEORITE, false);
                                }
                            }
                            events.ScheduleEvent(EVENT_VALIONA_TWILIGHT_METEORITE, urand(6000, 8000), 0, 0);
                            break;
                    }
                }

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
            uint8 dazzlingCount;

            void SetFlyState(bool fly)
            {
                me->SetFlying(fly);
                if (fly)
                {
                    me->SetReactState(REACT_PASSIVE);
                    me->AddUnitMovementFlag(MOVEMENTFLAG_LEVITATING);
                }
                else
                {
                    me->SetReactState(REACT_AGGRESSIVE);
                    me->RemoveUnitMovementFlag(MOVEMENTFLAG_LEVITATING);
                }
            }

            void MovementInform(uint32 type, uint32 point)
            {
                if (type != POINT_MOTION_TYPE)
                    return;

                switch (point)
                {
                    case POINT_VALIONA_ABOVE_HOME:
                        me->SetOrientation(me->GetHomePosition().GetOrientation());
                        break;
                    case POINT_CENTER_ROOM:                        
                        SetFlyState(false);
                        me->Attack(me->getVictim(), true);
                        me->AI()->AttackStart(me->getVictim());
                        me->AI()->DoAction(ACTION_VALIONA_LAND);
                        me->GetMotionMaster()->MoveChase(me->getVictim(), 1.0f, 1.0f);
                        break;
                }
            }

            void JustReachedHome()
            {
                SetFlyState(false);
                me->SetOrientation(me->GetHomePosition().GetOrientation());
            }

            void Reset()
            {
                events.Reset();
                phase = PHASE_NONE;
                dazzlingCount = 0;
                summons.DespawnAll();

                if (instance)
                {
                    instance->SetData(DATA_VALIONA_TERALION_HP, me->GetMaxHealth());
                    instance->SetData(DATA_VALIONA_THERALION_EVENT, NOT_STARTED);
                }
            }

            void JustDied(Unit* killer)
            {
                me->LowerPlayerDamageReq(me->GetMaxHealth());

                if (instance->GetData(DATA_FIEND_KILLS) >= 6)
                    instance->DoCompleteAchievement(4852);

                instance->SetData(DATA_VALIONA_THERALION_EVENT, DONE);
            }
            
            void DamageTaken(Unit* who, uint32 &damage)
            {
                if (!me || !me->isAlive())
                    return;
                
                if (instance)
                    instance->SetData(DATA_VALIONA_TERALION_HP, me->GetHealth() >= damage ? me->GetHealth() - damage : 0);
            }

            void JustSummoned(Creature* summon)
            {
                if (summon->GetEntry() ==  NPC_THERALION_FLIGHT_TARGET_STALKER)
                {
                    summon->CastSpell(summon, SPELL_DAZZLING_DESTRUCTION_VISUAL, true);
                    DoZoneInCombat(summon);
                    summon->SetReactState(REACT_PASSIVE);
                    summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    summon->AttackStop();
                    summon->StopMoving();
                }

                summons.Summon(summon);
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
                                    spTarget->setFaction(target->getFaction());
                                    spTarget->SetReactState(REACT_AGGRESSIVE);
                                    me->Attack(spTarget, true);
                                    spTarget->Attack(me, true);
                                    me->AddThreat(spTarget, 100000000.0f, SPELL_SCHOOL_MASK_NORMAL);
                                    spTarget->AddThreat(me, 100000000.0f, SPELL_SCHOOL_MASK_NORMAL);
                                    me->SetFacingToObject(spTarget);
                                    me->CastSpell(spTarget, SPELL_DEVOURING_FLAMES, true);
                                }
                            }
                            events.ScheduleEvent(EVENT_DEVOURING_FLAMES, urand(40000, 45000), 0, 0);
                            break;
                        case EVENT_TWILIGHT_SHIFT:
                            if (me->getVictim())
                            {
                                me->CastSpell(me->getVictim(), SPELL_TWILIGHT_SHIFT, true);

                                if (me->getVictim()->HasAura(SPELL_TWILIGHT_SHIFT) && me->getVictim()->GetAura(SPELL_TWILIGHT_SHIFT)->GetStackAmount() >= 5)
                                {
                                    me->getVictim()->CastCustomSpell(me->getVictim(), SPELL_SHIFTING_REALITY, NULL, NULL, NULL, true, 0, 0 , me->GetGUID());
                                    me->getVictim()->RemoveAura(SPELL_TWILIGHT_SHIFT);
                                }
                            }
                            events.ScheduleEvent(EVENT_TWILIGHT_SHIFT, urand(20000, 25000), 0, 0);
                            break;
                        case EVENT_DAZZLING_DESTRUCTION:
                            // Cast 2 flames per time, 6 total
                            for (uint8 i = 0; i < 2; i++)
                            {
                                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true, 0))
                                {
                                    if (Creature* theralion = me->GetCreature(*me, instance->GetData64(DATA_THERALION)))
                                    {
                                        // Summon stalker
                                        if (Creature* stalker = me->SummonCreature(NPC_THERALION_FLIGHT_TARGET_STALKER, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), target->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 12000))
                                            theralion->CastSpell(stalker, SPELL_DAZZLING_DESTRUCTION_MISSILE, true);
                                    }
                                }
                                dazzlingCount++;
                            }
                            if (dazzlingCount < 6)
                                events.ScheduleEvent(EVENT_DAZZLING_DESTRUCTION, 4500, 0, 0);
                            else
                                events.ScheduleEvent(EVENT_THERALION_LAND, 1000, 0, 0);
                            break;
                        case EVENT_THERALION_LAND:
                            events.CancelEvent(EVENT_DAZZLING_DESTRUCTION);
                            events.CancelEvent(EVENT_TWILIGHT_SHIFT);
                            events.CancelEvent(EVENT_DEVOURING_FLAMES);
                            events.CancelEvent(EVENT_BLACKOUT);
                            events.CancelEvent(EVENT_THERALION_TWILIGHT_BLASE);

                            phase = PHASE_VALIONA_FLY;
                            SetFlyState(true);
                            me->GetMotionMaster()->MovePoint(POINT_VALIONA_ABOVE_HOME, me->GetHomePosition().m_positionX, me->GetHomePosition().m_positionY, me->GetHomePosition().m_positionZ + 20.0f);

                            if (Creature* theralion = me->GetCreature(*me, instance->GetData64(DATA_THERALION)))
                            {
                                if (theralion->AI())
                                    theralion->AI()->DoAction(ACTION_THERALION_LAND);
                            }
                            break;
                        case EVENT_THERALION_TWILIGHT_BLASE:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                            {
                                if (Creature* theralion = me->GetCreature(*me, instance->GetData64(DATA_THERALION)))
                                    theralion->CastSpell(target, SPELL_TWILIGHT_BLAST, false);
                            }
                            events.ScheduleEvent(EVENT_THERALION_TWILIGHT_BLASE, urand(3000, 4000), 0, 0);
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
                        dazzlingCount = 0;

                        // Schedule events
                        events.ScheduleEvent(EVENT_BLACKOUT, 45000, 0, 0);
                        events.ScheduleEvent(EVENT_DEVOURING_FLAMES, 40000, 0, 0);
                        events.ScheduleEvent(EVENT_TWILIGHT_SHIFT, 20000, 0, 0);
                        events.ScheduleEvent(EVENT_DAZZLING_DESTRUCTION, 102000, 0, 0);
                        events.ScheduleEvent(EVENT_THERALION_TWILIGHT_BLASE, urand(3000, 4000), 0, 0);
                        break;
                    case ACTION_VALIONA_LAND_MOVE:
                        phase = PHASE_VALIONA_LAND;
                        me->GetMotionMaster()->MovePoint(POINT_CENTER_ROOM, -741.23f, -686.75, 831.88f);
                        break;
                    case ACTION_VALIONA_FLY:
                        events.CancelEvent(EVENT_DAZZLING_DESTRUCTION);
                        events.CancelEvent(EVENT_TWILIGHT_SHIFT);
                        events.CancelEvent(EVENT_DEVOURING_FLAMES);
                        events.CancelEvent(EVENT_BLACKOUT);
                        events.CancelEvent(EVENT_THERALION_TWILIGHT_BLASE);

                        phase = PHASE_VALIONA_FLY;
                        SetFlyState(true);
                        me->GetMotionMaster()->MovePoint(POINT_VALIONA_ABOVE_HOME, me->GetHomePosition().m_positionX, me->GetHomePosition().m_positionY, me->GetHomePosition().m_positionZ + 20.0f);
                        break;
                }
            }

            void EnterCombat(Unit* victim)
            {
                DoZoneInCombat(me);

                if (Creature* theralion = me->GetCreature(*me, instance->GetData64(DATA_THERALION)))
                {
                    if (!theralion->isInCombat())
                    {
                        theralion->Attack(victim, false);
                        DoZoneInCombat(theralion);
                        theralion->AttackStop();

                        if (theralion->AI())
                            theralion->AI()->DoAction(ACTION_THERALION_FLY);
                    }
                }

                instance->SetData(DATA_VALIONA_THERALION_EVENT, IN_PROGRESS);

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

class spell_engulfing_magic : public SpellScriptLoader
{
    public:
        spell_engulfing_magic() : SpellScriptLoader("spell_engulfing_magic") { }
        class spell_engulfing_magic_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_engulfing_magic_SpellScript);
            void onDmg()
            {
                if (!GetHitUnit() || !GetCaster())
                    return;
                
                // Remove caster
                if (GetHitUnit()->GetGUID() == GetCaster()->GetGUID())
                    SetHitDamage(0);
                else
                    SetHitDamage(GetHitDamage() / 2);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_engulfing_magic_SpellScript::onDmg);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_engulfing_magic_SpellScript();
        }
};

class spell_shifting_reality : public SpellScriptLoader
{
    public:
        spell_shifting_reality() : SpellScriptLoader("spell_shifting_reality") { }
        class spell_shifting_reality_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_shifting_reality_SpellScript);
            void onDmg()
            {
                if (!GetHitUnit() || !GetCaster())
                    return;
                
                if (GetHitUnit()->GetGUID() == GetCaster()->GetGUID())
                    return;

                if (!GetHitUnit()->HasAura(74807))
                    GetHitUnit()->AddAura(74807, GetHitUnit());
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_shifting_reality_SpellScript::onDmg);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_shifting_reality_SpellScript();
        }
};


class npc_twilight_portal_bot : public CreatureScript
{
    public:
        npc_twilight_portal_bot() : CreatureScript("npc_twilight_portal_bot") { }

        bool OnGossipHello(Player* pPlayer, Creature* pCreature)
        {
            pPlayer->RemoveAura(74807);
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
        {
            player->PlayerTalkClass->CloseGossip();
            return true;
        }

        struct npc_twilight_portal_botAI : public ScriptedAI
        {
            npc_twilight_portal_botAI(Creature* c) : ScriptedAI(c)
            { }

            InstanceScript* instance;
            uint32 timer;

            void Reset()
            {
                timer = 1000;
            }

            void UpdateAI(const uint32 diff)
            {
                if (timer <= diff)
                {
                    if (!me->HasAura(86291))
                        me->AddAura(86291, me);

                    timer = 1000;
                } else
                    timer -= diff;

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_twilight_portal_botAI(creature);
        }
};

class npc_twilight_fiend : public CreatureScript
{
public:
    npc_twilight_fiend() : CreatureScript("npc_twilight_fiend") { }

    struct npc_twilight_fiendAI : public ScriptedAI
    {
        npc_twilight_fiendAI(Creature* c) : ScriptedAI(c)
        {
            me->SetReactState(REACT_AGGRESSIVE);
            instance = me->GetInstanceScript();
        }

        InstanceScript* instance;

        void JustDied(Unit* killer)
        {
            instance->SetData(DATA_FIEND_KILLS, 1);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_twilight_fiendAI(creature);
    }
};

void AddSC_boss_theralion()
{
    new boss_theralion();
    new boss_valiona();
    new spell_dazzling_destruction();
    new spell_blackout();
    new spell_devouring_flame();
    new spell_engulfing_magic();
    new spell_shifting_reality();
    new npc_twilight_portal_bot();
    new npc_twilight_fiend();
}