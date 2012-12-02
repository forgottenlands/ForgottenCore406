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

#include "ScriptPCH.h"
#include "bastion_of_twilight.h"
#include <cstring>

enum spell 
{
    SPELL_UNRESPONSIVE                            = 86022,
    SPELL_DRAGONS_VEGEANCE                        = 87683,
    SPELL_MALEVOLENT_STRIKE                       = 83908,
    SPELL_MALEVOLENT_STRIKE_TRIG                  = 39171,
    SPELL_STONE_TOUCH                             = 83603,
    SPELL_STONE_GRIP                              = 84593,
    SPELL_FRENZIED_ASSAULT_                       = 83693,
    SPELL_NETHER_BLINDNESS                        = 83611,
    SPELL_FIREBOLT_BARRAGE_SLOW                   = 83733, // 83733 
    SPELL_FIREBOLT_BARRAGE_FAST                   = 83720,
    SPELL_TIME_DILATATION                         = 83601,
    SPELL_SCORCHING_BLAST                         = 83707,
    SPELL_SHADOW_NOVA                             = 83703,
    SPELL_DANCING_FLAMES                          = 84106,
    SPELL_CYCLONE_WINDS                           = 84092,
    SPELL_ENRAGE                                  = 26662,
    SPELL_FURIOUS_ROAR                            = 83710,
};

enum events
{
    EVENT_MALEVOLENT_STRIKE                       = 1,
    EVENT_FRENZIED_ASSOULT                        = 2,
    EVENT_FIREBALL_BARRAGE                        = 3,
    EVENT_ENRAGE                                  = 4,
    EVENT_FURIOUS_ROAR                            = 5,
};

enum sharedActions
{
    ACTION_FIREBALL_BARRAGE_START = 1,
};

class boss_halfus_wyrmbreaker : public CreatureScript
{
	public:
		boss_halfus_wyrmbreaker() : CreatureScript("boss_halfus_wyrmbreaker") {}

		struct boss_halfus_wyrmbreakerAI : public BossAI
		{
			boss_halfus_wyrmbreakerAI(Creature * creature) : BossAI(creature, DATA_WYRMBREAKER)
			{
				instance = me->GetInstanceScript();
			}

            InstanceScript* instance;
            EventMap events;
            uint8 barrageCount;
            bool firstFuriosCasted;
            uint8 roarCount;

			void Reset()
			{
                instance->SetData(DATA_WYRMBREAKER, NOT_STARTED);
                events.Reset();
                me->ClearUnitState(UNIT_STAT_STUNNED);
                barrageCount = 0;
                roarCount = 0;
                firstFuriosCasted = false;
			}

			void EnterCombat(Unit* /*who*/)
			{
                DoZoneInCombat(me);

                instance->SetData(DATA_WYRMBREAKER, IN_PROGRESS);

                // Increased Attack Speed
                me->AddAura(SPELL_FRENZIED_ASSAULT, me);
                
                // Malevolent Strike Aura trigger
                me->AddAura(SPELL_MALEVOLENT_STRIKE_TRIG, me);

                // Firball Barrage activator
                if (Creature* proto = me->FindNearestCreature(NPC_PROTO_BEHEMOTH, 500.0f, true))
                {
                    me->AddAura(SPELL_DANCING_FLAMES, proto);
                    DoZoneInCombat(proto);
                    proto->SetReactState(REACT_PASSIVE);
                    proto->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    proto->Attack(me->getVictim(), true);
                    proto->AttackStop();
                    proto->StopMoving();

                    if (proto->AI())
                        proto->AI()->DoAction(ACTION_FIREBALL_BARRAGE_START);

                    events.ScheduleEvent(EVENT_FIREBALL_BARRAGE, urand(15000, 20000));
                }
                events.ScheduleEvent(EVENT_ENRAGE, 360000);
			}

			void JustDied()
			{
                instance->SetData(DATA_WYRMBREAKER, DONE);
			}

            void DamageTaken(Unit* who, uint32 &damage)
            {
                if (damage > 0)
                {
                    if (me->HealthBelowPct(50) && !firstFuriosCasted)
                    {
                        firstFuriosCasted = true;
                        events.ScheduleEvent(EVENT_FURIOUS_ROAR, 1000);
                    }
                }
            }

			void UpdateAI(const uint32 diff)
			{
				if (!UpdateVictim())
					return;

                events.Update(diff);
                
                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_FIREBALL_BARRAGE:
                            // Cast barrage on random players
                            if (Creature* proto = me->FindNearestCreature(NPC_PROTO_BEHEMOTH, 500.0f, true))
                            {
                                for (uint8 i = 0; i < RAID_MODE(urand(1, !proto->HasAura(SPELL_TIME_DILATATION) ? 4 : 6), urand(3, !proto->HasAura(SPELL_TIME_DILATATION) ? 8 : 16)); ++i)
                                {
                                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true, 0))
                                    {
                                        if (proto->HasAura(SPELL_TIME_DILATATION))
                                            proto->CastSpell(target, SPELL_FIREBOLT_BARRAGE_SLOW, true);
                                        else
                                            proto->CastSpell(target, SPELL_FIREBOLT_BARRAGE_FAST, true);
                                    }
                                }
                                
