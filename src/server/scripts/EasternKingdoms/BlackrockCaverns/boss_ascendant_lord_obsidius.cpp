/*
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

/**********
* Script Coded by Naios
* Script Complete 97% (or less)
**********/

#include "ScriptPCH.h"
#include "blackrock_caverns.h"

enum Spells
{
	SPELL_THUNDERCLAP = 84622, 
	SPELL_TWILIGHT_CORRUPTION = 93613,
	SPELL_STONE_BLOW = 76185,
};

enum Events
{
	EVENT_THUNDERCLAP = 1,
	EVENT_TWILIGHT_CORRUPTION = 2,
	EVENT_STONE_BLOW = 3,
};

Position const summonPositions[3] =
{
	{349.049f, 569.186f, 66.0078f, 3.11421f},
	{350.668f, 553.744f, 66.0078f, 3.12599f},
	{344.015f, 561.265f, 66.0078f, 3.15348f},
};

class boss_ascendant_lord_obsidius : public CreatureScript
{
public:
	boss_ascendant_lord_obsidius() : CreatureScript("boss_ascendant_lord_obsidius") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new boss_ascendant_lord_obsidiusAI (creature);
	}

	struct boss_ascendant_lord_obsidiusAI : public ScriptedAI
	{
		boss_ascendant_lord_obsidiusAI(Creature* creature) : ScriptedAI(creature)
		{
			instance = creature->GetInstanceScript();

			for(uint8 i = 0; i <= RAID_MODE(1,2); i++)
				ShadowOfObsidiusList[i] = NULL;
		}

		InstanceScript* instance;
		Creature* ShadowOfObsidiusList[3];
		EventMap events;
		uint8 Phase;

		void Reset()
		{
			events.Reset();

			me->GetMotionMaster()->MoveTargetedHome();

			// Spawns his Shadows and Respawns
			for(uint8 i = 0; i <= RAID_MODE(1,2); i++)
			{
				if(ShadowOfObsidiusList[i] == NULL)
				ShadowOfObsidiusList[i] = me->SummonCreature(NPC_SHADOW_OF_OBSIDIUS,summonPositions[i],TEMPSUMMON_MANUAL_DESPAWN);

				if(ShadowOfObsidiusList[i]->isDead())
				{
					ShadowOfObsidiusList[i]->Respawn();
					ShadowOfObsidiusList[i]->GetMotionMaster()->MoveTargetedHome();
				}
			}
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_TWILIGHT_CORRUPTION, 10000);
			events.ScheduleEvent(EVENT_STONE_BLOW, 13000);

			if(me->GetMap()->IsHeroic())
			events.ScheduleEvent(EVENT_THUNDERCLAP, 7000);

			Phase = 0;

			for(uint8 i = 0; i <= RAID_MODE(1,2); i++)
				ShadowOfObsidiusList[i]->Attack(me->getVictim(),false);

			me->MonsterYell("You come seeking answers? Then have them! Look upon your answer to living!", LANG_UNIVERSAL, NULL);
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim() || me->HasUnitState(UNIT_STAT_CASTING))
				return;

			if ((me->HealthBelowPct(69) && Phase == 0) || (me->HealthBelowPct(34) && Phase == 1))
			{
				Phase++;

				// Switch Position with a random Shadow of Obsidius and empty Threat list

				Creature* target = ShadowOfObsidiusList[urand(0,RAID_MODE(1,2))];
				Position telePos;

				me->GetPosition(&telePos);

				// Switch Positions
				me->NearTeleportTo(target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(),0);
				target->NearTeleportTo(telePos.GetPositionX(),telePos.GetPositionY(),telePos.GetPositionZ(),0);

				// Resetts Aggro
				me->getThreatManager().resetAllAggro();

				me->MonsterYell("Your kind has no place in the master's world.", LANG_UNIVERSAL, NULL);

				return;
			}

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_THUNDERCLAP:
					DoCastAOE(SPELL_THUNDERCLAP);
					events.ScheduleEvent(EVENT_THUNDERCLAP, 7000);
					break;

				case EVENT_TWILIGHT_CORRUPTION:
					if(Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 200, true))
					DoCast(pTarget,SPELL_TWILIGHT_CORRUPTION);

					events.ScheduleEvent(EVENT_TWILIGHT_CORRUPTION, 10000);
					break;

				case EVENT_STONE_BLOW:
					DoCastVictim(SPELL_STONE_BLOW);
					events.ScheduleEvent(EVENT_STONE_BLOW, 13000);
					break;

				default:
					break;
				}
			}

			DoMeleeAttackIfReady();
		}

		void JustDied(Unit* /*killer*/)
		{
			for(uint8 i = 0; i <= RAID_MODE(1,2); i++)
			{
				ShadowOfObsidiusList[i]->DespawnOrUnsummon();

				ShadowOfObsidiusList[i] = NULL;
			}

			me->MonsterYell("I cannot be destroyed... Only... de... layed...", LANG_UNIVERSAL, NULL);


            if (me->GetMap()->IsHeroic())
            {
                if (!me->GetMap()->GetPlayers().isEmpty())
                {
                    for (Map::PlayerList::const_iterator i = me->GetMap()->GetPlayers().begin(); i != me->GetMap()->GetPlayers().end(); ++i)
                    {
                        if (i->getSource())
                        {
                            i->getSource()->KilledMonsterCredit(39705, 0);
                        }
                    }
                }
            }
		}
	};
};
enum shadowEvents
{
    EVENT_CREPUSCOLAR_VEIL = 1,
};

enum shadowSpells
{
    SPELL_CREPUSCOLAR_VEIL                        = 76189,
    SPELL_TWITCHY                                 = 76167,
};

class npc_shadow_obsidius : public CreatureScript
{
public:
    npc_shadow_obsidius() : CreatureScript("npc_shadow_obsidius") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_shadow_obsidiusAI (creature);
    }

    struct npc_shadow_obsidiusAI : public ScriptedAI
    {
        npc_shadow_obsidiusAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            events.Reset();
            me->AddAura(SPELL_TWITCHY, me);
            me->AddAura(87427, me);
        }

        void DamageTaken(Unit *who, uint32 &damage)
        {
            damage = 0;
            me->Attack(who, true);
            me->GetMotionMaster()->MoveChase(who, 2.0f, 0.0f);
        }

        void EnterCombat(Unit* /*who*/) 
        {
            events.ScheduleEvent(EVENT_CREPUSCOLAR_VEIL, urand(3000, 4000), 0, 0);
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
                    case EVENT_CREPUSCOLAR_VEIL:
                        DoCastVictim(SPELL_CREPUSCOLAR_VEIL);
                        events.ScheduleEvent(EVENT_CREPUSCOLAR_VEIL, urand(3000, 4000), 0, 0);
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_ascendant_lord_obsidius()
{
	new boss_ascendant_lord_obsidius();
    new npc_shadow_obsidius();
}