/*-----------------------------------------*/
/*-------------BOUNTY HUNTARD!-------------*/
/*-----------------------------------------*/

#include "ScriptPCH.h"
#include <map>
 
using namespace std;
 
#define MSG_PLACE_BOUNTY "Voglio inserire una taglia! [10g]"
static QueryResult BountyGoldQuery;
static QueryResult EnableQuery;
static QueryResult EnableHuntedQuery;
static QueryResult EnableDualBox;

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
					    //Primo gossip: mi fa inserire la bounty (rimanda al GossipSelectCode piu sotto)
                        EnableQuery = CharacterDatabase.Query("SELECT valore FROM bounty_options WHERE opzione=1");
                        uint32 enable = EnableQuery->Fetch()->GetUInt32();
                        if(enable == 1){
                            if(player->getLevel()==85){
                                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_BATTLE, MSG_PLACE_BOUNTY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1, "", 0, true);
                                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Cancella la taglia inserita", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
                            }
                        }
                        //Se la bounty non è vuota, faccio mostrare l'opzione per vedere la lista bounties (opzione 2)
						if(!Bounty.empty())
                                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Mostra la lista taglie", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                        //Opzione di uscita (opzione 4)
						player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Non importa..", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
                        //Abilito il menù
						player->SEND_GOSSIP_MENU(1, creature->GetGUID());
                        return true;
                }
 
                bool OnGossipSelect(Player * player, Creature * creature, uint32 sender, uint32 actions)
                {
						//Verifico di stare parlando con l'npc giusto
                        player->PlayerTalkClass->ClearMenus();
                        if(sender != GOSSIP_SENDER_MAIN)
                                return false;
                        int diobono = 0;
                        switch(actions)
                        {
						   //mostro la lista bounties al player (opzione 2)
                          case GOSSIP_ACTION_INFO_DEF+2:
                               ChatHandler(player).PSendSysMessage("Taglie attuali:");
                                   for(map<uint64, BountyInfo>::const_iterator i = Bounty.begin(); i != Bounty.end(); ++i)
                                           ChatHandler(player).PSendSysMessage("\n Nome: %s, Ricercato da: %s", i->second.name.c_str(), i->second.bounty.c_str());
                                   player->PlayerTalkClass->CloseGossip();
                                   break;
                           //cerco il nome da me inserito e lo deletto
                          case GOSSIP_ACTION_INFO_DEF+4:
                                diobono = 0;
                                for(map<uint64, BountyInfo>::const_iterator i = Bounty.begin(); i != Bounty.end(); ++i){
                                    if(i->second.hunter == player->GetGUID()){
                                        Bounty.erase(i->second.hunted);
                                        ChatHandler(player).PSendSysMessage("Taglia cancellata!");
                                        diobono = 1;
                                    }
                                }
                                if (diobono ==0){
                                    ChatHandler(player).PSendSysMessage("Non hai inserito nessuna taglia!");
                                }
                                player->PlayerTalkClass->CloseGossip();
                                break;
						   //uscita dal gossip (opzione 4)
                           case GOSSIP_ACTION_INFO_DEF+5:
                                   player->PlayerTalkClass->CloseGossip();
                                   break;
                        }
                        return true;
                }
 
                bool OnGossipSelectCode(Player* player, Creature* creature, uint32 sender, uint32 action, const char* code)
                {
                        //Verifico di stare parlando con l'npc giusto
                        player->PlayerTalkClass->ClearMenus();
                        if(sender != GOSSIP_SENDER_MAIN)
                                return false;
                        
                        //Salvo il nome inserito dal player
                        string name = code;
                        //Inizializzo il puntatore al personaggio "cacciato"
                        Player * hunted = NULL;
											
                        switch(action)
                        {
                           //Azione 1, post inserimento nome
                           case GOSSIP_ACTION_INFO_DEF+1:

                                   //vado a pescare sul db l'opzione 2, cioe il prezzo in gold del bounty hunter
                                   BountyGoldQuery = CharacterDatabase.Query("SELECT valore FROM bounty_options WHERE opzione=2");
                                   EnableHuntedQuery = CharacterDatabase.Query("SELECT valore FROM bounty_options WHERE opzione=3");
                                   EnableDualBox = CharacterDatabase.Query("SELECT valore FROM bounty_options WHERE opzione=4");
                                   uint32 enablehunted = EnableHuntedQuery->Fetch()->GetUInt32();
                                   uint32 bountygold = BountyGoldQuery->Fetch()->GetUInt32();
                                   uint32 enabledualbox = EnableDualBox->Fetch()->GetUInt32();
                                   //non hai abbastanza cash, non puoi far partire la taglia
                                   if(player->GetMoney() < bountygold)
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
                                           player->PlayerTalkClass->CloseGossip();
                                           return false;
                                   }

                                   if(hunted->GetSession()){
                                       if(player->GetSession()){
                                           if((hunted->GetSession()->GetRemoteAddress() == player->GetSession()->GetRemoteAddress()) && (enabledualbox == 0)){
                                           ChatHandler(player).PSendSysMessage("Perche dualboxi figliolo? Sei stato loggato non riprovarci");
                                           CharacterDatabase.PExecute("INSERT INTO bounty_kills (killer, victim, date) VALUES(%u, 0, NOW())", player->GetGUID());  
                                           player->PlayerTalkClass->CloseGossip();
                                           return false;
                                           }
                                       }
                                   }

                                   //scorro l'array delle taglie
                                   for(map<uint64, BountyInfo>::const_iterator i = Bounty.begin(); i != Bounty.end(); ++i)
                                   {

                                           //taglia gia inserita
                                           if(i->second.bounty == player->GetName())
                                           {
                                                   ChatHandler(player).SendSysMessage("Hai gia inserito una taglia!!");
                                                   player->PlayerTalkClass->CloseGossip();
                                                   return false;
                                           }
                                           //sei tu un most wanted, non puoi fare il cacciatore di taglie (disabilitabile con la enablehunted a 1)
                                           if((i->second.hunted == player->GetGUID()) && (enablehunted==0))
                                           {
                                                   ChatHandler(player).SendSysMessage("Non puoi inserire una taglia.. sei TU un most wanted!");
                                                   player->PlayerTalkClass->CloseGossip();
                                                   return false;
                                           }
                                           //Personaggio gia sotto bounty
                                           if(i->second.hunted == hunted->GetGUID())
                                           {
                                                   ChatHandler(player).PSendSysMessage("Attenzione, %s ha gia una taglia sulla sua testa... dagli la caccia!", i->second.name.c_str());
                                                   player->PlayerTalkClass->CloseGossip();
                                                   return false;
                                           }
                                   }
                                   
                                   // CREO LA BOUNTY
                                   // Levo il cash al player che crea la bounty
								   player->ModifyMoney(-(bountygold));
                                   //ASSEGNO NELL'ARRAY DELLE BOUNTY, I PARAMETRI PER LA NUOVA BOUNTY
                                   Bounty[hunted->GetGUID()].hunted = hunted->GetGUID();
                                   Bounty[hunted->GetGUID()].hunter = player->GetGUID();
                                   Bounty[hunted->GetGUID()].gold = bountygold;
                                   Bounty[hunted->GetGUID()].name = name.c_str();
                                   Bounty[hunted->GetGUID()].bounty = player->GetName();
                                   // Avviso il mondo che la caccia è iniziata
                                   ChatHandler(player).PSendSysMessage("|cffFF0000Taglia inserita per %s!|r", name.c_str());
                                   ChatHandler(hunted).PSendSysMessage("Attenzione, %s ha messo una taglia su di te!", player->GetName());
                                   DoSendMessageToWorld(1, name.c_str(), "");
								   player->PlayerTalkClass->CloseGossip();
                                   break;
                        }
                        //per finire mi riporto alla condizione di partenza
                        hunted = NULL;
                        name = "";
                        return false;
						
                }
};
 
