/*
* Copyright (C) 2011 - 2012 Forgotten Core <http://www.forgottenlands.eu/>
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
* ScriptAuthor: dimiandre
* Script Complete 0%
**********/

#include "ScriptPCH.h"
#include "vortex_pinnacle.h"

enum Spells
{
};

enum Events
{
};

enum Actions
{
};


class boss_asaad : public CreatureScript
{
public:
    boss_asaad() : CreatureScript("boss_asaad") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_asaadAI (creature);
    }

    struct boss_asaadAI : public BossAI
    {
        boss_asaadAI(Creature* creature) : BossAI(creature, DATA_ASAAD_EVENT)
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
                }
            }

            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*killer*/)
        {
            
        }

    };
};



void AddSC_boss_asaad()
{
    new boss_asaad();
}