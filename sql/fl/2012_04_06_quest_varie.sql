-- Quest 25309
UPDATE `creature_template` SET `faction_A`='31', `faction_H`='31' WHERE (`entry`='39752');

-- Quest 25494
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`='-100' WHERE (`entry`='40403') AND (`item`='54610');

-- Quest 25224
INSERT INTO `gameobject` VALUES ('4027705', '202619', '1', '1', '1', '4387.75', '-4344.25', '900.972', '0.56352', '0', '0', '0.278047', '0.960568', '300', '0', '1');
INSERT INTO `gameobject` VALUES ('4027703', '202619', '1', '1', '1', '4382.41', '-4349.68', '900.397', '4.04754', '0', '0', '0.899149', '-0.437643', '300', '0', '1');
INSERT INTO `gameobject` VALUES ('4027702', '202619', '1', '1', '1', '4407.49', '-4405.95', '898.949', '5.78956', '0', '0', '0.244314', '-0.969696', '300', '0', '1');
INSERT INTO `gameobject` VALUES ('4027701', '202619', '1', '1', '1', '4362.44', '-4430.57', '897.164', '1.67879', '0', '0', '0.744238', '0.667915', '300', '0', '1');

-- Quest 13505
UPDATE `gameobject_template` SET `flags`='4' WHERE (`entry`='194089');
UPDATE `gameobject_template` SET `flags`='4' WHERE (`entry`='194090');
UPDATE `gameobject_template` SET `data0`='57', `data1`='194089' WHERE (`entry`='194089');
UPDATE `gameobject_template` SET `data0`='57', `data1`='194090' WHERE (`entry`='194090');
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES ('194089', '44830', '-100');
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES ('194090', '44830', '-100');

-- Quest 9361
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`='41' WHERE (`entry`='16863') AND (`item`='23270');
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`='5' WHERE (`entry`='16879') AND (`item`='23270');
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`='2' WHERE (`entry`='16880') AND (`item`='23270');

-- Quest 9545
UPDATE `quest_template` SET `ReqItemId1`='23645', `ReqItemId2`='0' WHERE (`entry`='9545');
UPDATE `quest_template` SET `ReqItemCount1`='1', `ReqItemCount2`='0' WHERE (`entry`='9545');