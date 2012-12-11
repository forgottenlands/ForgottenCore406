UPDATE `creature_template` SET `Health_mod`=10.3911 WHERE  `entry`=40788;
UPDATE `creature_template` SET `Health_mod`=14.9913 WHERE  `entry`=49082;
UPDATE `creature_template` SET `exp`=3, `Health_mod`=60 WHERE  `entry`=49072;

-- Cache
DELETE FROM `gameobject_template` WHERE `entry` IN (2052160, 2052161);
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `data24`, `data25`, `data26`, `data27`, `data28`, `data29`, `data30`, `data31`, `AIName`, `ScriptName`, `WDBVerified`) VALUES 
(2052160, 3, 8630, 'Neptulon\'s Cache', '', '', '', 0, 0, 1.5, 0, 0, 0, 0, 0, 0, 1634, 2052160, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, '', '', 13623),
(2052161, 3, 8630, 'Neptulon\'s Cache', '', '', '', 0, 0, 1.5, 0, 0, 0, 0, 0, 0, 1634, 2052161, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, '', '', 13623);

DELETE FROM `reference_loot_template` WHERE `entry` IN (205216, 2052161);
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES 
(205216, 55249, 0, 1, 1, 1, 1),
(205216, 55250, 0, 1, 1, 1, 1),
(205216, 55251, 0, 1, 1, 1, 1),
(205216, 55252, 0, 1, 1, 1, 1),
(205216, 55253, 0, 1, 1, 1, 1),
(205216, 55254, 0, 1, 1, 1, 1),
(205216, 55255, 0, 1, 1, 1, 1),
(205216, 55256, 0, 1, 1, 1, 1),
(205216, 55258, 0, 1, 1, 1, 1),
(205216, 55259, 0, 1, 1, 1, 1),
(205217, 56289, 0, 1, 1, 1, 1),
(205217, 56285, 0, 1, 1, 1, 1),
(205217, 56288, 0, 1, 1, 1, 1),
(205217, 56290, 0, 1, 1, 1, 1),
(205217, 56283, 0, 1, 1, 1, 1),
(205217, 56284, 0, 1, 1, 1, 1),
(205217, 56282, 0, 1, 1, 1, 1),
(205217, 56281, 0, 1, 1, 1, 1),
(205217, 56291, 0, 1, 1, 1, 1),
(205217, 56286, 0, 1, 1, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE `entry` IN (2052160, 2052161);
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `mincountOrRef`, `maxcount`) VALUES 
(2052160, 1, -205216, 2),
(2052161, 1, -205217, 2);