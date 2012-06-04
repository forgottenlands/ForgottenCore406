-- Fix Leone e Scorpione di gilda

-- Richiesta reputazione delle 2 mount
UPDATE `item_template` SET `RequiredReputationFaction`=1168, `RequiredReputationRank`=7 WHERE (`entry`=67107);
UPDATE `item_template` SET `RequiredReputationFaction`=1168, `RequiredReputationRank`=7 WHERE (`entry`=62298);

-- Inserimento Reins of the Kor'kron Annihilator
INSERT INTO `npc_vendor` (`entry`,`item`,`ExtendedCost`) VALUES (46572,67107,0);
INSERT INTO `npc_vendor` (`entry`,`item`,`ExtendedCost`) VALUES (51496,67107,0);
INSERT INTO `npc_vendor` (`entry`,`item`,`ExtendedCost`) VALUES (51512,67107,0);
INSERT INTO `npc_vendor` (`entry`,`item`,`ExtendedCost`) VALUES (51503,67107,0);
INSERT INTO `npc_vendor` (`entry`,`item`,`ExtendedCost`) VALUES (52268,67107,0);

-- Inserimento Reins of the Golden King
INSERT INTO `npc_vendor` (`entry`,`item`,`ExtendedCost`) VALUES (51512,62298,0);
INSERT INTO `npc_vendor` (`entry`,`item`,`ExtendedCost`) VALUES (52268,62298,0);
INSERT INTO `npc_vendor` (`entry`,`item`,`ExtendedCost`) VALUES (46602,62298,0);
INSERT INTO `npc_vendor` (`entry`,`item`,`ExtendedCost`) VALUES (51495,62298,0);
INSERT INTO `npc_vendor` (`entry`,`item`,`ExtendedCost`) VALUES (51504,62298,0);
