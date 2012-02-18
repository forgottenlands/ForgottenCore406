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
* ScriptComplete: 0%
**********/

#include "ScriptPCH.h"
#include "vortex_pinnacle.h"

enum Spells
{

};

enum events
{   

};

class boss_grand_vizier_ertan : public CreatureScript
{
public:
    boss_grand_vizier_ertan() : CreatureScript("boss_grand_vizier_ertan") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_grand_vizier_ertanAI (creature);
    }

    struct boss_grand_vizier_ertanAI : public BossAI
    {
        boss_grand_vizier_ertanAI(Creature* creature) : BossAI(creature, DATA_GRAND_VIZIER_ERTAN_EVENT), summons(me)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;
        SummonList summons;

        void Reset() 
        {
            events.Reset();
            summons.DespawnAll();
        }

        void EnterCombat(Unit* who)
        {
        }

        void JustDied(Unit* killer)
        {
            summons.DespawnAll();
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

        void JustSummoned(Creature* summoned)
        {
            summons.Summon(summoned);
        }
    };
};

void AddSC_boss_grand_vizier_ertan()
{
    new boss_grand_vizier_ertan();
}