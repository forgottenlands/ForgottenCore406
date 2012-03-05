UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=0, `groupid`=1 WHERE `entry` IN (39625, 48337, 40177, 48702, 40319, 48784, 40484);
DELETE FROM `creature_onkill_reward` WHERE `creature_id` IN (39625, 48337, 40177, 48702, 40319, 48784, 40484, 48822);
INSERT INTO `creature_onkill_reward` (`creature_id`, `RewOnKillRepFaction1`, `RewOnKillRepFaction2`, `MaxStanding1`, `IsTeamAward1`, `RewOnKillRepValue1`, `MaxStanding2`, `IsTeamAward2`, `RewOnKillRepValue2`, `TeamDependent`, `CurrencyId1`, `CurrencyId2`, `CurrencyId3`, `CurrencyCount1`, `CurrencyCount2`, `CurrencyCount3`) VALUES 
(48337, 1177, 1178, 7, 0, 300, 7, 0, 300, 1, 395, 0, 0, 7000, 0, 0),
(39625, 1177, 1178, 7, 0, 270, 7, 0, 270, 1, 395, 0, 0, 3000, 0, 0),
(40177, 1177, 1178, 7, 0, 270, 7, 0, 270, 1, 395, 0, 0, 3000, 0, 0),
(48702, 1177, 1178, 7, 0, 300, 7, 0, 300, 1, 395, 0, 0, 7000, 0, 0),
(40319, 1177, 1178, 7, 0, 270, 7, 0, 270, 1, 395, 0, 0, 3000, 0, 0),
(48784, 1177, 1178, 7, 0, 300, 7, 0, 300, 1, 395, 0, 0, 7000, 0, 0),
(40484, 1177, 1178, 7, 0, 270, 7, 0, 270, 1, 395, 0, 0, 3000, 0, 0),
(48822, 1177, 1178, 7, 0, 300, 7, 0, 300, 1, 395, 0, 0, 7000, 0, 0);

DELETE FROM `creature_loot_template` WHERE `entry` = 48822;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (48822, 52078, 0, 1, 2, 1, 1);
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (48822, 56455, 0, 1, 1, 1, 1);
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (48822, 56456, 0, 1, 1, 1, 1);
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (48822, 56457, 0, 1, 1, 1, 1);
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (48822, 56458, 0, 1, 1, 1, 1);
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (48822, 56459, 0, 1, 1, 1, 1);
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (48822, 56460, 0, 1, 1, 1, 1);
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (48822, 56461, 0, 1, 1, 1, 1);
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (48822, 56462, 0, 1, 1, 1, 1);
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (48822, 56463, 0, 1, 1, 1, 1);
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (48822, 56464, 0, 1, 1, 1, 1);