class bounty_kills : public PlayerScript
{
   public:
           bounty_kills() : PlayerScript("bounty_kills") { }
 
		   //Questa funzione viene chiamata da Unit.cpp ogni qualvolta avviene una kill in pvp
           void OnPVPKill(Player * killer, Player * victim)
           {
			   //verifico esistenza del killer e il fatto che sia un normale player
			   if(killer && !(killer->isGameMaster())){
				   //verifico esistenza della victim e il fatto che sia un normale player
				   if(victim && !(victim->isGameMaster())){

					   //verifico esistenza della victim e il fatto che sia un normale player
					   if(killer->GetGUID() == victim->GetGUID() || Bounty.empty())
							   return;

					   //giro la lista delle bounty e vado a selezionare la bounty appena avvenuta
					   //(guardo la victim che mi viene passata come argomento)
					   for(map<uint64, BountyInfo>::const_iterator i = Bounty.begin(); i != Bounty.end(); ++i)
					   {
							   if(i->second.hunted == victim->GetGUID())
							   {
								       //mi salvo i guid di killer e vittima
								       uint64 killerguid = killer->GetGUID();
									   uint64 victimguid = victim->GetGUID();
									   //Salvo la kill sul database a fini statistici
								       CharacterDatabase.PExecute("INSERT INTO bounty_kills (killer, victim, date) VALUES(%u, %u, NOW())", killerguid, victimguid);  
									   //Do' i soldi al killer
									   killer->ModifyMoney(Bounty[victim->GetGUID()].gold);
									   //Cancello la entry per questa bounty
									   Bounty.erase(victim->GetGUID());
									   //Annuncio al mondo l'uccisione
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