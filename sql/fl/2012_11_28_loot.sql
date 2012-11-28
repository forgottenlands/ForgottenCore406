DELETE FROM `gameobject_template` WHERE `entry` IN (8000009, 8000008);
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `data24`, `data25`, `data26`, `data27`, `data28`, `data29`, `data30`, `data31`, `AIName`, `ScriptName`, `WDBVerified`) VALUES 
(8000009, 3, 9233, 'Omnotron\'s Cache', '', '', '', 0, 0, 2.5, 0, 0, 0, 0, 0, 0, 1634, 8000009, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, '', '', 12340),
(8000008, 3, 9233, 'Omnotron\'s Cache', '', '', '', 0, 0, 2.5, 0, 0, 0, 0, 0, 0, 1634, 8000008, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, '', '', 12340);

DELETE FROM `gameobject_loot_template` WHERE `entry` IN (8000009, 8000008);
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES 
(8000009, 0, 100, 1, 1, -42166, 3),
(8000008, 0, 100, 1, 1, -42166, 6);