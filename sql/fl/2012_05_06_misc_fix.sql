-- FAERIE DRAGON
UPDATE `creature_template` SET `faction_A`='35', `faction_H`='35' WHERE (`entry`='39921');

-- FOULWEAD TOTEMIC e PATHFINDER
UPDATE `creature_template` SET `unit_flags`='0' WHERE (`entry`='3745');
UPDATE `creature_template` SET `unit_flags`='0' WHERE (`entry`='3750');

-- SHROUD OF COOPERATION (GORAM)
UPDATE `npc_vendor` SET `item`='63353' WHERE (`entry`='46572') AND (`item`='63352');

-- PACK HOBGOBLIN
UPDATE `creature_template` SET `npcflag`='131072' WHERE (`entry`='36613');

-- SILVERWIND REFUGE
UPDATE `creature` SET `spawntimesecs`='604800' WHERE (`guid`='266316');
UPDATE `creature` SET `spawntimesecs`='604800' WHERE (`guid`='32703');
UPDATE `creature` SET `spawntimesecs`='604800' WHERE (`guid`='32871');
UPDATE `creature` SET `spawntimesecs`='604800' WHERE (`guid`='34255');
UPDATE `creature` SET `spawntimesecs`='604800' WHERE (`guid`='32346');
UPDATE `creature` SET `spawntimesecs`='604800' WHERE (`guid`='32653');
UPDATE `creature` SET `spawntimesecs`='604800' WHERE (`guid`='32647');
UPDATE `creature` SET `spawntimesecs`='604800' WHERE (`guid`='32719');
UPDATE `creature` SET `spawntimesecs`='604800' WHERE (`guid`='32718');
UPDATE `creature` SET `spawntimesecs`='604800' WHERE (`guid`='32677');
UPDATE `creature` SET `spawntimesecs`='604800' WHERE (`guid`='33373');
UPDATE `creature` SET `spawntimesecs`='604800' WHERE (`guid`='33370');
UPDATE `creature` SET `spawntimesecs`='604800' WHERE (`guid`='32681');
UPDATE `creature` SET `spawntimesecs`='604800' WHERE (`guid`='265234');
UPDATE `creature` SET `spawntimesecs`='604800' WHERE (`guid`='265408');
UPDATE `creature` SET `spawntimesecs`='604800' WHERE (`guid`='266697');
UPDATE `creature` SET `spawntimesecs`='604800' WHERE (`guid`='263670');
UPDATE `creature` SET `spawntimesecs`='604800' WHERE (`guid`='267089');
UPDATE `creature` SET `spawntimesecs`='604800' WHERE (`guid`='266598');
UPDATE `creature` SET `spawntimesecs`='604800' WHERE (`guid`='267092');
UPDATE `creature` SET `spawntimesecs`='604800' WHERE (`guid`='264448');
UPDATE `creature` SET `spawntimesecs`='604800' WHERE (`guid`='266435');
UPDATE `creature` SET `spawntimesecs`='604800' WHERE (`guid`='265634');
UPDATE `creature` SET `spawntimesecs`='604800' WHERE (`guid`='266826');
UPDATE `creature` SET `spawntimesecs`='604800' WHERE (`guid`='266201');
UPDATE `creature` SET `spawntimesecs`='604800' WHERE (`guid`='33371');
UPDATE `creature` SET `spawntimesecs`='604800' WHERE (`guid`='264055');
UPDATE `creature` SET `spawntimesecs`='604800' WHERE (`guid`='266031');
UPDATE `creature` SET `spawntimesecs`='604800' WHERE (`guid`='264839');