                                ++barrageCount;
                                if (barrageCount == (proto->HasAura(SPELL_TIME_DILATATION) ? 3 : 8))
                                {
                                    barrageCount = 0;
                                    events.ScheduleEvent(EVENT_FIREBALL_BARRAGE, urand(15000, 20000));
                                } else
                                    events.ScheduleEvent(EVENT_FIREBALL_BARRAGE, !proto->HasAura(SPELL_TIME_DILATATION) ? 2500 : 1000);
                            }
                            break;
                        case EVENT_ENRAGE:
                            me->CastSpell(me, SPELL_ENRAGE, true);
                            break;
                        case EVENT_FURIOUS_ROAR:
                            roarCount++;
                            me->CastSpell(me, SPELL_FURIOUS_ROAR, false);
                            if (roarCount < 3)
                            {
                                events.ScheduleEvent(EVENT_FURIOUS_ROAR, 3000);
                            }
                            else
                            {
                                roarCount = 0;
                                events.ScheduleEvent(EVENT_FURIOUS_ROAR, 30000);
                            }
                            break;
                        default:
                            break;
                    }                
                }

				DoMeleeAttackIfReady();
			}
		};

		CreatureAI* GetAI(Creature* creature) const
        {
			return new boss_halfus_wyrmbreakerAI(creature);
        }
};

class npc_halfus_dragon : public CreatureScript
{
	public:
		npc_halfus_dragon() : CreatureScript("npc_halfus_dragon")
        { }

		struct npc_halfus_dragonAI : public ScriptedAI
        {
			npc_halfus_dragonAI(Creature * creature) : ScriptedAI(creature)
			{
				pInstance = (InstanceScript*)creature->GetInstanceScript();
			}

			InstanceScript* pInstance;

			void Reset()
			{
                me->RemoveAllAuras();
                me->setFaction(35);

                switch (me->GetEntry())
                {
                    case NPC_STORM_RIDER:
                        me->AddAura(SPELL_UNRESPONSIVE, me);
                        return;
                    default:
			            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                        break;
                }
			}

            void JustDied(Unit* killer)
            {
                if (Creature* halfus = me->FindNearestCreature(BOSS_WYRMBREAKER, 500.0f, true))
                    me->AddAura(SPELL_DRAGONS_VEGEANCE, halfus);
            }

			void UpdateAI(const uint32 uiDiff)
			{
				if (me->HasFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE))
				{
					me->SetReactState(REACT_PASSIVE);
				}

				DoMeleeAttackIfReady();
			}
		};

		CreatureAI* GetAI(Creature* creature) const
        {
			return new npc_halfus_dragonAI(creature);
        }

		bool OnGossipHello(Player* player, Creature* creature)
        {
            if (!player || !creature)
                return false;

            if (creature->HasAura(SPELL_UNRESPONSIVE))
                return false;

            player->PlayerTalkClass->ClearMenus();
            player->CLOSE_GOSSIP_MENU();
            
            creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE); 
            creature->setFaction(14);
            creature->Attack(player, true);
            creature->GetMotionMaster()->MoveChase(player, 1.0f, 1.0f);

            if (Creature* halfus = creature->FindNearestCreature(BOSS_WYRMBREAKER, 500.0f, true))
            {
                switch (creature->GetEntry())
                {
                    case NPC_SLATE_DRAKE:
                        creature->AddAura(SPELL_STONE_TOUCH, halfus);
                        break;
                    case NPC_NETHER_SCION:
                        creature->AddAura(SPELL_NETHER_BLINDNESS, halfus);
                        break;
                    case NPC_TIME_WARDEN:
                        if (Creature* proto = creature->FindNearestCreature(NPC_PROTO_BEHEMOTH, 500.0f, true))
                            creature->AddAura(SPELL_TIME_DILATATION, proto);
                        break;
                }

                if (!halfus->isInCombat())
                {
                    halfus->Attack(player, true);
                    halfus->GetMotionMaster()->MoveChase(player, 1.0f, 1.0f);
                }
            }
            creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            // creature->AddAura(SPELL_BIND_WILL, creature);
			return true;
		}

		bool OnGossipSelect(Player* pPlayer, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
        {
            return true;
        }
};

class spell_halfus_stone_touch : public SpellScriptLoader
{
    public:
        spell_halfus_stone_touch() : SpellScriptLoader("spell_halfus_stone_touch") { }

        class spell_halfus_stone_touch_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_halfus_stone_touch_AuraScript);
                            
            void HandleEffectApply(AuraEffect const * /*aurEff*/)
            {
                if (Unit * target = GetTarget())
                {
                    target->AddUnitState(UNIT_STAT_STUNNED);
                    target->ClearUnitState(UNIT_STAT_CASTING);
                    target->AddAura(SPELL_STONE_GRIP, target);
                }
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_halfus_stone_touch_AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_halfus_stone_touch_AuraScript();
        }
};

class spell_halfus_stone_grip : public SpellScriptLoader
{
    public:
        spell_halfus_stone_grip() : SpellScriptLoader("spell_halfus_stone_grip") { }

        class spell_halfus_stone_grip_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_halfus_stone_grip_AuraScript);
                            
            void HandleEffectApply(AuraEffect const * /*aurEff*/)
            {
                if (Unit * target = GetTarget())
                {
                    target->ClearUnitState(UNIT_STAT_STUNNED);
                    target->RemoveAurasDueToSpell(SPELL_STONE_GRIP);
                }
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_halfus_stone_grip_AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_halfus_stone_grip_AuraScript();
        }
};

void AddSC_boss_halfus_wyrmbreaker()
{
	new boss_halfus_wyrmbreaker();
	new npc_halfus_dragon();
    new spell_halfus_stone_touch();
    new spell_halfus_stone_grip();
}