/*
* Copyright (C) 2011 - 2012 ArkCORE <http://www.arkania.net/>
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License,  or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful,  but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not,  see <http://www.gnu.org/licenses/>.
*/

#include "ScriptPCH.h"

// Quest: (14242) Precious cargo
class npc_gyrochoppa: public CreatureScript 
{
    public:
	    npc_gyrochoppa() : CreatureScript("npc_gyrochoppa")
        { }

	bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) 
    {
		if (quest->GetQuestId() == 14242) 
        {
			player->CompleteQuest(14242);
            player->TeleportTo(648, 987.350f, 3824.70f, 12.431f, 1.24f);
		}
		return true;
	}
};

// Quest: (14242) Warchief Revenge
class npc_thrall_goblin: public CreatureScript 
{
    public:
	    npc_thrall_goblin() : CreatureScript("npc_thrall_goblin")
        { }

	bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (pPlayer->GetQuestStatus(14243) == QUEST_STATUS_COMPLETE)
        {
		    pPlayer->PrepareGossipMenu(pCreature);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Teleport me to Wild Overlook", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
            pPlayer->SEND_GOSSIP_MENU(1, pCreature->GetGUID());
            return true;
        }
        return false;
	}

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
       
        switch(uiAction)
        {
            case GOSSIP_ACTION_INFO_DEF:
                pPlayer->TeleportTo(648, 866.22f, 2779.55f, 114.20f, 6.233f, 0); 
                break;
        }
        pPlayer->PlayerTalkClass->CloseGossip();
        return true;
    }
};
            
void AddSC_lost_isles()
{
    new npc_gyrochoppa();
    new npc_thrall_goblin();
}