UPDATE `creature` SET `DeathState`='1' WHERE (`guid`='264839');
UPDATE `creature` SET `DeathState`='1' WHERE (`guid`='266031');
UPDATE `creature` SET `DeathState`='1' WHERE (`guid`='264055');
UPDATE `creature` SET `DeathState`='1' WHERE (`guid`='33371');
UPDATE `creature` SET `DeathState`='1' WHERE (`guid`='266201');
UPDATE `creature` SET `DeathState`='1' WHERE (`guid`='266826');
UPDATE `creature` SET `DeathState`='1' WHERE (`guid`='265634');
UPDATE `creature` SET `DeathState`='1' WHERE (`guid`='266435');
UPDATE `creature` SET `DeathState`='1' WHERE (`guid`='264448');
UPDATE `creature` SET `DeathState`='1' WHERE (`guid`='267092');
UPDATE `creature` SET `DeathState`='1' WHERE (`guid`='266598');
UPDATE `creature` SET `DeathState`='1' WHERE (`guid`='267089');
UPDATE `creature` SET `DeathState`='1' WHERE (`guid`='263670');
UPDATE `creature` SET `DeathState`='1' WHERE (`guid`='266697');
UPDATE `creature` SET `DeathState`='1' WHERE (`guid`='266316');
UPDATE `creature` SET `DeathState`='1' WHERE (`guid`='32703');
UPDATE `creature` SET `DeathState`='1' WHERE (`guid`='32871');
UPDATE `creature` SET `DeathState`='1' WHERE (`guid`='34255');
UPDATE `creature` SET `DeathState`='1' WHERE (`guid`='32346');
UPDATE `creature` SET `DeathState`='1' WHERE (`guid`='32653');
UPDATE `creature` SET `DeathState`='1' WHERE (`guid`='32647');
UPDATE `creature` SET `DeathState`='1' WHERE (`guid`='32719');
UPDATE `creature` SET `DeathState`='1' WHERE (`guid`='32718');
UPDATE `creature` SET `DeathState`='1' WHERE (`guid`='32677');
UPDATE `creature` SET `DeathState`='1' WHERE (`guid`='33373');
UPDATE `creature` SET `DeathState`='1' WHERE (`guid`='33372');
UPDATE `creature` SET `DeathState`='1' WHERE (`guid`='33370');
UPDATE `creature` SET `DeathState`='1' WHERE (`guid`='32681');
UPDATE `creature` SET `DeathState`='1' WHERE (`guid`='265234');
UPDATE `creature` SET `DeathState`='1' WHERE (`guid`='265408');

-- QUEST NIBBLER! NO!
UPDATE `quest_template` SET `ReqCreatureOrGOId1`='0' WHERE (`entry`='25158');
UPDATE `quest_template` SET `ReqCreatureOrGOCount1`='0' WHERE (`entry`='25158');

-- DRUKMA (ORGRIMMAR PET HANDLER)
UPDATE `creature_template` SET `ScriptName`='npc_pet_trainer' WHERE (`entry`='47771');
UPDATE `creature_template` SET `flags_extra`='2' WHERE (`entry`='47771');

-- QUEST HORDE A PRESENT FOR LILA
UPDATE `quest_template` SET `ReqItemCount1`='3' WHERE (`entry`='25160');

-- JC VENDOR RECIPE Design: willfull ember topaz
UPDATE `item_template` SET `name`='Design: Willful Ember Topaz' WHERE (`entry`='68359');
UPDATE `item_template` SET `Quality`='3' WHERE (`entry`='68359');
UPDATE `item_template` SET `Flags`='4160' WHERE (`entry`='68359');
UPDATE `item_template` SET `FlagsExtra`='8192' WHERE (`entry`='68359');
UPDATE `item_template` SET `ItemLevel`='83', `RequiredSkill`='755', `RequiredSkillRank`='465' WHERE (`entry`='68359');
UPDATE `item_template` SET `spellid_1`='483', `spellcharges_1`='-1' WHERE (`entry`='68359');
UPDATE `item_template` SET `spellid_2`='95754', `spelltrigger_2`='6' WHERE (`entry`='68359');
UPDATE `item_template` SET `spellcharges_2`='0' WHERE (`entry`='68359');
UPDATE `item_template` SET `bonding`='1', `description`='Teaches you how to cut a Willful Ember Topaz.' WHERE (`entry`='68359');

