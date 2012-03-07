-- Looks like a Tauren Pirate to me
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES ('2663', '59148');
UPDATE `quest_template` SET `SrcItemId`='59147', `SrcItemCount`='1' WHERE (`entry`='26630');
UPDATE `quest_template` SET `Objectives`='Obtain a Cow Head and an Oversized Pirate Hat (sold by Narkk), then bring them back to Fleet Master Seahorn.' WHERE (`entry`='26630');
