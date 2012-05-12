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

#define MAX_ENERGY 90
#define RATE_ENERGY 1

/*
############
### Boss Anshal
############ 
*/

enum anshalEvents
{
    EVENT_WINTERING_WINDS = 1,
    EVENT_ANSHAL_REGEN_ENERGY,
};

class boss_anshal: public CreatureScript
{
    public:
        boss_anshal() : CreatureScript("boss_anshal") { }

    struct boss_anshalAI: public BossAI
    {
        boss_anshalAI(Creature* creature) : BossAI(creature, DATA_ANSHAL_EVENT), summons(me) 
        {
            instance = me->GetInstanceScript();
        }

        SummonList summons;
        InstanceScript* instance;
        bool pauseRegen;

        void Reset()
        {
            me->setPowerType(POWER_ENERGY);
            me->SetMaxPower(POWER_ENERGY, MAX_ENERGY);
            me->SetPower(POWER_ENERGY, 0);
            pauseRegen = false;
            events.Reset();
        }   

        void EnterCombat(Unit* who)
        {
            events.ScheduleEvent(EVENT_ANSHAL_REGEN_ENERGY, 1000, 0, 0);
            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ADD, me);
        }

        void JustDied(Unit* killer)
        {
            summons.DespawnAll();
            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_REMOVE, me);
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
                    case EVENT_ANSHAL_REGEN_ENERGY:
                        RegenerateEnergy();
                        events.ScheduleEvent(EVENT_ANSHAL_REGEN_ENERGY, 1000, 0, 0);
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void RegenerateEnergy()
        {
            if (pauseRegen)
                return;

            me->SetPower(POWER_ENERGY, me->GetPower(POWER_ENERGY) + RATE_ENERGY );
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
    EVENT_NEZIR_REGEN_ENERGY
};

class boss_nezir: public CreatureScript
{
    public:
        boss_nezir() : CreatureScript("boss_nezir") { }

    struct boss_nezirAI: public BossAI
    {
        boss_nezirAI(Creature* creature) : BossAI(creature, DATA_NEZIR_EVENT), summons(me)
        {
            instance = me->GetInstanceScript();
        }
        
        SummonList summons;
        InstanceScript* instance;

        bool pauseRegen;

        void Reset()
        {
            me->setPowerType(POWER_RUNIC_POWER);
            me->SetMaxPower(POWER_RUNIC_POWER, MAX_ENERGY*10); // runic power go ten by ten
            me->SetPower(POWER_RUNIC_POWER, 0);
            pauseRegen = false;
            events.Reset();
        }   

        void EnterCombat(Unit* who)
        {
            events.ScheduleEvent(EVENT_NEZIR_REGEN_ENERGY, 1000, 0, 0);
            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ADD, me);
        }

        void JustDied(Unit* killer)
        {
            summons.DespawnAll();
            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_REMOVE, me);
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
                    case EVENT_NEZIR_REGEN_ENERGY:
                        RegenerateEnergy();
                        events.ScheduleEvent(EVENT_NEZIR_REGEN_ENERGY, 1000, 0, 0);
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
        
        void RegenerateEnergy()
        {
            if (pauseRegen)
                return;

            me->SetPower(POWER_RUNIC_POWER, me->GetPower(POWER_RUNIC_POWER) + RATE_ENERGY*10 );
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
    EVENT_ROHASH_REGEN_ENERGY,
};


class boss_rohash: public CreatureScript
{
    public:
        boss_rohash() : CreatureScript("boss_rohash") { }

    struct boss_rohashAI: public BossAI
    {
        boss_rohashAI(Creature* creature) : BossAI(creature, DATA_ANSHAL_EVENT), summons(me)
        {
            instance = me->GetInstanceScript();
        }
        
        SummonList summons;
        InstanceScript* instance;

        bool pauseRegen;

        void Reset()
        {
            me->setPowerType(POWER_ENERGY);
            me->SetMaxPower(POWER_ENERGY, MAX_ENERGY);
            me->SetPower(POWER_ENERGY, 0);
            pauseRegen = false;
            events.Reset();
        }   

        void EnterCombat(Unit* who)
        {
            events.ScheduleEvent(EVENT_ROHASH_REGEN_ENERGY, 1000, 0, 0);
            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ADD, me);
        }

        void JustDied(Unit* killer)
        {
            summons.DespawnAll();

            if (instance)
                instance->SendEncounterUnit(ENCOUNTER_FRAME_REMOVE, me);
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
                    case EVENT_ROHASH_REGEN_ENERGY:
                        RegenerateEnergy();
                        events.ScheduleEvent(EVENT_ROHASH_REGEN_ENERGY, 1000, 0, 0);
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void RegenerateEnergy()
        {
            if (pauseRegen)
                return;

            me->SetPower(POWER_ENERGY, me->GetPower(POWER_ENERGY) + RATE_ENERGY);
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