-- JC STONE WILLFUL EMBER TOPAZ
UPDATE `item_template` SET `name`='Willful Ember Topaz' WHERE (`entry`='68356');
UPDATE `item_template` SET `Quality`='3', `FlagsExtra`='8192', `BuyPrice`='150000', `SellPrice`='37500', `ItemLevel`='85' WHERE (`entry`='68356');
UPDATE `item_template` SET `description`='Matches a Red or Yellow Socket.' WHERE (`entry`='68356');
UPDATE `item_template` SET `BagFamily`='512' WHERE (`entry`='68356');
UPDATE `item_template` SET `GemProperties`='1846' WHERE (`entry`='68356');

-- JC VENDOR RECIPE Design: lucent ember topaz
UPDATE `item_template` SET `name`='Design: Lucent Ember Topaz' WHERE (`entry`='68360');
UPDATE `item_template` SET `Quality`='3' WHERE (`entry`='68360');
UPDATE `item_template` SET `Flags`='4160' WHERE (`entry`='68360');
UPDATE `item_template` SET `FlagsExtra`='8192' WHERE (`entry`='68360');
UPDATE `item_template` SET `ItemLevel`='83', `RequiredSkill`='755', `RequiredSkillRank`='465' WHERE (`entry`='68360');
UPDATE `item_template` SET `spellid_1`='483', `spellcharges_1`='-1' WHERE (`entry`='68360');
UPDATE `item_template` SET `spellid_2`='95755', `spelltrigger_2`='6' WHERE (`entry`='68360');
UPDATE `item_template` SET `spellcharges_2`='0' WHERE (`entry`='68360');
UPDATE `item_template` SET `bonding`='1', `description`='Teaches you how to cut a Lucent Ember Topaz.' WHERE (`entry`='68360');

-- JC STONE LUCENT EMBER TOPAZ
UPDATE `item_template` SET `name`='Lucent Ember Topaz' WHERE (`entry`='68357');
UPDATE `item_template` SET `Quality`='3', `FlagsExtra`='8192', `BuyPrice`='150000', `SellPrice`='37500', `ItemLevel`='85' WHERE (`entry`='68357');
UPDATE `item_template` SET `description`='Matches a Red or Yellow Socket.' WHERE (`entry`='68357');
UPDATE `item_template` SET `BagFamily`='512' WHERE (`entry`='68357');
UPDATE `item_template` SET `GemProperties`='1847' WHERE (`entry`='68357');

-- JC VENDOR RECIPE Design: willfull ember topaz
UPDATE `item_template` SET `name`='Design: Resplendent Ember Topaz' WHERE (`entry`='68361');
UPDATE `item_template` SET `Quality`='3' WHERE (`entry`='68361');
UPDATE `item_template` SET `Flags`='4160' WHERE (`entry`='68361');
UPDATE `item_template` SET `FlagsExtra`='8192' WHERE (`entry`='68361');
UPDATE `item_template` SET `ItemLevel`='83', `RequiredSkill`='755', `RequiredSkillRank`='465' WHERE (`entry`='68361');
UPDATE `item_template` SET `spellid_1`='483', `spellcharges_1`='-1' WHERE (`entry`='68361');
UPDATE `item_template` SET `spellid_2`='95756', `spelltrigger_2`='6' WHERE (`entry`='68361');
UPDATE `item_template` SET `spellcharges_2`='0' WHERE (`entry`='68361');
UPDATE `item_template` SET `bonding`='1', `description`='Teaches you how to cut a Willful Ember Topaz.' WHERE (`entry`='68361');

