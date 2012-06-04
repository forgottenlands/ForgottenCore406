DELETE FROM `reference_loot_template` WHERE `entry` = 45871;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES 
(45871, 63488, 11.6, 1, 0, 1, 1),
(45871, 63489, 19.3, 1, 0, 1, 1),
(45871, 63491, 19.6, 1, 0, 1, 1),
(45871, 63492, 14.5, 1, 0, 1, 1),
(45871, 63493, 13.8, 1, 0, 1, 1),
(45871, 63494, 21.5, 1, 0, 1, 1),
(45871, 63495, 20.7, 1, 0, 1, 1),
(45871, 63496, 17.1, 1, 0, 1, 1),
(45871, 63497, 17.1, 1, 0, 1, 1),
(45871, 63498, 21.1, 1, 0, 1, 1);

DELETE FROM `creature_loot_template` WHERE `entry` = 45871;
INSERT INTO `creature_loot_template` (`entry`, `item`, `mincountOrRef`, `maxcount`) VALUES
(45871, 1, -45871, 3);