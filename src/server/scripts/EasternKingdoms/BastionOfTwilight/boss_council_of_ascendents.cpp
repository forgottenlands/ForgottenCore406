/*
 * Copyright (C) 2008-2013 Forgotten Lands <http://www.forgottenlands.eu/>
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

#include "ScriptPCH.h"
#include "ScriptMgr.h"
#include "bastion_of_twilight.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "math.h"
 
enum Creatures
{
    //BOSS_ELEMENTIUM               = 43735,
    //BOSS_IGNACIOUS                = 43686,
    //BOSS_FELUDIUS                     = 43687,
    //BOSS_ARION                        = 43688,
    //BOSS_TERRASTRA                = 43689,
    NPC_INFERNO_RUSH                = 47501,
    NPC_WATER_BOMB                  = 44201,
    NPC_VIOLENT_CYCLONE             = 44747,
    NPC_GRAVITY_WELL                = 44824,
    NPC_LIQUID_ICE                  = 45452,
    NPC_LAVA_SEED                   = 00000, // da definire
    NPC_FROZEN_ORB_COUNCIL          = 49518,
    NPC_FLAMESTRIKE_COUNCIL         = 50297,
};
                                                               
#define SAY_AGGRO1    "You dare invade our lord's sanctum?"    
#define SOU_AGGRO1    20162
#define SAY_AGGRO2    "You will die for your insolence!"      
#define SOU_AGGRO2    20285
#define SAY_AGGRO3    "Enough of this foolishness!"            
#define SOU_AGGRO3    20237
#define SAY_AGGRO4    "We will handle them!"                  
#define SOU_AGGRO4    21843
 
#define SAY_MONSTR1   "An impressive display..."              
#define SOU_MONSTR1   20240
#define SAY_MONSTR2   "...to have made it this far."        
#define SOU_MONSTR2   21845
#define SAY_MONSTR3   "But now, witness true power..."      
#define SOU_MONSTR3   20165
#define SAY_MONSTR4   "...the fury of the elements!"      
#define SOU_MONSTR4   20288
#define SAY_MONSTR5   "BEHOLD YOUR DOOM!"                    
#define SOU_MONSTR5   20396 //20289 20166 20241 21846        
#define SOU_MONSTR6   20289        
#define SOU_MONSTR7   20166          
#define SOU_MONSTR8   20241    
#define SOU_MONSTR9   21846
 
#define SAY_KILL_FEL  "Perish!"                            
#define SOU_KILL_FEL  20163
#define SAY_KILL_IGN  "More fuel for the fire!"              
#define SOU_KILL_IGN  20286
#define SAY_KILL_ARI  "Merely a whisper in the wind...."    
#define SOU_KILL_ARI  20238
#define SAY_KILL_TER  "The soil welcomes your bones!"        
#define SOU_KILL_TER  21842
#define SAY_KILL_MON1 "Annihilate...."                      
#define SOU_KILL_MON1 20397
#define SAY_KILL_MON2 "Eradicate...."                        
#define SOU_KILL_MON2 20398
 
#define SAY_GLACIATE  "I will freeze the blood in your veins!"
#define SOU_GLACIATE  20164
#define SAY_RISING    "BURN!"                                  
#define SOU_RISING    20287
#define SAY_CALL_WIND "Wind, hear my call!"                  
#define SOU_CALL_WIND 20239
#define SAY_QUAKE     "The earth will devour you!"            
#define SOU_QUAKE     21844
#define SAY_CRUSH     "FEEL THE POWER!"                      
#define SOU_CRUSH     20400
 
#define SAY_DEATH     "Impossible...."                        
#define SOU_DEATH     20399
 
 
enum spell_c
{
    SPELL_TELEPORT_VISUAL        = 26638, //funziona
    SPELL_EXPLOSION_VISUAL       = 84207, //funziona
    SPELL_ELEMENTAL_STASIS       = 82285, //da sistemare il range in spellmgr.cpp
    // Feludius
    SPELL_FROZEN                 = 82772, //funziona
    SPELL_GLACIATE               = 82746, //funziona
    SPELL_HEART_OF_ICE           = 82665, //danno da scriptare
    SPELL_ICY_REPRISAL           = 82817, //(danno di heart of ice)
    SPELL_HYDRO_LANCE            = 82752, //funziona
    SPELL_WATER_BOMB             = 82699, //funziona
    SPELL_WATER_BOMB_EXPLO       = 82700, //solo danno, da testare se mette waterlogged
    SPELL_WATER_BOMB_VISUAL      = 54260, //###### visuale da cambiare
    SPELL_WATERLOGGED            = 82762, //funziona
    SPELL_FROST_IMBUED           = 82666, //funziona
    // Ignacious
    SPELL_AEGIS_OF_FLAME         = 82631, //funziona
    SPELL_BURNING_BLOOD          = 82660, //danno incrementale da scriptare
    SPELL_BURNING_SPITE          = 82813, //(danno di burning blood)
    SPELL_FLAME_TORRENT          = 82777, //funziona
    SPELL_INFERNO_LEAP           = 82856, //funziona
    SPELL_INFERNO_RUSH           = 82859, //funziona
    SPELL_INFERNO_AURA           = 88579, //funziona (aura delle fiamme, tikka la successiva)
    SPELL_INFERNO_PERIODIC       = 82860, //funziona (tick periodico)
    SPELL_RISING_FLAMES          = 82636, //funziona
    SPELL_RISING_FLAMES_TICK     = 82643, //funziona
    SPELL_RISING_FLAMES_BUFF     = 82639, //funziona
    SPELL_FIRE_IMBUED            = 82663, //funziona
    // Arion
    SPELL_THUNDERSHOCK           = 83067, //funziona
    SPELL_LIGHTNING_ROD          = 83099, //funziona
    SPELL_CHAIN_LIGHTNING        = 83300, //non fa danno
    SPELL_DISPERSION             = 83087, //teleport da scriptare
    SPELL_LIGHTNING_BLAST        = 83070, //non fa danno
    SPELL_CALL_WINDS             = 83491, //funziona
    SPELL_VIOLENT_CYCLONE        = 83500, //funziona
    SPELL_SWIRLING_WINDS         = 83500, //funziona
    // Terrastra
    SPELL_QUAKE                  = 83565, //funziona
    SPELL_MAGNETIC_PULL          = 28337, //funziona
    SPELL_GRAVITY_WELL_AURA      = 83579,
    SPELL_GROUNDED               = 83581, //funziona
    SPELL_HARDEN_SKIN            = 83718, //funziona
    SPELL_ERUPTION               = 83692, //funziona
    // Elementium Monstrosity
    SPELL_GROW                   = 84917, //funziona
    SPELL_LIQUID_ICE             = 84914, //danno da scriptare
    SPELL_CRYOGENIC_AURA         = 84918, //da scriptare
    SPELL_LAVA_SEED              = 84913, //manca npc
    SPELL_LAVA_PLUME             = 84912, //funziona
    SPELL_LAVA_SEED_AURA         = 84911,
    SPELL_GRAVITY_CRUSH          = 84948, //funziona
    SPELL_GRAVITY_LAPSE_AURA     = 39432,
    SPELL_ELECTRICAL_INSTABILITY = 84529,
    // Heroics
    SPELL_STATIC_OVERLOAD        = 92067, // ok
    SPELL_GRAVITY_CORE           = 92075, // ok
    SPELL_FLAMESTRIKE            = 92212, //funziona
    SPELL_FLAMESTRIKE_VISUAL     = 36730,
    SPELL_FROZEN_ORB_GLACIATE    = 92548,
    SPELL_FROST_BEACON           = 92307,
 
};
 
enum Events
{
    // General
    EVENT_SAY = 1,
    //Feludius
    EVENT_GLACIATE,
    EVENT_HYDRO_LANCE,
    EVENT_WATER_BOMB,
    EVENT_WATER_BOMB_SPAWN,
    EVENT_HEART_OF_ICE,
    //Ignacious
    EVENT_AEGIS_OF_FLAME,
    EVENT_RISING_FLAMES,
    EVENT_INFERNO_LEAP,
    EVENT_INFERNO_RUSH,
    EVENT_SPAWN_FLAME,
    EVENT_FLAME_TORRENT,
    EVENT_BURNING_BLOOD,
    //Arion
    EVENT_THUNDERSHOCK,
    EVENT_DISPERSION,
    EVENT_LIGHTNING_BLAST,
    EVENT_LIGHTNING_ROD,
    EVENT_CHAIN_LIGHTNING,
    EVENT_CYCLONE,
    //Terrastra
    EVENT_QUAKE,
    EVENT_ERUPTION,
    EVENT_HARDEN_SKIN,
    EVENT_GRAVITY_WELL,
    //Elementium Monstrosity
    EVENT_ZAP,
    EVENT_ELECTRICAL_INSTABILITY,
    EVENT_CRYOGENIC_AURA,
    EVENT_LAVA_SEED,
    EVENT_LAVA_SEED_SPAWN,
    EVENT_GRAVITY_CRUSH,
    // Heroics
    EVENT_OVERLOAD_AND_CORE,
    EVENT_FLAMESTRIKE_AND_ORB,
 
};
 
enum BossActions
{
    COUNCIL_START_EVENT,
    COUNCIL_EVENT_RESET,
    COUNCIL_EVENT_FINISHED,
    COUNCIL_EVENT_FAILED,
    COUNCIL_PHASE_1,
    COUNCIL_PHASE_2,
};
 
Position const wayPos[2] =
{
    {-1048.587f, -565.365f, 835.250f, 5.87f},
    {-1049.343f, -598.859f, 835.250f, 0.401f},
};
 
Position const center[5] =
{
    {-1008.665f, -582.682f, 831.900f, 0.0f   }, //center
    {-983.665f,  -582.682f, 831.900f, 3.14f  }, //feludius
    {-1033.665f, -582.682f, 831.900f, 0.0f   }, //ignacious
    {-1008.665f, -557.682f, 831.900f, 4.71f  }, //arion
    {-1008.665f, -607.682f, 831.900f, 1.57f  }, //terrastra
};
 
Position const cyclone[9] =
{
    { -993.250f,  -543.682f,  831.900f,  0.0f }, //start
    { -971.665f,  -581.682f,  831.900f,  0.0f },
    { -981.800f,  -609.682f,  831.900f,  0.0f },
    {-1020.860f,  -619.882f,  831.900f,  0.0f },
    {-1032.665f,  -619.282f,  835.250f,  0.0f },
    {-1049.995f,  -619.282f,  603.250f,  0.0f },
    {-1053.165f,  -619.282f,  568.460f,  0.0f },
    {-1030.965f,  -544.392f,  568.460f,  0.0f },
    {-1018.965f,  -542.782f,  831.900f,  0.0f },
};
 
 
class boss_elementium_monstrosity : public CreatureScript
{
public:
    boss_elementium_monstrosity() : CreatureScript("boss_elementium_monstrosity") { }
 
    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_elementium_monstrosityAI (creature);
    }
 
    struct boss_elementium_monstrosityAI : public ScriptedAI
    {
        boss_elementium_monstrosityAI(Creature* creature) : ScriptedAI(creature), eventActive(false), initialized(false)
        {
            instance = creature->GetInstanceScript();
        }
 
        InstanceScript* instance;
        EventMap events;
        Unit* prevtarget;
        Unit* chaintargets[3];
        bool initialized;
        bool isEncounterDone;
        bool phasechange;
        uint8 phase;
        uint8 count;
        uint32 killtimer;
        uint8 zap;
 
        Creature* ascendant[4];
 
        bool eventActive;
 
        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
            me->SetVisible(false);
            
            ascendant[0] = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_IGNACIOUS));
            ascendant[1] = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_FELUDIUS));
            ascendant[2] = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_ARION));
            ascendant[3] = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_TERRASTRA));
           
            for(uint8 i = 0; i<=3; i++)
            {
                if(ascendant[i] == NULL)
                    return;

                ascendant[i]->SetMaxHealth(ascendant[i]->GetMaxHealth());
            }

            eventActive = false;
            initialized = true;
            phase       = 0;
            count       = 0;
            killtimer   = 0;
            zap = 1;
            phasechange = false;
            DoAction(COUNCIL_EVENT_RESET);
            chaintargets[0]=NULL;
            chaintargets[1]=NULL;
            chaintargets[2]=NULL;
        }

        void UpdateAI(const uint32 diff)
        {
                if (!UpdateVictim())
                    return;

                if (killtimer>=diff)
                    killtimer -= diff;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                    case EVENT_SAY:
                        if (phase == 0)
                        {
                            ascendant[0]->MonsterYell(SAY_AGGRO2, 0, 0);
                            DoPlaySoundToSet(ascendant[0], SOU_AGGRO2);
                        }
                        else if (phase == 1)
                        {
                            //###############
                            // here will begin phase 2
                            //###############
                            std::list<Creature*> unitList;
                            ascendant[0]->GetCreatureListWithEntryInGrid(unitList, NPC_INFERNO_RUSH, 100.0f);
                            for (std::list<Creature*>::const_iterator itr = unitList.begin(); itr != unitList.end(); ++itr)
                            {// this will despawn the flames
                                if (*itr)
                                    (*itr)->DespawnOrUnsummon();
                            }

                            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_STATIC_OVERLOAD);
                            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_GRAVITY_CORE);
                            //visibility
                            ascendant[0]->SetReactState(REACT_PASSIVE);
                            ascendant[1]->SetReactState(REACT_PASSIVE);
                            ascendant[2]->SetReactState(REACT_AGGRESSIVE);
                            ascendant[3]->SetReactState(REACT_AGGRESSIVE);
                            ascendant[0]->SetVisible(false);
                            ascendant[1]->SetVisible(false);
                            ascendant[2]->SetVisible(true);
                            ascendant[3]->SetVisible(true);
                            ascendant[0]->AttackStop();
                            ascendant[1]->AttackStop();
                            ascendant[0]->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                            ascendant[1]->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                            ascendant[2]->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                            ascendant[3]->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                            ascendant[2]->SetPosition(wayPos[0]);
                            ascendant[3]->SetPosition(wayPos[1]);
                            ascendant[3]->MonsterYell(SAY_AGGRO4, 0, 0);
                            DoPlaySoundToSet(ascendant[3], SOU_AGGRO4);
 
                            DoZoneInCombat(ascendant[3]);
                            DoZoneInCombat(ascendant[2]);

                            //AI schedules                            
                            events.ScheduleEvent(EVENT_CYCLONE, 6000);                            
                            events.ScheduleEvent(EVENT_GRAVITY_WELL, 7000);
                            events.ScheduleEvent(EVENT_LIGHTNING_ROD, 7600);
                            events.ScheduleEvent(EVENT_ERUPTION, 7000);
                            events.ScheduleEvent(EVENT_CHAIN_LIGHTNING, 19400);
                            events.ScheduleEvent(EVENT_HARDEN_SKIN, 20000);
                            events.ScheduleEvent(EVENT_QUAKE, 30000);
                            events.ScheduleEvent(EVENT_THUNDERSHOCK, 60000);
                            if (me->GetMap()->GetDifficulty() == RAID_DIFFICULTY_10MAN_HEROIC || me->GetMap()->GetDifficulty() == RAID_DIFFICULTY_25MAN_HEROIC)
                                events.ScheduleEvent(EVENT_FLAMESTRIKE_AND_ORB, 19000);
                        }
                        else if (phase == 2)
                        {
                            switch (count)
                            {
                            case 0:
                                ascendant[2]->MonsterYell(SAY_MONSTR2, 0, 0);
                                DoPlaySoundToSet(ascendant[2], SOU_MONSTR2);
                                events.ScheduleEvent(EVENT_SAY, 3000);
                                ascendant[2]->GetMotionMaster()->MovePoint(0, center[0]);
                                break;
                            case 1:
                                ascendant[1]->MonsterYell(SAY_MONSTR3, 0, 0);
                                DoPlaySoundToSet(ascendant[1], SOU_MONSTR3);
                                events.ScheduleEvent(EVENT_SAY, 3000);
                                ascendant[1]->GetMotionMaster()->MovePoint(0, center[0]);
                                break;
                            case 2:
                                ascendant[0]->MonsterYell(SAY_MONSTR4, 0, 0);
                                DoPlaySoundToSet(ascendant[0], SOU_MONSTR4);
                                events.ScheduleEvent(EVENT_SAY, 3000);
                                ascendant[0]->GetMotionMaster()->MovePoint(0, center[0]);
                                break;
                            case 3:
                                me->MonsterYell(SAY_MONSTR5, 0, 0);
                                DoPlaySoundToSet(me, SOU_MONSTR5);
                                DoPlaySoundToSet(me, SOU_MONSTR6);
                                DoPlaySoundToSet(me, SOU_MONSTR7);
                                DoPlaySoundToSet(me, SOU_MONSTR8);
                                DoPlaySoundToSet(me, SOU_MONSTR9);
                                events.ScheduleEvent(EVENT_SAY, 2000);
                                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_ELEMENTAL_STASIS);
                                ascendant[0]->SetReactState(REACT_PASSIVE);
                                ascendant[1]->SetReactState(REACT_PASSIVE);
                                ascendant[2]->SetReactState(REACT_PASSIVE);
                                ascendant[3]->SetReactState(REACT_PASSIVE);
                                ascendant[0]->SetVisible(false);
                                ascendant[1]->SetVisible(false);
                                ascendant[2]->SetVisible(false);
                                ascendant[3]->SetVisible(false);
                                ascendant[0]->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                                ascendant[1]->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                                ascendant[2]->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                                ascendant[3]->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                                me->NearTeleportTo(center[0].GetPositionX(), center[0].GetPositionY(), center[0].GetPositionZ(), center[0].GetOrientation());
                                me->SetVisible(true);
                                me->CastSpell(me, SPELL_EXPLOSION_VISUAL, false);
                                break;
                            case 4:
                                me->SetReactState(REACT_AGGRESSIVE);
                                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                                //AI Schedules
                                events.ScheduleEvent(EVENT_ZAP, 2000);
                                events.ScheduleEvent(EVENT_CRYOGENIC_AURA, 2000);
                                events.ScheduleEvent(EVENT_ELECTRICAL_INSTABILITY, 10000);
                                events.ScheduleEvent(EVENT_LAVA_SEED, 12000);
                                events.ScheduleEvent(EVENT_GRAVITY_CRUSH, 6000);
                                break;
                            default:
                                break;
                            }
                            count++;
                        }
                        return;
                        break;
                    //##############
                    // Feludius
                    //##############
                    case EVENT_GLACIATE:
                        if (ascendant[1] && ascendant[1]->getVictim())
                        {
                            ascendant[1]->CastSpell(ascendant[1]->getVictim(), SPELL_GLACIATE, false);
                            ascendant[1]->MonsterYell(SAY_GLACIATE, 0, 0);
                            DoPlaySoundToSet(ascendant[1], SOU_GLACIATE);
                        }
                        events.ScheduleEvent(EVENT_GLACIATE, 16000);
                        return;
                        break;
                    case EVENT_HYDRO_LANCE:
                        if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0)){
                            if (ascendant[1] != NULL){
                                ascendant[1]->CastSpell(ascendant[1], SPELL_HYDRO_LANCE, false);
                            }
                        }
                        events.ScheduleEvent(EVENT_HYDRO_LANCE, 10000);
                        return;
                        break;
                    case EVENT_WATER_BOMB:
                        if (ascendant[1])
                        {
                            ascendant[1]->CastSpell(ascendant[1]->getVictim(), SPELL_WATER_BOMB, false);
                        }
                        events.ScheduleEvent(EVENT_WATER_BOMB, 16000);
                        events.ScheduleEvent(EVENT_WATER_BOMB_SPAWN, 2000);
                        return;
                        break;
                    case EVENT_WATER_BOMB_SPAWN:
                        {
                            if (!ascendant[1])
                                return;
                            uint32 num = urand(8, 12);
                            for(uint32 i=0; i<num; i++)
                            {
                                float dir  = float(urand(0, 628))/100;
                                float dist = float(urand(15, 50));
                                ascendant[1]->SummonCreature(NPC_WATER_BOMB,
                                                        ascendant[1]->GetPositionX() + dist*cos(dir),
                                                        ascendant[1]->GetPositionY() + dist*cos(dir),
                                                        ascendant[1]->GetPositionZ(),
                                                        ascendant[1]->GetOrientation());
                            }
                            return;
                        }
                        break;
                    case EVENT_HEART_OF_ICE:
                        if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0)){
                            if (ascendant[1] != NULL){
                                ascendant[1]->CastSpell(ascendant[1], SPELL_HEART_OF_ICE, false);
                            }
                        }
                        events.ScheduleEvent(EVENT_HEART_OF_ICE, urand(20000, 40000));
                        return;
                        break;
                    //##############
                    // Ignacious
                    //##############
                    case EVENT_AEGIS_OF_FLAME:
                        if (ascendant[0] != NULL)
                        {
                            ascendant[0]->CastSpell(ascendant[0], SPELL_AEGIS_OF_FLAME, false);
                            events.ScheduleEvent(EVENT_RISING_FLAMES, 1550);
                        }
                        events.ScheduleEvent(EVENT_AEGIS_OF_FLAME, 16000);
                        return;
                        break;
                    case EVENT_RISING_FLAMES:
                        if (ascendant[0] != NULL)
                        {
                            ascendant[0]->CastSpell(ascendant[0], SPELL_RISING_FLAMES, false);
                            ascendant[0]->MonsterYell(SAY_RISING, 0, 0);
                            DoPlaySoundToSet(ascendant[0], SOU_RISING);
                        }
                        return;
                        break;
                    case EVENT_INFERNO_LEAP:
                        if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, -10.0f)){
                            if (ascendant[0] != NULL){
                                ascendant[0]->CastSpell(ascendant[0], SPELL_INFERNO_LEAP, false);
                                events.ScheduleEvent(EVENT_INFERNO_RUSH, 1550);
                            }
                        }
                        events.ScheduleEvent(EVENT_INFERNO_LEAP, 16000);
                        return;
                        break;
                    case EVENT_INFERNO_RUSH:
                        if (Unit* pTarget = ascendant[0]->getVictim()){
                            if (ascendant[0] != NULL){
                                ascendant[0]->CastSpell(pTarget, SPELL_INFERNO_RUSH, false);
                                events.ScheduleEvent(EVENT_SPAWN_FLAME, 750);
                            }
                        }
                        return;
                        break;
                    case EVENT_SPAWN_FLAME:
                        if (ascendant[0] != NULL)
                        {
                            std::list<Creature*> unitList;
                            ascendant[0]->GetCreatureListWithEntryInGrid(unitList, NPC_INFERNO_RUSH, 100.0f);
                            for (std::list<Creature*>::const_iterator itr = unitList.begin(); itr != unitList.end(); ++itr)
                            {// this will despawn the previous flame trail
                                if (*itr)
                                    (*itr)->DespawnOrUnsummon();
                            }
                            ascendant[0]->SummonCreature(NPC_INFERNO_RUSH, ascendant[0]->GetPositionX(),ascendant[0]->GetPositionY(), ascendant[0]->GetPositionZ(),ascendant[0]->GetOrientation());
                        }
                        return;
                        break;
                    case EVENT_FLAME_TORRENT:
                        if (Unit *pTarget = ascendant[0]->getVictim())
                        {
                            if (ascendant[0] != NULL)
                            {
                                ascendant[0]->CastSpell(pTarget, SPELL_FLAME_TORRENT, false);
                            }
                        }
                        events.ScheduleEvent(EVENT_FLAME_TORRENT, 10000);
                        return;
                        break;
                    case EVENT_BURNING_BLOOD:
                        if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0)){
                            if (ascendant[0] != NULL){
                                ascendant[0]->CastSpell(ascendant[1], SPELL_BURNING_BLOOD, false);
                            }
                        }
                        events.ScheduleEvent(EVENT_BURNING_BLOOD, urand(20000, 40000));
                        return;
                        break;
                    //##############
                    // Arion
                    //##############
                    case EVENT_LIGHTNING_ROD:
                        if (me->GetMap()->GetDifficulty() == RAID_DIFFICULTY_25MAN_NORMAL || me->GetMap()->GetDifficulty() == RAID_DIFFICULTY_25MAN_HEROIC)
                        {//25 man mode, 3 targets
                            if (ascendant[2] != NULL)
                            {
                                std::list<Unit*> chaintargetList;
                                SelectTargetList(chaintargetList, 3, SELECT_TARGET_RANDOM, 100, true);
                                int i=0;
                                for (std::list<Unit*>::const_iterator iter = chaintargetList.begin(); iter != chaintargetList.end(); ++iter)
                                {
                                                ascendant[2]->AddAura(SPELL_LIGHTNING_ROD, (*iter));
                                    if (i<3)
                                        chaintargets[i]= *iter;
                                    i++;
                                }
                            }
                        }
                        else if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                        {// 10 man mode, 1 target
                            if (ascendant[2] != NULL)
                            {
                                chaintargets[0] = pTarget;
                                ascendant[2]->AddAura(SPELL_LIGHTNING_ROD, pTarget);
                            }
                        }
                        events.ScheduleEvent(EVENT_LIGHTNING_ROD, 30000);
                        return;
                        break;
                    case EVENT_CHAIN_LIGHTNING:
                        if (me->GetMap()->GetDifficulty() == RAID_DIFFICULTY_25MAN_NORMAL || me->GetMap()->GetDifficulty() == RAID_DIFFICULTY_25MAN_HEROIC)
                        {//25 man mode, 3 targets
                            for (int i=0; i<3; i++)
                            {
                                if (ascendant[2] != NULL && chaintargets[i]!= NULL)
                                {
                                    ascendant[2]->CastSpell(chaintargets[i], SPELL_CHAIN_LIGHTNING, false);
                                }
                            }
                        }
                        else
                        {// 10 man mode, 1 target
                            if (ascendant[2] != NULL && chaintargets[0] != NULL)
                            {
                                ascendant[2]->CastSpell(chaintargets[0], SPELL_CHAIN_LIGHTNING, false);
                            }
                        }
                        events.ScheduleEvent(EVENT_CHAIN_LIGHTNING, 30000);
                        return;
                        break;
                    case EVENT_DISPERSION:
                        if (Unit *pTarget = ascendant[2]->getVictim())
                            prevtarget=pTarget;
                        if (ascendant[2] != NULL)
                        {
                            ascendant[2]->CastSpell(ascendant[2], SPELL_DISPERSION, false);
                        }
                        events.ScheduleEvent(EVENT_LIGHTNING_BLAST, 1550);
                        return;
                        break;
                    case EVENT_LIGHTNING_BLAST:
                        if (prevtarget && ascendant[2] != NULL)
                        {
                            ascendant[2]->CastSpell(prevtarget, SPELL_LIGHTNING_BLAST, false);
                        }
                        ascendant[2]->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                        ascendant[2]->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                        me->NearTeleportTo(urand(-1019,-975), urand(-624,-535), me->GetPositionZ(), me->GetOrientation());
                        events.ScheduleEvent(EVENT_DISPERSION, 13450);
                        return;
                        break;
                    case EVENT_CYCLONE:
                        if (ascendant[2] != NULL)
                        {
                            ascendant[2]->CastSpell(ascendant[2], SPELL_CALL_WINDS, false);
                            ascendant[2]->MonsterYell(SAY_CALL_WIND, 0, 0);
                            DoPlaySoundToSet(ascendant[2], SOU_CALL_WIND);
                        }
                        events.ScheduleEvent(EVENT_CYCLONE, 60000);
                        return;
                        break;
                    case EVENT_THUNDERSHOCK:
                        if (ascendant[2] != NULL)
                        {
                            ascendant[2]->CastSpell(ascendant[2], SPELL_THUNDERSHOCK, false);
                        }
                        events.ScheduleEvent(EVENT_THUNDERSHOCK, 60000);
                        return;
                        break;
                    //##############
                    // Terrastra
                    //##############
                    case EVENT_QUAKE:
                        if (ascendant[3] != NULL)
                        {
                            ascendant[3]->CastSpell(ascendant[2], SPELL_QUAKE, false);
                            ascendant[3]->MonsterYell(SAY_QUAKE, 0, 0);
                            DoPlaySoundToSet(ascendant[3], SOU_QUAKE);
                        }
                        events.ScheduleEvent(EVENT_QUAKE, 60000);
                        return;
                        break;
                    case EVENT_HARDEN_SKIN:
                        if (ascendant[3] != NULL)
                        {
                            ascendant[3]->CastSpell(ascendant[2], SPELL_HARDEN_SKIN, false);
                        }
                        events.ScheduleEvent(EVENT_HARDEN_SKIN, 15000);
                        return;
                        break;
                    case EVENT_GRAVITY_WELL:
                        if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, -10.0f))
                        {
                            if (ascendant[3] != NULL)
                            {
                                ascendant[3]->SummonCreature(NPC_GRAVITY_WELL, pTarget->GetPositionX(),pTarget->GetPositionY(), pTarget->GetPositionZ(),pTarget->GetOrientation());
                            }
                        }
                        events.ScheduleEvent(EVENT_GRAVITY_WELL, 60000);
                        return;
                        break;
                    case EVENT_ERUPTION:
                        if (ascendant[3] != NULL)
                        {
                            ascendant[3]->CastSpell(ascendant[3], SPELL_ERUPTION, false);
                        }
                        events.ScheduleEvent(EVENT_ERUPTION, 15000);
                        return;
                        break;
                    //##############
                    // Monstrosity
                    //##############
                    case EVENT_ZAP:
                        for (int i=0; i<zap; i++)
                        {
                            if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                            {
                                me->CastSpell(pTarget, SPELL_ELECTRICAL_INSTABILITY, true);
                            }
                        }
                        events.ScheduleEvent(EVENT_ZAP, 1000);
                        return;
                        break;
                    case EVENT_ELECTRICAL_INSTABILITY:
                        zap++;
                        events.ScheduleEvent(EVENT_ELECTRICAL_INSTABILITY, urand(12000, 15000));
                        return;
                        break;
                    case EVENT_CRYOGENIC_AURA:
                        {
                            std::list<Creature*> unitList;
                            ascendant[0]->GetCreatureListWithEntryInGrid(unitList, NPC_LIQUID_ICE, 100.0f);
                            bool newspawn = true;    
                            for (std::list<Creature*>::const_iterator itr = unitList.begin(); itr != unitList.end(); ++itr)
                            {
                                float dist = 4.0f;
                                if ((*itr)->GetAura(SPELL_GROW))
                                {
                                    dist *= pow (1.4,(*itr)->GetAura(SPELL_GROW)->GetStackAmount());
                                    //uint32 stack=(*itr)->GetAura(SPELL_GROW)->GetStackAmount();
                                    //for (int i=0; i<stack; i++)
                                    //    dist *= 1.4;
                                }
                                if (*itr && me->GetDistance2d(*itr) > dist)
                                {
                                    newspawn = false;
                                    (*itr)->AddAura(SPELL_GROW, *itr);
                                }
                                if (newspawn)
                                    me->SummonCreature(NPC_LIQUID_ICE, me->GetPositionX(),me->GetPositionY(), me->GetPositionZ(),me->GetOrientation());
                            }
 
                            if (me->GetMap()->GetDifficulty() == RAID_DIFFICULTY_10MAN_HEROIC || me->GetMap()->GetDifficulty() == RAID_DIFFICULTY_25MAN_HEROIC)
                                events.ScheduleEvent(EVENT_CRYOGENIC_AURA, 1500);
                            else
                                events.ScheduleEvent(EVENT_CRYOGENIC_AURA, 3000);
                            return;
                            break;
                        }
                    case EVENT_GRAVITY_CRUSH:
                        if (me->GetMap()->GetDifficulty() == RAID_DIFFICULTY_25MAN_NORMAL || me->GetMap()->GetDifficulty() == RAID_DIFFICULTY_25MAN_HEROIC)
                        {//25 man mode, 3 targets
                            if (ascendant[2] != NULL)
                            {
                                std::list<Unit*> chaintargetList;
                                SelectTargetList(chaintargetList, 3, SELECT_TARGET_RANDOM, 100, true);
                                for (std::list<Unit*>::const_iterator iter = chaintargetList.begin(); iter != chaintargetList.end(); ++iter)
                                {
                                                ascendant[2]->AddAura(SPELL_GRAVITY_CRUSH, (*iter));
                                    DoTeleportPlayer((*iter), (*iter)->GetPositionX(), (*iter)->GetPositionY(), (*iter)->GetPositionZ()+35, (*iter)->GetOrientation());
                                }
                            }
                        }
                        else if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                        {// 10 man mode, 1 target
                            if (ascendant[2] != NULL)
                            {
                                ascendant[2]->AddAura(SPELL_GRAVITY_CRUSH, pTarget);
                                DoTeleportPlayer(pTarget, pTarget->GetPositionX(), pTarget->GetPositionY(), pTarget->GetPositionZ()+35, pTarget->GetOrientation());
                            }
                        }
                        me->CastSpell(me, SPELL_GRAVITY_CRUSH, false);
                        me->MonsterYell(SAY_CRUSH, 0, 0);
                        DoPlaySoundToSet(me, SOU_CRUSH);
                        events.ScheduleEvent(EVENT_GRAVITY_CRUSH, 12000);
                        return;
                        break;
                    case EVENT_LAVA_SEED:
                        me->CastSpell(me, SPELL_LAVA_SEED, false);
                        events.ScheduleEvent(EVENT_LAVA_SEED, 12000);
                        events.ScheduleEvent(EVENT_LAVA_SEED_SPAWN, 2000);
                        return;
                        break;
                    case EVENT_LAVA_SEED_SPAWN:
                        {
                            uint32 num = urand(12, 20);
                            for(uint32 i=0; i<num; i++)
                            {
                                float dir  = float(urand(0, 628))/100;
                                float dist = float(urand(15, 60));
                               me->SummonCreature(NPC_LAVA_SEED,
                                                       me->GetPositionX() + dist*cos(dir),
                                                       me->GetPositionY() + dist*cos(dir),
                                                       me->GetPositionZ()+35,
                                                       me->GetOrientation());
                            }
                            return;
                        }
                        break;
                    //##############
                    // Heroics
                    //##############
                    case EVENT_OVERLOAD_AND_CORE:
                        if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                        {
                            me->AddAura(SPELL_ELECTRICAL_INSTABILITY, pTarget);
                            if (Unit *rTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                            {
                                if (pTarget->GetGUID() == rTarget->GetGUID())
                                    rTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true);
                                if (pTarget->GetGUID() == rTarget->GetGUID())
                                    rTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true);
                                //if the same target get chosen four times in a row, nevermind, its his/her fate (or maybe the only one left)
                                me->AddAura(SPELL_GRAVITY_CORE, rTarget);
                            }
                        }
                        events.ScheduleEvent(EVENT_OVERLOAD_AND_CORE, 30000);
                        return;
                        break;
                    case EVENT_FLAMESTRIKE_AND_ORB:
                        if (Unit *pTarget = SelectTarget(SELECT_TARGET_FARTHEST, 0))
                        {
                            me->SummonCreature(NPC_FLAMESTRIKE_COUNCIL, pTarget->GetPositionX(),pTarget->GetPositionY(), pTarget->GetPositionZ(),pTarget->GetOrientation());
                            if (Unit *rTarget = SelectTarget(SELECT_TARGET_NEAREST, 0))
                            {
                                //if the same target get chosen four times in a row, nevermind, its his/her fate (or maybe the only one left)
                                me->SummonCreature(NPC_FROZEN_ORB_COUNCIL, rTarget->GetPositionX(),rTarget->GetPositionY(), rTarget->GetPositionZ(),rTarget->GetOrientation());
                            }
                        }
                        events.ScheduleEvent(EVENT_FLAMESTRIKE_AND_ORB, 30000);
                        return;
                        break;
                    default:
                        break;
                    }
                }
            DoMeleeAttackIfReady();
        }
 
        void DoAction(const int32 action)
        {
            switch(action)
            {
            case COUNCIL_START_EVENT:
                if (phase != 0 || eventActive)
                    return;

                if (instance)
                    instance->SetData(DATA_COUNCIL_EVENT, IN_PROGRESS);

                eventActive = true;
                events.Reset();
                //visibility
                ascendant[2]->SetReactState(REACT_PASSIVE);
                ascendant[2]->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                ascendant[2]->SetVisible(false);
                ascendant[3]->SetReactState(REACT_PASSIVE);
                ascendant[3]->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                ascendant[3]->SetVisible(false);
 
                DoZoneInCombat(me);
                DoZoneInCombat(ascendant[0]);
                DoZoneInCombat(ascendant[1]);

                //AI schedules
                ascendant[0]->MonsterYell(SAY_AGGRO1, 0, 0);
                DoPlaySoundToSet(ascendant[0], SOU_AGGRO1);
                events.ScheduleEvent(EVENT_SAY, 4000);
                events.ScheduleEvent(EVENT_GLACIATE, 15000);
                events.ScheduleEvent(EVENT_HYDRO_LANCE, 6500);
                events.ScheduleEvent(EVENT_WATER_BOMB, urand(8000, 10000));
                events.ScheduleEvent(EVENT_HEART_OF_ICE, urand(20000, 40000));
                events.ScheduleEvent(EVENT_AEGIS_OF_FLAME, urand(15000, 20000));
                events.ScheduleEvent(EVENT_INFERNO_LEAP, urand(10000, 10000));
                events.ScheduleEvent(EVENT_FLAME_TORRENT, 6500);
                events.ScheduleEvent(EVENT_BURNING_BLOOD, urand(20000, 40000));
                if (me->GetMap()->GetDifficulty() == RAID_DIFFICULTY_10MAN_HEROIC || me->GetMap()->GetDifficulty() == RAID_DIFFICULTY_25MAN_HEROIC)
                    events.ScheduleEvent(EVENT_OVERLOAD_AND_CORE, 19000);
                break;
            case COUNCIL_PHASE_1:
                if (phase==0)
                {//here will comes arion and terrastra
                    phase = 1;
                    events.Reset();
                    ascendant[2]->MonsterYell(SAY_AGGRO3, 0, 0);
                    DoPlaySoundToSet(ascendant[2], SOU_AGGRO3);
 
                    events.ScheduleEvent(EVENT_SAY, 4000);
                }
                break;
            case COUNCIL_PHASE_2:
                if (phase==1)
                {//here will summon the elementium monstrosity
                    std::list<Creature*> unitList;
                    ascendant[2]->GetCreatureListWithEntryInGrid(unitList, NPC_VIOLENT_CYCLONE, 100.0f);
                    for (std::list<Creature*>::const_iterator itr = unitList.begin(); itr != unitList.end(); ++itr)
                    {// this will despawn the cyclones
                        if (*itr)
                            (*itr)->DespawnOrUnsummon();
                    }
                    ascendant[3]->GetCreatureListWithEntryInGrid(unitList, NPC_GRAVITY_WELL, 100.0f);
                    for (std::list<Creature*>::const_iterator itr = unitList.begin(); itr != unitList.end(); ++itr)
                    {// this will despawn the gravity wells
                        if (*itr)
                            (*itr)->DespawnOrUnsummon();
                    }
                    me->GetCreatureListWithEntryInGrid(unitList, NPC_FLAMESTRIKE_COUNCIL, 100.0f);
                    for (std::list<Creature*>::const_iterator itr = unitList.begin(); itr != unitList.end(); ++itr)
                    {// this will despawn the flamestrike
                        if (*itr)
                            (*itr)->DespawnOrUnsummon();
                    }
                    me->GetCreatureListWithEntryInGrid(unitList, NPC_FROZEN_ORB_COUNCIL, 100.0f);
                    for (std::list<Creature*>::const_iterator itr = unitList.begin(); itr != unitList.end(); ++itr)
                    {// this will despawn the frozen orb
                        if (*itr)
                            (*itr)->DespawnOrUnsummon();
                    }
                    phase = 2;
                    events.Reset();
                    std::list<Unit*> targets;
                    ascendant[0]->SetReactState(REACT_PASSIVE);
                    ascendant[1]->SetReactState(REACT_PASSIVE);
                    ascendant[2]->SetReactState(REACT_PASSIVE);
                    ascendant[3]->SetReactState(REACT_PASSIVE);
                    ascendant[0]->SetVisible(true);
                    ascendant[1]->SetVisible(true);
                    ascendant[2]->SetVisible(true);
                    ascendant[3]->SetVisible(true);
                    ascendant[0]->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                    ascendant[1]->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                    ascendant[2]->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                    ascendant[3]->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                    ascendant[0]->NearTeleportTo(center[2].GetPositionX(), center[2].GetPositionY(), center[2].GetPositionZ(), center[2].GetOrientation());
                    ascendant[1]->NearTeleportTo(center[1].GetPositionX(), center[1].GetPositionY(), center[1].GetPositionZ(), center[1].GetOrientation());
                    ascendant[2]->NearTeleportTo(center[3].GetPositionX(), center[3].GetPositionY(), center[3].GetPositionZ(), center[3].GetOrientation());
                    ascendant[3]->NearTeleportTo(center[4].GetPositionX(), center[4].GetPositionY(), center[4].GetPositionZ(), center[4].GetOrientation());
                    ascendant[0]->CastSpell(ascendant[0], SPELL_TELEPORT_VISUAL, false);
                    ascendant[1]->CastSpell(ascendant[0], SPELL_TELEPORT_VISUAL, false);
                    ascendant[2]->CastSpell(ascendant[0], SPELL_TELEPORT_VISUAL, false);
                    ascendant[3]->CastSpell(ascendant[0], SPELL_TELEPORT_VISUAL, false);
                    ascendant[3]->MonsterYell(SAY_MONSTR1, 0, 0);
                    DoPlaySoundToSet(ascendant[3], SOU_MONSTR1);
                    ascendant[3]->GetMotionMaster()->MovePoint(0, center[0]);
                    events.ScheduleEvent(EVENT_SAY, 3000);
                }
                break;
            case COUNCIL_EVENT_RESET:
                // Resets Encounter
                //################
                //  da scriptare
                //################
                if(eventActive)
                {
                    me->SetFullHealth();
                    eventActive = false;
 
                    events.Reset();
 
                    if (instance)
                    instance->SetData(DATA_COUNCIL_EVENT, FAIL);
                }
                break;
 
            case COUNCIL_EVENT_FINISHED:
                //################
                //  da scriptare
                //################
 
                if (instance)
                    instance->SetData(DATA_COUNCIL_EVENT, DONE);
               
                events.Reset();
                eventActive = false;
                break;
 
            default:
                break;
            }
        }
 
        void JustDied ()
        {
            me->AI()->DoAction(COUNCIL_EVENT_FINISHED);
            me->MonsterYell(SAY_DEATH, 0, 0);
            DoPlaySoundToSet(me, SOU_DEATH);
            std::list<Creature*> unitList;
            me->GetCreatureListWithEntryInGrid(unitList, NPC_LIQUID_ICE, 100.0f);

            for (uint8 i = 0; i < 4; i++)
                ascendant[i]->DisappearAndDie();

            for (std::list<Creature*>::const_iterator itr = unitList.begin(); itr != unitList.end(); ++itr)
            {// this will despawn the cyclones
                if (*itr)
                    (*itr)->DespawnOrUnsummon();
            }
        }
 
        void KilledUnit(Unit* victim)
        {
            if (victim->GetTypeId() != TYPEID_PLAYER || killtimer > 0)
                return;
            switch (urand(1, 2))
            {
            case 1:
                me->MonsterYell(SAY_KILL_MON1, 0, 0);
                DoPlaySoundToSet(me, SOU_KILL_MON1);
                break;
            case 2:
                me->MonsterYell(SAY_KILL_MON2, 0, 0);
                DoPlaySoundToSet(me, SOU_KILL_MON2);
                break;
            default:
                break;
            }
            killtimer = 10000;
        }
 
    private:
        void DespawnCreatures(uint32 entry)
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, me, entry, 100.0f);
 
            if (creatures.empty())
                return;
 
            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                (*iter)->DespawnOrUnsummon();
        }
    };
};
 
class boss_ascendants : public CreatureScript
{
public:
    boss_ascendants() : CreatureScript("boss_ascendants") { }
 
    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_ascendantsAI (creature);
    }
 
    struct boss_ascendantsAI : public ScriptedAI
    {
        boss_ascendantsAI(Creature* creature) : ScriptedAI(creature), activated(false), isFirstTron(false)
        {
            instance = creature->GetInstanceScript();
 
            creature->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            creature->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
            creature->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
 
            homePosition = creature->GetHomePosition();
        }
 
        InstanceScript* instance;
        EventMap events;
        bool activated;
        bool isFirstTron;
        bool isMovingHome;
        Position homePosition;
        Creature* elementium;
        uint32 killtimer;
 
        void EnterCombat(Unit * who)
        {
            if (Creature* monstrosity = ObjectAccessor::GetCreature(*me,instance->GetData64(DATA_MONSTROSITY)))
                monstrosity->AI()->DoAction(COUNCIL_START_EVENT);

            killtimer =0;
        }
 
        void Reset()
        {
            if (me->GetEntry() != BOSS_FELUDIUS && me->GetEntry() != BOSS_IGNACIOUS)
                me->SetVisible(false);

            if (Creature* elementium = ObjectAccessor::GetCreature(*me,instance->GetData64(DATA_MONSTROSITY)))
                elementium->AI()->DoAction(COUNCIL_EVENT_RESET);
        };
 
        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (killtimer>=diff)
                killtimer -= diff;
 
            DoMeleeAttackIfReady();
        }
 
        void DamageTaken(Unit* who, uint32& damage)
        {
            if (me->GetEntry() == BOSS_FELUDIUS && who->HasAura(SPELL_FIRE_IMBUED))
                damage *=2;
            else if (me->GetEntry() == BOSS_IGNACIOUS && who->HasAura(SPELL_FROST_IMBUED))
                damage *=2;
 
            if (Creature* elementium = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_MONSTROSITY)))
            {
                elementium->SetHealth(elementium->GetHealth()-damage);
               
                // phase change when an attack will put an ascendant under 25% hp
                if (me->GetHealthPct() <= 25.0f )
                {
                    if (me->GetEntry() == BOSS_FELUDIUS || me->GetEntry() == BOSS_IGNACIOUS)
                        elementium->AI()->DoAction(COUNCIL_PHASE_1);
                    else
                        elementium->AI()->DoAction(COUNCIL_PHASE_2);
                }
            }
        }
 
        void KilledUnit(Unit* victim)
        {
            if (victim->GetTypeId() != TYPEID_PLAYER || killtimer > 0)
                return;
            switch (me->GetEntry())
            {
            case BOSS_FELUDIUS:
                me->MonsterYell(SAY_KILL_FEL, 0, 0);
                DoPlaySoundToSet(me, SOU_KILL_FEL);
                break;
            case BOSS_IGNACIOUS:
                me->MonsterYell(SAY_KILL_IGN, 0, 0);
                DoPlaySoundToSet(me, SOU_KILL_IGN);
                break;
            case BOSS_ARION:
                me->MonsterYell(SAY_KILL_ARI, 0, 0);
                DoPlaySoundToSet(me, SOU_KILL_ARI);
                break;
            case BOSS_TERRASTRA:
                me->MonsterYell(SAY_KILL_TER, 0, 0);
                DoPlaySoundToSet(me, SOU_KILL_TER);
                break;
            default:
                break;
            }
            killtimer = 8000;
        }
 
        void JustSummoned(Creature* summon)
        {
            summon->setFaction(me->getFaction());
            summon->SetInCombatWithZone();
        }
 
    };
};
 
class npc_violent_cyclone : public CreatureScript
{
public: npc_violent_cyclone() : CreatureScript("npc_violent_cyclone") { }
 
    struct npc_violent_cycloneAI : public ScriptedAI
    {
        npc_violent_cycloneAI(Creature* c) : ScriptedAI(c)
        {
            me->SetReactState(REACT_PASSIVE);
        }
 
        uint32 checkTimer;
        int chase;
 
        void Reset()
        {
            me->SetSpeed(MOVE_WALK,   0.8f, true);
            me->SetSpeed(MOVE_RUN,    0.8f, true);
            me->SetSpeed(MOVE_FLIGHT, 0.8f, true);
 
            checkTimer = 100;
            chase      =   0;
 
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
            me->SetReactState(REACT_PASSIVE);
            //me->AddUnitMovementFlag(MOVEMENTFLAG_FLYING);
            //me->SetCanFly(true);
        }
 
        void CheckViolentCyclone(Unit *who)
        {
                        if (who->isAlive() && !who->HasAura(SPELL_VIOLENT_CYCLONE))
                                me->CastSpell(who, SPELL_VIOLENT_CYCLONE, true);
                }
 
        void UpdateAI(const uint32 diff)
        {
            if (checkTimer <= diff)
            {
                checkTimer = 1000;
                if(me->GetDistance(cyclone[chase]) < 5.0f)
                {
                    chase++;
                    if (chase==9)
                        chase=0;
                    me->GetMotionMaster()->MovePoint(0, cyclone[chase]);
                }
                std::list<Unit*> targets;
                        Trinity::AnyUnfriendlyUnitInObjectRangeCheck u_check(me, me, 5.0f);
                        Trinity::UnitListSearcher<Trinity::AnyUnfriendlyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                        me->VisitNearbyObject(5.0f, searcher);
                        for (std::list<Unit*>::const_iterator iter = targets.begin();iter != targets.end(); ++iter)
                {
                                CheckViolentCyclone(*iter);
                }
            }
            else
                checkTimer -= diff;
        }
       
    };
        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_violent_cycloneAI(creature);
        }
};
 
class npc_frozen_orb_council : public CreatureScript
{
public: npc_frozen_orb_council() : CreatureScript("npc_frozen_orb_council") { }
 
    struct npc_frozen_orb_councilAI : public ScriptedAI
    {
        npc_frozen_orb_councilAI(Creature* c) : ScriptedAI(c)
        {
            me->SetReactState(REACT_PASSIVE);
        }
 
        uint32 checkTimer;
        bool dying;
        float speed;
        Unit* chase;
        Unit* flamestrike;
 
        void Reset()
        {
            speed = 0.8f;
            me->SetSpeed(MOVE_WALK,   speed, true);
            me->SetSpeed(MOVE_RUN,    speed, true);
            me->SetSpeed(MOVE_FLIGHT, speed, true);
            chase = SelectTarget(SELECT_TARGET_RANDOM, -10);
            if (chase)
            {
                me->AddAura(SPELL_FROST_BEACON, chase);
                me->GetMotionMaster()->MoveChase(chase, 0, 0);
            }
            if (me->GetInstanceScript())
                flamestrike = ObjectAccessor::GetCreature(*me, me->GetInstanceScript()->GetData64(NPC_FLAMESTRIKE_COUNCIL));
            checkTimer = 100;
            dying = false;
 
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
            me->SetReactState(REACT_PASSIVE);
            //me->AddUnitMovementFlag(MOVEMENTFLAG_FLYING);
            //me->SetCanFly(true);
        }
 
        void UpdateAI(const uint32 diff)
        {
            if (checkTimer <= diff)
            {
                if (dying)
                    me->DespawnOrUnsummon();
                else if (!chase)
                    chase = SelectTarget(SELECT_TARGET_RANDOM, -10);
                if (!flamestrike && me->GetInstanceScript())
                    flamestrike = ObjectAccessor::GetCreature(*me, me->GetInstanceScript()->GetData64(NPC_FLAMESTRIKE_COUNCIL));
                me->SetSpeed(MOVE_WALK,   speed, true);
                me->SetSpeed(MOVE_RUN,    speed, true);
                me->SetSpeed(MOVE_FLIGHT, speed, true);
                speed =  speed * 1.08;
                checkTimer = 1000;
                if(me->GetDistance(flamestrike) < 6.0f)
                {
                    me->DespawnOrUnsummon();
                    if (flamestrike && flamestrike->ToCreature())
                        flamestrike->ToCreature()->DespawnOrUnsummon();
                }
                if(me->GetDistance(chase) < 5.0f)
                {
                    me->CastSpell(me, SPELL_FROZEN_ORB_GLACIATE, false);
                    dying=true;
                }
               
               
            }
            else
                checkTimer -= diff;
        }
       
    };
        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_frozen_orb_councilAI(creature);
        }
};
 
class npc_gravity_well_council : public CreatureScript
{
public: npc_gravity_well_council() : CreatureScript("npc_gravity_well_council") { }
 
    struct npc_gravity_well_councilAI : public ScriptedAI
    {
        npc_gravity_well_councilAI(Creature* c) : ScriptedAI(c)
        {
            me->SetReactState(REACT_PASSIVE);
        }
 
        uint32 checkTimer;
        int chase;
 
        void Reset()
        {
            checkTimer = 100;
            chase      =   0;
            me->AddAura(83579, me);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
            me->SetReactState(REACT_PASSIVE);
            //me->AddUnitMovementFlag(MOVEMENTFLAG_FLYING);
            //me->SetCanFly(true);
        }
 
        void Checkgravitywell(Unit *who)
        {
            if (who->isAlive() && !who->HasAura(SPELL_GROUNDED))
            {
                                me->CastSpell(who, SPELL_GROUNDED, true);
                me->CastSpell(who, SPELL_MAGNETIC_PULL, true);
            }
        }
 
        void UpdateAI(const uint32 diff)
        {
            if (checkTimer <= diff)
            {
                checkTimer = 1000;
                std::list<Unit*> targets;

                Trinity::AnyUnfriendlyUnitInObjectRangeCheck u_check(me, me, 5.0f);
                Trinity::UnitListSearcher<Trinity::AnyUnfriendlyUnitInObjectRangeCheck> searcher(me, targets, u_check);
                me->VisitNearbyObject(5.0f, searcher);

                for (std::list<Unit*>::const_iterator iter = targets.begin();iter != targets.end(); ++iter)
                    Checkgravitywell(*iter);
            }
            else
                checkTimer -= diff;
        }
       
    };
        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_gravity_well_councilAI(creature);
        }
};
 
class npc_water_bomb: public CreatureScript
{
public: npc_water_bomb() : CreatureScript("npc_water_bomb") {}
 
    struct npc_water_bombAI: public ScriptedAI
    {
        npc_water_bombAI(Creature *c) :ScriptedAI(c) {}
 
        float distanza;
        uint32 timer;
        uint32 death;
        Unit* feludius;
 
        void InitializeAI()
        {
            death = 5000;
            feludius = me->GetOwner();
            me->setFaction(feludius->getFaction());
            distanza = me->GetDistance2d(feludius);
            if (distanza >10.0f) distanza=10.0f;
            timer = uint32((distanza - 10) * 50 + 500);
            feludius->CastSpell(me, SPELL_WATER_BOMB_VISUAL, true);
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
 
        }
 
        void UpdateAI(const uint32 diff)
        {
            if (death <=diff)
                me->DespawnOrUnsummon();
            else
                death -=diff;

            if (timer <= diff)
            {
                me->CastSpell(me, SPELL_WATER_BOMB_EXPLO, true);
            }
            else
                timer -= diff;
        }
    };
 
    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_water_bombAI(pCreature);
    }
};
 
class npc_lava_seed: public CreatureScript
{
public: npc_lava_seed() : CreatureScript("npc_lava_seed") {}
 
    struct npc_lava_seedAI: public ScriptedAI
    {
        npc_lava_seedAI(Creature *c) :ScriptedAI(c) {}
 
        uint32 timer;
        uint32 death;
        Unit* monstrosity;
 
                void InitializeAI()
        {
            death = 8000;
            monstrosity = me->GetOwner();
            me->setFaction(monstrosity->getFaction());
            timer = 5000;
            me->AddAura(SPELL_LAVA_SEED_AURA, me);
                        me->SetReactState(REACT_PASSIVE);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetUnitMovementFlags(MOVEMENTFLAG_FLYING);
            me->SetSpeed(MOVE_WALK,   4.0f, true);
            me->SetSpeed(MOVE_RUN,    4.0f, true);
            me->SetSpeed(MOVE_FLIGHT, 4.0f, true);
            me->GetMotionMaster()->MovePoint(0,me->GetPositionX(),me->GetPositionY(), me->GetPositionZ()-35);
                }
 
                void UpdateAI(const uint32 diff)
        {
            if (death <=diff)
                me->DespawnOrUnsummon();
            else
                death -=diff;
                        if (timer <= diff)
            {
                me->CastSpell(me, SPELL_LAVA_PLUME, false);
            }
            else
                                timer -= diff;
                }
        };
 
        CreatureAI* GetAI(Creature* pCreature) const
    {
                return new npc_lava_seedAI(pCreature);
        }
};
 
class npc_inferno_rush: public CreatureScript {
public: npc_inferno_rush() : CreatureScript("npc_inferno_rush") {}
 
        struct npc_inferno_rushAI: public ScriptedAI
    {
                npc_inferno_rushAI(Creature *c) :ScriptedAI(c) {}
 
                bool Isready;
                uint32 timer;
        Unit* igna;
 
                void InitializeAI()
        {
            Isready = false;
            timer = 250;
            igna = me->GetOwner();
            me->setFaction(igna->getFaction());
                        me->SetReactState(REACT_PASSIVE);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                }
 
                void UpdateAI(const uint32 diff)
        {
                        if (timer <= diff)
            {
                me->AddAura(88579, me);
                if (!igna)
                    return;
                me->SetFacingToObject(igna);
                float ori = me->GetOrientation();
                me->NearTeleportTo(me->GetPositionX()+ 6*cos(ori), me->GetPositionY()+ 6*sin(ori), me->GetPositionZ(), me->GetOrientation());
                if(me->GetDistance2d(igna) > 6.0f)
                {
                    igna->SummonCreature(NPC_INFERNO_RUSH, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation());
                }
            }
            else
                                timer -= diff;
                }
        };
 
        CreatureAI* GetAI(Creature* pCreature) const
    {
                return new npc_inferno_rushAI(pCreature);
        }
};
 
class npc_flamestrike: public CreatureScript {
public: npc_flamestrike() : CreatureScript("npc_flamestrike") {}
 
        struct npc_flamestrikeAI: public ScriptedAI
    {
                npc_flamestrikeAI(Creature *c) :ScriptedAI(c) {}
 
                uint32 timer;
 
                void InitializeAI()
        {
            timer = 3000;
                        me->SetReactState(REACT_PASSIVE);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->AddAura(SPELL_FLAMESTRIKE_VISUAL, me);
                }
 
                void UpdateAI(const uint32 diff)
        {
                        if (timer <= diff)
            {
                me->CastSpell(me, SPELL_FLAMESTRIKE, true);
                me->RemoveAura(SPELL_FLAMESTRIKE_VISUAL);
            }
            else
                                timer -= diff;
                }
        };
 
        CreatureAI* GetAI(Creature* pCreature) const
    {
                return new npc_flamestrikeAI(pCreature);
        }
};
 
class npc_liquid_ice: public CreatureScript {
public: npc_liquid_ice() : CreatureScript("npc_liquid_ice") {}
 
        struct npc_liquid_iceAI: public ScriptedAI
    {
                npc_liquid_iceAI(Creature *c) :ScriptedAI(c) {}
 
                void InitializeAI()
        {
            me->AddAura(SPELL_LIQUID_ICE, me);
                        me->SetReactState(REACT_PASSIVE);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                }
        };
 
        CreatureAI* GetAI(Creature* pCreature) const
    {
                return new npc_liquid_iceAI(pCreature);
        }
};
 
class spell_glaciate : public SpellScriptLoader
{
    public: spell_glaciate() : SpellScriptLoader("spell_glaciate") { }
 
        class spell_glaciate_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_glaciate_SpellScript);
 
            void HandleGlaciate()
            {
                Unit* target = GetTargetUnit();
                Unit* caster = GetCaster();  
                if (!target || !caster)
                    return;
                if (target->HasAura(SPELL_WATERLOGGED))
                    caster->AddAura(SPELL_FROZEN, target);
            }
 
            void GlaciateDamage()
            {
                Unit* target = GetTargetUnit();
                Unit* caster = GetCaster();  
                if (!target || !caster)
                    return;
                uint32 damage = GetHitDamage();
                float dist = target->GetDistance(caster);
                if (dist > 5.0f)
                    damage = uint32 (damage/(dist/3));
                SetHitDamage(damage);  
            }
 
            void Register()
            {
                AfterHit += SpellHitFn(spell_glaciate_SpellScript::HandleGlaciate);
                BeforeHit += SpellHitFn(spell_glaciate_SpellScript::GlaciateDamage);
            }
        };
 
        SpellScript* GetSpellScript() const
        {
            return new spell_glaciate_SpellScript();
        }
};
 
class spell_thundershock : public SpellScriptLoader
{
    public: spell_thundershock() : SpellScriptLoader("spell_thundershock") { }
 
        class spell_thundershock_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_thundershock_SpellScript);
 
            void ThundershockDamage()
            {
                Unit* target = GetTargetUnit();
                if (!target)
                    return;
                uint32 damage = GetHitDamage();
                if (target->HasAura(SPELL_GROUNDED))
                    damage = uint32 (damage/4);
                SetHitDamage(damage);  
            }
 
            void Register()
            {
                BeforeHit += SpellHitFn(spell_thundershock_SpellScript::ThundershockDamage);
            }
        };
 
        SpellScript* GetSpellScript() const
        {
            return new spell_thundershock_SpellScript();
        }
};
 
class spell_static_overload : public SpellScriptLoader
{
    public: spell_static_overload() : SpellScriptLoader("static_overload") { }
 
        class spell_static_overload_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_static_overload_SpellScript);
 
            void StaticOverloadDamage()
            {
                Unit* target = GetTargetUnit();
 
                if (!target)
                    return;
                uint32 damage = GetHitDamage();
                if (target->HasAura(SPELL_GRAVITY_CORE))
                {
                    target->GetAura(SPELL_GRAVITY_CORE)->Remove();
                    if (target->GetInstanceScript())
                        target->GetInstanceScript()->DoRemoveAurasDueToSpellOnPlayers(SPELL_STATIC_OVERLOAD);
                }
            }
 
            void Register()
            {
                BeforeHit += SpellHitFn(spell_static_overload_SpellScript::StaticOverloadDamage);
            }
        };
 
        SpellScript* GetSpellScript() const
        {
            return new spell_static_overload_SpellScript();
        }
};
 
class spell_quake : public SpellScriptLoader
{
    public: spell_quake() : SpellScriptLoader("spell_quake") { }
 
        class spell_quake_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_quake_SpellScript);
 
            void QuakeDamage()
            {
                Unit* target = GetTargetUnit();
                if (!target)
                    return;
                if (target->HasAura(SPELL_SWIRLING_WINDS))
                    SetHitDamage(0);  
            }
 
            void Register()
            {
                BeforeHit += SpellHitFn(spell_quake_SpellScript::QuakeDamage);
            }
        };
 
        SpellScript* GetSpellScript() const
        {
            return new spell_quake_SpellScript();
        }
};
 
class spell_rising_flames : public SpellScriptLoader
{
    public:
        spell_rising_flames() : SpellScriptLoader("spell_rising_flames") { }
 
        class spell_rising_flames_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_rising_flames_SpellScript);
 
            SpellCastResult CheckCast()
            {
                Unit* caster = GetCaster();  
                if (!caster)
                    return SPELL_FAILED_ERROR;

                if (!caster->GetAura(SPELL_RISING_FLAMES_BUFF))
                    caster->AddAura(SPELL_RISING_FLAMES_BUFF, caster);
                else
                {
                    Aura* buff =caster->GetAura(SPELL_RISING_FLAMES_BUFF);
                    buff->SetStackAmount(buff->GetStackAmount()+1);
                    buff->RefreshDuration();
                }
 
                return SPELL_CAST_OK;
            }
 
            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_rising_flames_SpellScript::CheckCast);
            }
           
        };
 
        SpellScript* GetSpellScript() const
        {
            return new spell_rising_flames_SpellScript();
        }
};
 
class spell_harden_skin : public SpellScriptLoader
{
   public:
       spell_harden_skin() : SpellScriptLoader("spell_harden_skin") { }
 
       class spell_harden_skin_AuraScript : public AuraScript
       {
           PrepareAuraScript(spell_harden_skin_AuraScript);
 
           void AfterRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
           {
               if (GetTargetApplication()->GetRemoveMode() != AURA_REMOVE_BY_ENEMY_SPELL)
                   return;
               if (!GetCaster())
                   return;
               Unit* caster = GetCaster();
               uint32 damage = 500000;
               if (this && this->GetAura() && this->GetAura()->GetEffect(EFFECT_1) )
                   damage = this->GetAura()->GetEffect(EFFECT_1)->GetAmount();
               caster->DealDamage(caster, damage);
           }
 
           void Absorb(AuraEffect* aurEff, DamageInfo & dmgInfo, uint32 & absorbAmount)
           {
               if (!dmgInfo.GetVictim() || !dmgInfo.GetAttacker())
                   return;
               Unit* caster = dmgInfo.GetVictim();
               Unit* who = dmgInfo.GetAttacker();
               uint32 damage = absorbAmount/2;
               caster->SetHealth(caster->GetHealth()-damage);
               if (caster->GetAI())
                   caster->GetAI()->DamageTaken(who, damage);
           }
 
           void Register()
           {
               OnEffectAbsorb += AuraEffectAbsorbFn(spell_harden_skin_AuraScript::Absorb, EFFECT_1);
               AfterEffectRemove += AuraEffectRemoveFn(spell_harden_skin_AuraScript::AfterRemove, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB, AURA_EFFECT_HANDLE_REAL);
           }
       };
 
       AuraScript* GetAuraScript() const
       {
           return new spell_harden_skin_AuraScript();
       }
};
 
void AddSC_boss_ascendant_council()
{
    new boss_elementium_monstrosity();
    new boss_ascendants();
    new npc_violent_cyclone();
    new npc_frozen_orb_council();
    new npc_gravity_well_council();
    new npc_water_bomb();
    new npc_lava_seed();
    new npc_inferno_rush();
    new npc_flamestrike();
    new npc_liquid_ice();
    new spell_glaciate();
    new spell_thundershock();
    new spell_static_overload();
    new spell_quake();
    new spell_rising_flames();
    new spell_harden_skin();
}