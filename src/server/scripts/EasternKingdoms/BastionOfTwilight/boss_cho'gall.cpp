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
 * */

#include "ScriptPCH.h"
#include "bastion_of_twilight.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

enum spell_c
{
    // Chogall
    SPELL_CORRUPTED_BLOOD                 = 93189,
    SPELL_CORRUPTION_ACCELERATED          = 81836,
    SPELL_CORRUPTION_SICKNESS             = 93202,
    SPELL_CORRUPTION_MALFORMATION         = 82125,
    SPELL_CORRUPTION_ABSOLUTE             = 82170,
    
    SPELL_FURY_CHOGALL                    = 82524,

    // P1
    SPELL_SUMMON_CORRUPTING_ADHERENT      = 82712,
    SPELL_CONVERSION                      = 91303, 
    SPELL_TWISTED_DEVOTION                = 91331, 
    SPELL_FLAME_ORDER                     = 81171,
    SPELL_FLAMING_DESTRUCTION             = 81194, 
    SPELL_SHADOW_ORDER                    = 81556,
    SPELL_EMPOWERED_SHADOW                = 81572,

    // P2 - 25% PV
    SPELL_DARKENED_CREATIONS              = 82433,
    SPELL_CORRUPTION_OF_THE_OLD_GOD       = 82361,

    // Trashs
    SPELL_CORRUPTING_CRASH                = 81685,
    SPELL_DEPRAVITY                       = 81713,
    SPELL_FESTERING_BLOOD                 = 82914,
    SPELL_SPILLED_BLOOD_OF_THE_OLD_GOD    = 81757,
    SPELL_BRASIER_DAMAGE                  = 93212,
    SPELL_BRASIER_AURA                    = 93484,
    SPELL_PORTAL_SHADOW_VISUAL            = 49666,
    SPELL_PORTAL_SHADOW_VISUAL_RAYON      = 70685,
    SPELL_DEBILITING_BEAM                 = 82411,
    SPELL_DEBILITING_BEAM_H               = 93133,

    // Trash HM
    SPELL_SHADOW_SHELL                    = 93311,
    SPELL_SHADOW_POWER                    = 93301,
    SPELL_FIRE_SHELL                      = 93276,
    SPELL_FIRE_POWER                      = 93245,
};

enum Nums
{
    NPC_BLOOD_OF_THE_OLD_GOD              = 43707,
    NPC_CORRUPTING_ADHERENT               = 43622,
    NPC_CREATION_ASSOMBRIE                = 44045,
    NPC_SHADOW_LORD                       = 43592,
    NPC_FIRE_LORD                         = 43406,
    NPC_SPIKED_TENTACLE                   = 50264,
    GO_CHOGALL_FLOOR                      = 205898,
};

/**************
** BOSS Chogall
***************/

class boss_chogall : public CreatureScript
{
public:
    boss_chogall() : CreatureScript("boss_chogall") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_chogallAI(creature);
    }

    struct boss_chogallAI : public BossAI
    {
        boss_chogallAI(Creature* creature) : BossAI(creature, DATA_CHOGALL)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            _EnterCombat();

            DoZoneInCombat(me);

            instance->SetData(DATA_CHOGALL_EVENT, IN_PROGRESS);
        }

        void JustSummoned(Creature *summon)
        {
            summons.Summon(summon);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STAT_CASTING))
                return;

            events.Update(diff);
            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*killer*/)
        {
            _JustDied();
            instance->SetData(DATA_CHOGALL_EVENT, DONE);
        }
    };
};

void AddSC_boss_chogall()
{
    new boss_chogall();
}