-- JC STONE WILLFUL EMBER TOPAZ
UPDATE `item_template` SET `name`='Resplendent Ember Topaz' WHERE (`entry`='68358');
UPDATE `item_template` SET `Quality`='3', `FlagsExtra`='8192', `BuyPrice`='150000', `SellPrice`='37500', `ItemLevel`='85' WHERE (`entry`='68358');
UPDATE `item_template` SET `description`='Matches a Red or Yellow Socket.' WHERE (`entry`='68358');
UPDATE `item_template` SET `BagFamily`='512' WHERE (`entry`='68358');
UPDATE `item_template` SET `GemProperties`='1848' WHERE (`entry`='68358');

-- VOLATILE AIR
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`='38' WHERE (`entry`='40170') AND (`item`='52328');
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`='36' WHERE (`entry`='45917') AND (`item`='52328');
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`='37' WHERE (`entry`='45924') AND (`item`='52328');
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`='36' WHERE (`entry`='40033') AND (`item`='52328');
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`='35' WHERE (`entry`='45477') AND (`item`='52328');
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`='35' WHERE (`entry`='45912') AND (`item`='52328');
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`='35' WHERE (`entry`='45922') AND (`item`='52328');
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`='34' WHERE (`entry`='45919') AND (`item`='52328');
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`='33' WHERE (`entry`='45915') AND (`item`='52328');
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`='14' WHERE (`entry`='46328') AND (`item`='52328');
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`='13' WHERE (`entry`='47728') AND (`item`='52328');
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`='12' WHERE (`entry`='45755') AND (`item`='52328');
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`='11' WHERE (`entry`='47151') AND (`item`='52328');
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`='10' WHERE (`entry`='39844') AND (`item`='52328');
UPDATE `creature_loot_template` SET `maxcount`='3' WHERE (`entry`='40170') AND (`item`='52328');
UPDATE `creature_loot_template` SET `maxcount`='3' WHERE (`entry`='45917') AND (`item`='52328');
UPDATE `creature_loot_template` SET `maxcount`='3' WHERE (`entry`='45924') AND (`item`='52328');
UPDATE `creature_loot_template` SET `maxcount`='3' WHERE (`entry`='40033') AND (`item`='52328');
UPDATE `creature_loot_template` SET `maxcount`='3' WHERE (`entry`='45477') AND (`item`='52328');
UPDATE `creature_loot_template` SET `maxcount`='3' WHERE (`entry`='45912') AND (`item`='52328');
UPDATE `creature_loot_template` SET `maxcount`='3' WHERE (`entry`='45922') AND (`item`='52328');
UPDATE `creature_loot_template` SET `maxcount`='3' WHERE (`entry`='45919') AND (`item`='52328');
UPDATE `creature_loot_template` SET `maxcount`='3' WHERE (`entry`='45915') AND (`item`='52328');
UPDATE `creature_loot_template` SET `maxcount`='3' WHERE (`entry`='46328') AND (`item`='52328');
UPDATE `creature_loot_template` SET `maxcount`='3' WHERE (`entry`='47728') AND (`item`='52328');
UPDATE `creature_loot_template` SET `maxcount`='3' WHERE (`entry`='45755') AND (`item`='52328');
UPDATE `creature_loot_template` SET `maxcount`='3' WHERE (`entry`='47151') AND (`item`='52328');
UPDATE `creature_loot_template` SET `maxcount`='3' WHERE (`entry`='39844') AND (`item`='52328');

-- Inserire i lootid
UPDATE `creature_template` SET `lootid`='47409' WHERE (`entry`='47409');
UPDATE `creature_template` SET `lootid`='52107' WHERE (`entry`='52107');
UPDATE `creature_template` SET `lootid`='50491' WHERE (`entry`='50491');
UPDATE `creature_template` SET `lootid`='48833' WHERE (`entry`='48833');
UPDATE `creature_template` SET `lootid`='47401' WHERE (`entry`='47401');
UPDATE `creature_template` SET `lootid`='45748' WHERE (`entry`='45748');
UPDATE `creature_template` SET `lootid`='46785' WHERE (`entry`='46785');
UPDATE `creature_template` SET `lootid`='52503' WHERE (`entry`='52503');
UPDATE `creature_template` SET `lootid`='52663' WHERE (`entry`='52663');
UPDATE `creature_template` SET `lootid`='52816' WHERE (`entry`='52816');
UPDATE `creature_template` SET `lootid`='48394' WHERE (`entry`='48394');
UPDATE `creature_template` SET `family`='1' WHERE (`entry`='50491');    

