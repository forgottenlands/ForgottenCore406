/*
 * Copyright (C) 2005 - 2011 MaNGOS <http://www.getmangos.org/>
 *
 * Copyright (C) 2008 - 2011 TrinityCore <http://www.trinitycore.org/>
 *
 * Copyright (C) 2011 - 2012 ArkCORE <http://www.arkania.net/>
 *
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

#include "throne_of_the_four_winds.h"

/*
############
### Boss Anshal
############ 
*/

enum anshalEvents
{
    EVENT_WINTERING_WINDS = 1,
};

class boss_anshal: public CreatureScript
{
    public:
        boss_anshal() : CreatureScript("boss_anshal") { }

    struct boss_anshalAI: public BossAI
    {
        boss_anshalAI(Creature* creature) : BossAI(creature, DATA_ANSHAL_EVENT), summons(me) { }

        SummonList summons;

        void Reset()
        {
            events.Reset();
        }   

        void EnterCombat(Unit* who)
        {
        }

        void JustDied(Unit* killer)
        {
            summons.DespawnAll();
        }

        void JustSummoned(Creature* summoned)
        {
            summons.Summon(summoned);
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
                    case EVENT_WINTERING_WINDS:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
     };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_anshalAI(creature);
    }
};

/*
############
### Boss Nezir
############ 
*/

enum nezirEvents
{
    EVENT_CHILLING_WINDS = 1,
};

class boss_nezir: public CreatureScript
{
    public:
        boss_nezir() : CreatureScript("boss_nezir") { }

    struct boss_nezirAI: public BossAI
    {
        boss_nezirAI(Creature* creature) : BossAI(creature, DATA_NEZIR_EVENT), summons(me) { }
        
        SummonList summons;

        void Reset()
        {
            events.Reset();
        }   

        void EnterCombat(Unit* who)
        {
        }

        void JustDied(Unit* killer)
        {
            summons.DespawnAll();
        }

        void JustSummoned(Creature* summoned)
        {
            summons.Summon(summoned);
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
                    case EVENT_CHILLING_WINDS:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
     };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_nezirAI(creature);
    }
};

/*
############
### Boss Rohash
############ 
*/

enum rohashEvents
{
    EVENT_DEAFENING_WINDS = 1,
};


class boss_rohash: public CreatureScript
{
    public:
        boss_rohash() : CreatureScript("boss_rohash") { }

    struct boss_rohashAI: public BossAI
    {
        boss_rohashAI(Creature* creature) : BossAI(creature, DATA_ANSHAL_EVENT), summons(me) { }
        
        SummonList summons;

        void Reset()
        {
            events.Reset();
        }   

        void EnterCombat(Unit* who)
        {
        }

        void JustDied(Unit* killer)
        {
            summons.DespawnAll();
        }

        void JustSummoned(Creature* summoned)
        {
            summons.Summon(summoned);
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
                    case EVENT_DEAFENING_WINDS:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
     };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_rohashAI(creature);
    }
};

void AddSC_boss_conclave_of_wind()
{
    new boss_anshal();
    new boss_nezir();
    new boss_rohash();
}