/*
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

#include"ScriptPCH.h"
#include"the_stonecore.h"

enum Spells
{

};

enum Events
{

};

class boss_high_priestess_azil: public CreatureScript
{
    public:
        boss_high_priestess_azil() : CreatureScript("boss_high_priestess_azil") { }

    struct boss_high_priestess_azilAI: public BossAI
    {
       boss_high_priestess_azilAI(Creature* creature) : BossAI(creature, DATA_HIGH_PRIESTESS_AZIL) 
       { }

        void Reset()
        {
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
                
                }
            }

            DoMeleeAttackIfReady();
        }
     };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_high_priestess_azilAI(creature);
    }
};

void AddSC_boss_high_priestess_azil()
{
    new boss_high_priestess_azil();
}