UPDATE `creature_template` SET `dynamicflags`='2048' WHERE (`entry`='47409');
UPDATE `creature_template` SET `dynamicflags`='2048' WHERE (`entry`='52107');
UPDATE `creature_template` SET `dynamicflags`='2048' WHERE (`entry`='50491');
UPDATE `creature_template` SET `dynamicflags`='2048' WHERE (`entry`='48833');
UPDATE `creature_template` SET `dynamicflags`='2048' WHERE (`entry`='47401');
UPDATE `creature_template` SET `dynamicflags`='2048' WHERE (`entry`='45748');
UPDATE `creature_template` SET `dynamicflags`='2048' WHERE (`entry`='46785');
UPDATE `creature_template` SET `dynamicflags`='2048' WHERE (`entry`='52503');
UPDATE `creature_template` SET `dynamicflags`='2048' WHERE (`entry`='52663');
UPDATE `creature_template` SET `dynamicflags`='2048' WHERE (`entry`='52816');
UPDATE `creature_template` SET `dynamicflags`='2048' WHERE (`entry`='48394');


-- NPC POSEIDUS DROP
UPDATE `creature_loot_template` SET `item`='68781' WHERE (`entry`='50005') AND (`item`='68789');
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`='13' WHERE (`entry`='50005') AND (`item`='67132');
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`='8' WHERE (`entry`='50005') AND (`item`='67140');
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`='8' WHERE (`entry`='50005') AND (`item`='68781');
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`='7' WHERE (`entry`='50005') AND (`item`='67139');
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`='7' WHERE (`entry`='50005') AND (`item`='67142');
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`='6' WHERE (`entry`='50005') AND (`item`='67146');
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`='5' WHERE (`entry`='50005') AND (`item`='67137');
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`='5' WHERE (`entry`='50005') AND (`item`='67143');
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`='5' WHERE (`entry`='50005') AND (`item`='67148');
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`='5' WHERE (`entry`='50005') AND (`item`='67144');
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`='4' WHERE (`entry`='50005') AND (`item`='67136');
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`='3' WHERE (`entry`='50005') AND (`item`='67141');
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`='3' WHERE (`entry`='50005') AND (`item`='67135');
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES ('50005', '67147', '6');


-- Book of Glyph Mastery
UPDATE `skill_discovery_template` SET `reqSkillValue`='0' WHERE (`spellId`='64268') AND (`reqSpell`='64323');
UPDATE `skill_discovery_template` SET `reqSkillValue`='0' WHERE (`spellId`='64295') AND (`reqSpell`='64323');
UPDATE `skill_discovery_template` SET `reqSkillValue`='0' WHERE (`spellId`='64309') AND (`reqSpell`='64323');


-- Inserita Big Daddy in npc Roxxik
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`) VALUES ('11017', '95707', '200000', '202', '500');


-- Rimuove item buggo in vendor
DELETE FROM `npc_vendor` WHERE (`entry`='45289') AND (`item`='60355');
DELETE FROM `npc_vendor` WHERE (`entry`='46556') AND (`item`='60361') AND (`ExtendedCost`='3034');

-- CALL OF DUTY
UPDATE `quest_template` SET `ZoneOrSort`='1519' WHERE (`entry`='14482');
UPDATE `quest_template` SET `QuestFlags`='200' WHERE (`entry`='14482'); -- prima era 3145932
