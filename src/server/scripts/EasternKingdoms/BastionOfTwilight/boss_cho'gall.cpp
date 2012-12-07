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


/* Scriptato da Sceicco senza base - da testare */

#include"ScriptPCH.h"
#include"bastion_of_twilight.h"

#define SAY_AGGRO "You not get through defenses!"
#define SAY_CONVERSION1 "Give me your strength!"
#define SAY_CONVERSION2 "Behold the might of the Hammer!"
#define SAY_CONVERSION3 "Everyone succumbs in the end!"
#define SAY_SUMMON1 "Behold the destiny of your fragile world!"
#define SAY_SUMMON2 "(Come brothers! Feast on hope!)"
#define SAY_SUMMON3 "More, more! (More! They need more!)"
#define SAY_CORRUPTION_OLD_GOD "Brother... it cannot be... (Destiny has come!) My strength... (Too proud! He speaks in blood! Listen!) My mind... (It is for His glory we serve!) What... is happening...? (Gone is the dawn. Come shades of twilight! Come madness! Come Havoc! Come infinite night!)"
#define SAY_DARKENED_CREATIONS1 "(The claws of fate grasp the unbelievers!!)"
#define SAY_DARKENED_CREATIONS2 "What madness have we wrought... (Not yet enough!)"
#define SAY_DARKENED_CREATIONS3 "I can't take much more... (Brother, it merely begins!!)"
#define SAY_PLAYER_KILL1 "Cho'gall cackles maniacally. (NOW they see the darkness! Their eyes are open!!)"
#define SAY_PLAYER_KILL2 "Now the master has them! (Chaos! Madness! Like a hug for your brain!!)"
#define SAY_RAID_WIPE "It is finished. (The fate of all!)"
#define SAY_DEFEAT "Brother... we are shattered... (But the master... I still hear... so angry... Master...)"


enum eSpells {
    /*corruption spells*/
    SPELL_CORRUPTED_BLOOD = 93189,
    SPELL_CORRUPTION_ACCELERATED = 81836,
    SPELL_CORRUPTION_SICKNESS = 93202,
    SPELL_CORRUPTION_MALFORMATION = 82125,
    SPELL_CORRUPTION_ABSOLUTE = 82170,

    /* phase 1: da 100 a 25% vita*/
    SPELL_CONVERSION = 93204,
    SPELL_TWISTED_DEVOTION = 93206,
    SPELL_FLAME_ORDERS = 87579,
    SPELL_SHADOW_ORDERS = 87579,
    SPELL_FURY_OF_CHOGALL = 86027,
    SPELL_SUMMON_CORRUPTING_ADHERENT = 81628,
    SPELL_FESTER_BLOOD = 82299,

    /*phase 2: da 25 a 0 vita */
    SPELL_CORRUPTION_OLD_GODS = 94144,
    SPELL_DARKENED_CREATIONS = 93161,
    SPELL_DEBILITATING_BEAM = 93133,

    /* spells corrupting adherent*/
    SPELL_DEPRAVITY = 93176,
    SPELL_CORRUPTING_CRASH = 93185,
    SPELL_SPILLED_BLOOD = 81757,
    SPELL_FESTERING_BLOOD = 82914,
    SPELL_SPRAYED_CORRUPTION = 93109
};


enum events
{
    EVENT_SUMMON_ADHERATE                 = 1,
    EVENT_CORRUPTION                      = 2,
    EVENT_FLAME_SHADOW                    = 3,
    EVENT_ENRAGE                          = 4,
    EVENT_FURY                            = 5,
};


class boss_chogall : public CreatureScript
{
public:
    boss_chogall() : CreatureScript("boss_chogall") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_chogallAI (creature);
    }

    struct boss_chogallAI : public BossAI
    {
        boss_chogallAI(Creature* creature) : BossAI(creature,DATA_CHOGALL)
        {
            pInstance = creature->GetInstanceScript();
        }

        InstanceScript* pInstance;
        EventMap events;
        uint32 phase;

        void Reset() {
            instance->SetData(DATA_CHOGALL, NOT_STARTED);
            events.Reset();
            me->ClearUnitState(UNIT_STAT_STUNNED);
			summons.DespawnAll();
			me->ResetLootMode();
            phase=1;
		}

        
		void EnterCombat(Unit * /*pWho*/) {
            me->MonsterYell(SAY_AGGRO, LANG_UNIVERSAL, NULL);
            DoZoneInCombat(me);
            instance->SetData(DATA_CHOGALL, IN_PROGRESS);
			events.Reset();
		}

        void JustDied()
        {
            instance->SetData(DATA_WYRMBREAKER, DONE);
        }

        void DamageTaken(Unit* who, uint32 &damage)
        {
            if (damage > 0){
                if (me->HealthBelowPct(25))
                     phase = 2;
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
                        case EVENT_CORRUPTION:
                            break;
                        default:
                            break;
                    }                
                }

				DoMeleeAttackIfReady();
			}
    };
};

void AddSC_boss_chogall()
{
    new boss_chogall();
}



