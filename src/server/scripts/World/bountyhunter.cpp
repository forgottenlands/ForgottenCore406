/*-----------------------------------------*/
/*-------------BOUNTY HUNTARD!-------------*/
/*-----------------------------------------*/

#include "ScriptPCH.h"
#include <map>
 
using namespace std;
 
#define MSG_PLACE_BOUNTY "Voglio inserire una taglia [10g]"
 
/* Bounty Misc */
void DoSendMessageToWorld(int msg, string name, string playerName)
{
        ostringstream ss;
        if (msg == 1)
        {
                ss << "|cffFF0000Una taglia e' stata messa sulla testa di "
                        << name.c_str()
                        << "!!!|r";
        }
        else if (msg == 2)
        {
                ss << "|cffFFA500Aumenta la taglia su "
                        << name.c_str()
                        << "!|r";
        }
        else if (msg == 3)
        {
                ss << "|cffFF0000 "
                        << playerName.c_str()
                        << " ha ucciso "
                        << name.c_str()
                        << ", che aveva una taglia sulla sua testa!";
        }
        sWorld->SendGlobalText(ss.str().c_str(), NULL);
}
 
/* Bounty Enumeration */
enum eGold
{
        BOUNTY_AMOUNT_GOLD = 100000
};
 
/* Bounty Map */
struct BountyInfo
{
        string name;
        string bounty;
        uint64 hunted;
        uint64 hunter;
        uint32 gold;
};
 
map<uint64, BountyInfo> Bounty;
 
class npc_b_hunter : public CreatureScript
{
    public:
                npc_b_hunter() : CreatureScript("npc_bounty_hunter") { }
 
                bool OnGossipHello(Player * player, Creature * creature)
                {
                        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_BATTLE, MSG_PLACE_BOUNTY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1, "", 0, true);
                        if(!Bounty.empty())
                                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Mostra la lista taglie", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Non importa..", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
                        player->SEND_GOSSIP_MENU(1, creature->GetGUID());
                        return true;
                }
 
                bool OnGossipSelect(Player * player, Creature * creature, uint32 sender, uint32 actions)
                {
                        player->PlayerTalkClass->ClearMenus();
                        if(sender != GOSSIP_SENDER_MAIN)
                                return false;
 
                        switch(actions)
                        {

                           case GOSSIP_ACTION_INFO_DEF+2:
                                   for(map<uint64, BountyInfo>::const_iterator i = Bounty.begin(); i != Bounty.end(); ++i)
                                           ChatHandler(player).PSendSysMessage("Taglie attuali: \n Name: %s, Valore: %u, Taglia: %s", i->second.name.c_str(), i->second.gold, i->second.bounty.c_str());
                                   player->PlayerTalkClass->CloseGossip();
                                   break;
 
                           case GOSSIP_ACTION_INFO_DEF+4:
                                   player->PlayerTalkClass->CloseGossip();
                                   break;
                        }
                        return true;
                }
 
                bool OnGossipSelectCode(Player* player, Creature* creature, uint32 sender, uint32 action, const char* code)
                {
                        player->PlayerTalkClass->ClearMenus();
                        if(sender != GOSSIP_SENDER_MAIN)
                                return false;
 
                        string name = code;
                        Player * hunted = NULL;
											
                        switch(action)
                        {
                           case GOSSIP_ACTION_INFO_DEF+1:
							       
                                   for(map<uint64, BountyInfo>::const_iterator i = Bounty.begin(); i != Bounty.end(); ++i)
                                   {
                                           if(i->second.bounty == player->GetName())
                                           {
                                                   ChatHandler(player).SendSysMessage("Hai gia inserito una taglia!!");
                                                   player->PlayerTalkClass->CloseGossip();
                                                   return false;
                                           }
 
                                           if(i->second.hunted == player->GetGUID())
                                           {
                                                   ChatHandler(player).SendSysMessage("Non puoi inserire una taglia.. sei TU un most wanted!");
                                                   player->PlayerTalkClass->CloseGossip();
                                                   return false;
                                           }
 
                                           if(i->second.hunted == hunted->GetGUID())
                                           {
                                                   Bounty[i->second.hunter].gold += BOUNTY_AMOUNT_GOLD;
                                                   ChatHandler(player).PSendSysMessage("Attenzione, %s ha gia una taglia sulla sua testa.. Quindi il suo valore e' aumentato!", i->second.name.c_str());
                                                   DoSendMessageToWorld(2, i->second.name, "");
                                                   player->PlayerTalkClass->CloseGossip();
                                                   return false;
                                           }
                                   }
                                   
                                   if(player->GetMoney() >= BOUNTY_AMOUNT_GOLD)
                                   {
                                           //player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_BATTLE, MSG_PLACE_BOUNTY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1, "", 0, true);
                                           player->ModifyMoney(-BOUNTY_AMOUNT_GOLD);
                                   }
                                   else
                                   {
                                           ChatHandler(player).SendSysMessage("Non hai abbastanza oro!");
                                           player->PlayerTalkClass->CloseGossip();
                                           return false;
                                   }
                                   if(!name.empty())
                                           hunted = sObjectAccessor->FindPlayerByName(name.c_str());
 
                                   if(name == player->GetName())
                                   {
                                           ChatHandler(player).SendSysMessage("Non puoi mettere una taglia su te stesso!");
                                           player->PlayerTalkClass->CloseGossip();
                                           return false;
                                   }
 
                                   if(!hunted)
                                   {
                                           ChatHandler(player).PSendSysMessage("Il giocatore %s non e' online.", name.c_str());
										   player->ModifyMoney(BOUNTY_AMOUNT_GOLD);
                                           player->PlayerTalkClass->CloseGossip();
                                           return false;
                                   }
                                   Bounty[hunted->GetGUID()].hunted = hunted->GetGUID();
                                   Bounty[hunted->GetGUID()].hunter = player->GetGUID();
                                   Bounty[hunted->GetGUID()].gold = BOUNTY_AMOUNT_GOLD;
                                   Bounty[hunted->GetGUID()].name = name.c_str();
                                   Bounty[hunted->GetGUID()].bounty = player->GetName();
                                   ChatHandler(player).PSendSysMessage("|cffFF0000Taglia inserita per %s!|r", name.c_str());
                                   player->Whisper("Ho messo una taglia su di te!", LANG_UNIVERSAL, hunted->GetGUID());
                                   DoSendMessageToWorld(1, name.c_str(), "");
								   player->PlayerTalkClass->CloseGossip();
                                   break;
                        }
                        hunted = NULL;
                        name = "";
                        return false;
						
                }
};
 
class bounty_kills : public PlayerScript
{
   public:
           bounty_kills() : PlayerScript("bounty_kills") { }
 
           void OnPVPKill(Player * killer, Player * victim)
           {
			   if(killer){
				   if(victim){

					   if(killer->GetGUID() == victim->GetGUID() || Bounty.empty())
							   return;

					   for(map<uint64, BountyInfo>::const_iterator i = Bounty.begin(); i != Bounty.end(); ++i)
					   {
							   if(i->second.hunted == victim->GetGUID())
							   {
									   killer->ModifyMoney(Bounty[victim->GetGUID()].gold);
									   //ChatHandler(killer).PSendSysMessage("E' stato aggiunto %u oro per la tua uccisione!", Bounty[victim->GetGUID()].gold);
									   Bounty.erase(victim->GetGUID());
									   DoSendMessageToWorld(3, victim->GetName(), killer->GetName());
							   }
					   }
				   }
			   }
           }
};
 
void AddSC_bounties_hunters()
{
        new npc_b_hunter;
        new bounty_kills;
}