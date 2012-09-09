#include "ScriptMgr.h"
#include "ObjectMgr.h"

#define MSG_GOSSIP_ADDITEM   "Completami le Quest Bugghe"
#define MSG_GOSSIP_CLOSE	 "Chiudi"

static QueryResult ResultQuest;

class npc_questcompleter : public CreatureScript
{
public:
	npc_questcompleter() : CreatureScript("npc_questcompleter") { }
	
	bool OnGossipHello(Player* pPlayer, Creature* creature)
	{
		pPlayer->SaveToDB();
		ResultQuest = CharacterDatabase.Query("SELECT Entry FROM quest_completer WHERE Enabled=1");  //Carico in ResultQuest tutte le quest disponibili bugghe
		if (ResultQuest)
		{
			bool thereis = false;
			uint32 lunghezza = ResultQuest->GetRowCount();
			for(uint32 i=0;i<lunghezza;i++)
			{
				uint32 Appoggio = ResultQuest->Fetch()->GetUInt32();

				Quest const* quest = sObjectMgr->GetQuestTemplate(Appoggio);
				if (quest && pPlayer->GetQuestStatus(Appoggio) == QUEST_STATUS_INCOMPLETE)
				{
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, quest->GetTitle(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+Appoggio);
					thereis = true;
				}
				
				ResultQuest->NextRow();  //mi sposto sulla quest successiva, se esiste
			}
			
			if(thereis)
				pPlayer->SEND_GOSSIP_MENU(1300000, creature->GetGUID());
			else
				pPlayer->SEND_GOSSIP_MENU(1300001, creature->GetGUID());
		}
		
		else
			pPlayer->SEND_GOSSIP_MENU(1300002, creature->GetGUID());
			
		return true;
	}
	bool OnGossipSelect(Player* pPlayer, Creature* creature, uint32 uiSender, uint32 uiAction)
	{
         if (uiSender != GOSSIP_SENDER_MAIN)
            return true;
		
		uint32 entry = uiAction - GOSSIP_ACTION_INFO_DEF;
		
		Quest const* quest = sObjectMgr->GetQuestTemplate(entry);

        // If pPlayer doesn't have the quest
        if (!quest || pPlayer->GetQuestStatus(entry) == QUEST_STATUS_NONE)
        {
            return false;
        }

        // Add quest items for quests that require items
        for (uint8 x = 0; x < QUEST_ITEM_OBJECTIVES_COUNT; ++x)
        {
            uint32 id = quest->ReqItemId[x];
            uint32 count = quest->ReqItemCount[x];
            if (!id || !count)
                continue;

            uint32 curItemCount = pPlayer->GetItemCount(id, true);

            ItemPosCountVec dest;
            uint8 msg = pPlayer->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, id, count-curItemCount);
            if (msg == EQUIP_ERR_OK)
            {
                Item* item = pPlayer->StoreNewItem(dest, id, true);
                pPlayer->SendNewItem(item, count-curItemCount, true, false);
            }
        }

        // All creature/GO slain/casted (not required, but otherwise it will display "Creature slain 0/10")
        for (uint8 i = 0; i < QUEST_OBJECTIVES_COUNT; ++i)
        {
			int32 creature = quest->ReqCreatureOrGOId[i];
			uint32 creaturecount = quest->ReqCreatureOrGOCount[i];

			if (uint32 spell_id = quest->ReqSpell[i])
            {
                for (uint16 z = 0; z < creaturecount; ++z)
                    pPlayer->CastedCreatureOrGO(creature, 0, spell_id);
            }
            else if (creature > 0)
            {
                if (CreatureInfo const* cInfo = sObjectMgr->GetCreatureTemplate(creature))
                    for (uint16 z = 0; z < creaturecount; ++z)
                        pPlayer->KilledMonster(cInfo, 0);
            }
            else if (creature < 0)
            {
                for (uint16 z = 0; z < creaturecount; ++z)
                    pPlayer->CastedCreatureOrGO(creature, 0, 0);
            }
        }

        // If the quest requires reputation to complete
        if (uint32 repFaction = quest->GetRepObjectiveFaction())
        {
            uint32 repValue = quest->GetRepObjectiveValue();
            uint32 curRep = pPlayer->GetReputationMgr().GetReputation(repFaction);
            if (curRep < repValue)
                if (FactionEntry const* factionEntry = sFactionStore.LookupEntry(repFaction))
                    pPlayer->GetReputationMgr().SetReputation(factionEntry, repValue);
        }

        // If the quest requires a SECOND reputation to complete
        if (uint32 repFaction = quest->GetRepObjectiveFaction2())
        {
            uint32 repValue2 = quest->GetRepObjectiveValue2();
            uint32 curRep = pPlayer->GetReputationMgr().GetReputation(repFaction);
            if (curRep < repValue2)
                if (FactionEntry const* factionEntry = sFactionStore.LookupEntry(repFaction))
                    pPlayer->GetReputationMgr().SetReputation(factionEntry, repValue2);
        }

        // If the quest requires money
        int32 ReqOrRewMoney = quest->GetRewOrReqMoney();
        if (ReqOrRewMoney < 0)
            pPlayer->ModifyMoney(-ReqOrRewMoney);

        pPlayer->CompleteQuest(entry);
		CharacterDatabase.PExecute("INSERT INTO quest_completer_logs (guidPlayer, entryQuest, time) VALUES(%u, %u, NOW())", pPlayer->GetGUID(), entry);
		pPlayer->SaveToDB();
        pPlayer->PlayerTalkClass->CloseGossip();
		return true;
	}
};

void AddSC_npc_questcompleter()
{
	new npc_questcompleter;
}