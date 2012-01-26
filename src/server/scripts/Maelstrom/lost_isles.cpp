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

void AddSC_lost_isles()
{
    new  npc_gyrochoppa();
}