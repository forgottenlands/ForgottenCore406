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

class boss_corborus: public CreatureScript
{
    public:
        boss_corborus() : CreatureScript("boss_corborus") { }

    struct boss_corborusAI: public BossAI
    {
        boss_corborusAI(Creature* creature) : BossAI(creature, DATA_CORBORUS) { }

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
        return new boss_corborusAI(creature);
    }
};

void AddSC_boss_corborus()
{
    new boss_corborus();
}