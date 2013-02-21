DELETE FROM `gameobject_template` WHERE `entry` IN (8000017, 8000018);
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `data24`, `data25`, `data26`, `data27`, `data28`, `data29`, `data30`, `data31`, `AIName`, `ScriptName`, `WDBVerified`) VALUES 
(8000017, 3, 9233, 'Valiona\'s Cache', '', '', '', 0, 0, 2.5, 0, 0, 0, 0, 0, 0, 1634, 8000017, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, '', '', 12340),
(8000018, 3, 9233, 'Valiona\'s Cache', '', '', '', 0, 0, 2.5, 0, 0, 0, 0, 0, 0, 1634, 8000018, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, '', '', 12340);

DELETE FROM `gameobject_loot_template` WHERE `entry` IN (8000017, 8000018);
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(8000017, 1, 100, 1, 0, -45994, 3),
(8000018, 1, 100, 1, 0, -45994, 6);

-- Valiona & theralion loot
DELETE FROM `reference_loot_template` WHERE `entry` IN (45994);
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(45994, 65107, 0, 1, 1, 1, 1),
(45994, 65106, 0, 1, 1, 1, 1),
(45994, 65109, 0, 1, 1, 1, 1),
(45994, 65096, 0, 1, 1, 1, 1),
(45994, 65095, 0, 1, 1, 1, 1),
(45994, 65094, 0, 1, 1, 1, 1),
(45994, 65091, 0, 1, 1, 1, 1),
(45994, 65108, 0, 1, 1, 1, 1),
(45994, 65093, 0, 1, 1, 1, 1),
(45994, 65105, 0, 1, 1, 1, 1),
(45994, 65112, 0, 1, 1, 1, 1),
(45994, 65092, 0, 1, 1, 1, 1);