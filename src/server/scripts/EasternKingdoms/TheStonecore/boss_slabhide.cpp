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

#include"ScriptPCH.h"
#include"the_stonecore.h"

enum Spells
{

};

enum Events
{

};

class boss_slabhide: public CreatureScript
{
    public:
        boss_slabhide() : CreatureScript("boss_slabhide") { }

    struct boss_slabhideAI: public BossAI
    {
        boss_slabhideAI(Creature* creature) : BossAI(creature, DATA_SLABHIDE) { }

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
        return new boss_slabhideAI(creature);
    }
};

void AddSC_boss_slabhide()
{
    new boss_slabhide();
}