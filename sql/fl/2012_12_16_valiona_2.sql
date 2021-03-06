UPDATE `creature_template` SET `modelid1`=11686, `minlevel`=85, `maxlevel`=85, `exp`=3, `faction_A`=14, `faction_H`=14, `Health_mod`=20, `flags_extra`=2 WHERE  `entry`=46374 LIMIT 1;
UPDATE `creature_template` SET `flags_extra`=0 WHERE  `entry`=46588 LIMIT 1;

DELETE FROM `spell_proc_event` WHERE `entry`IN(86622, 95639, 95640, 95641);
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES 
(86622, 0, 0, 0, 0, 0, 349524, 0, 0, 100, 0),
(95639, 0, 0, 0, 0, 0, 349524, 0, 0, 100, 0),
(95640, 0, 0, 0, 0, 0, 349524, 0, 0, 100, 0),
(95641, 0, 0, 0, 0, 0, 349524, 0, 0, 100, 0);

DELETE FROM `spell_script_names` WHERE `spell_id` IN (86631, 93055);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES 
(86631, 'spell_engulfing_magic'),
(86406, 'spell_shifting_reality'),
(92926, 'spell_shifting_reality'),
(92927, 'spell_shifting_reality'),
(92928, 'spell_shifting_reality'),
(93055, 'spell_shifting_reality');
UPDATE `creature_template` SET `modelid1`=11686, `modelid2`=0, `minlevel`=85, `maxlevel`=85, `exp`=3, `faction_A`=14, `faction_H`=14, `Health_mod`=200, `flags_extra`=2 WHERE  `entry`=46448 LIMIT 1;

UPDATE `creature_template` SET `minlevel`=85, `modelid1`=11686, `modelid2`=0, `maxlevel`=85, `exp`=3, `faction_A`=14, `faction_H`=14, `unit_flags`=33554440, `InhabitType`=5, `flags_extra`=2 WHERE  `entry`=46304 LIMIT 1;
DELETE FROM `creature_template_addon` WHERE `entry`=46304;
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES (46304, '86302 0');
DELETE FROM `creature_template_addon` WHERE `entry`=46301;
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES (46301, '86291 0');
UPDATE `creature_template` SET `modelid1`=35016, `modelid2`=0, `faction_A`=35, `faction_H`=35, `npcflag`=3 WHERE  `entry`=46301 LIMIT 1;
UPDATE `creature_template` SET `InhabitType`=5, `ScriptName`='npc_twilight_portal_bot' WHERE  `entry`=46301 LIMIT 1;
UPDATE `creature_template` SET `faction_A`=14, `faction_H`=14, `ScriptName`='npc_twilight_fiend' WHERE  `entry`=49864 LIMIT 1;

DELETE FROM `creature` WHERE `id` IN (49864, 46304, 46301);
INSERT INTO `creature` (`id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(46304, 671, 1, 32, 0, 0, -735.666, -710.047, 832.534, 5.36649, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -738.186, -699.758, 832.891, 4.56146, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -732.664, -656.229, 833.663, 5.88093, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -726.167, -660.471, 833.488, 5.78668, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -743.806, -652.058, 833.869, 5.92413, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -740.335, -671.443, 834.508, 2.83752, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -757.311, -693.174, 832.535, 4.48792, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -745.518, -694.262, 833.868, 3.35302, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -738.122, -692.406, 834.801, 3.50225, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -729.989, -688.761, 833.375, 3.71823, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -710.99, -689.184, 832.828, 1.16853, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -713.459, -697.959, 833.413, 1.27849, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -716.656, -706.157, 832.959, 0.709071, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -729.097, -713.272, 833.338, 0.343861, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -739.978, -686.189, 834.089, 5.4254, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -745.755, -679.373, 833.725, 3.10455, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -729.704, -670.967, 833.989, 3.72894, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -724.189, -666.538, 833.857, 3.91744, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -751.993, -654.515, 833.483, 0.783694, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -753.772, -662.257, 833.61, 1.57695, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -754.217, -670.536, 833.363, 1.50626, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -755.75, -681.767, 833.481, 1.41594, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -752.7, -688.102, 833.438, 2.6765, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -742.81, -688.642, 832.948, 3.56008, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -738.467, -682.667, 833.389, 3.29697, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -728.677, -679.747, 833.238, 4.2905, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -722.351, -674.24, 833.636, 3.22628, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -716.742, -678.758, 833.341, 2.18955, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -718.048, -684.028, 833.187, 0.842596, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -722.601, -694.051, 833.636, 1.39237, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -725.429, -699.901, 833.941, 0.960406, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -733.327, -701.533, 833.532, 6.23436, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -744.858, -701.173, 833.967, 6.27755, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -752.9, -701.955, 834.182, 0.0297079, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -761.598, -699.456, 833.857, 5.84951, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -766.62, -695.144, 832.864, 5.24869, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -768.333, -685.754, 832.841, 4.70284, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -765.616, -677.121, 833.495, 4.00776, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -760.229, -673.152, 834.092, 3.56794, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0),
(46301, 671, 1, 32, 0, 0, -722.807, -686.53, 831.89, 4.89537, 300, 0, 0, 154980, 0, 0, 0, 0, 0, 0),
(49864, 671, 1, 32, 0, 0, -743.767, -709.88, 831.896, 0.630229, 300, 2, 0, 77490, 0, 0, 1, 0, 0, 0),
(49864, 671, 1, 32, 0, 0, -756.389, -712.986, 831.899, 5.59709, 300, 2, 0, 77490, 0, 0, 1, 0, 0, 0),
(49864, 671, 1, 32, 0, 0, -754.388, -698.421, 831.892, 2.99821, 300, 2, 0, 77490, 0, 0, 1, 0, 0, 0),
(49864, 671, 1, 32, 0, 0, -730.982, -700.102, 831.895, 4.60592, 300, 2, 0, 77490, 0, 0, 1, 0, 0, 0),
(49864, 671, 1, 32, 0, 0, -714.537, -688.14, 831.891, 1.43527, 300, 2, 0, 77490, 0, 0, 1, 0, 0, 0),
(49864, 671, 1, 32, 0, 0, -735.315, -677.325, 831.893, 4.22029, 300, 2, 0, 77490, 0, 0, 1, 0, 0, 0),
(49864, 671, 1, 32, 0, 0, -763.238, -667.667, 831.896, 5.64029, 300, 2, 0, 77490, 0, 0, 1, 0, 0, 0),
(49864, 671, 1, 32, 0, 0, -764.323, -686.654, 831.89, 1.25855, 300, 2, 0, 77490, 0, 0, 1, 0, 0, 0),
(49864, 671, 1, 32, 0, 0, -734.522, -667.787, 831.895, 5.84449, 300, 2, 0, 77490, 0, 0, 1, 0, 0, 0),
(49864, 671, 1, 32, 0, 0, -746.23, -665.269, 831.897, 0.190409, 300, 2, 0, 77490, 0, 0, 1, 0, 0, 0),
(46304, 671, 1, 32, 0, 0, -749.65, -670.808, 833.742, 3.08492, 300, 2, 0, 154980, 0, 0, 1, 0, 0, 0);

DELETE FROM `gameobject_template` WHERE `entry` IN (8000016, 8000015);
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `data24`, `data25`, `data26`, `data27`, `data28`, `data29`, `data30`, `data31`, `AIName`, `ScriptName`, `WDBVerified`) VALUES 
(8000015, 3, 9233, 'Valiona\'s Cache', '', '', '', 0, 0, 2.5, 0, 0, 0, 0, 0, 0, 1634, 8000015, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, '', '', 12340),
(8000016, 3, 9233, 'Valiona\'s Cache', '', '', '', 0, 0, 2.5, 0, 0, 0, 0, 0, 0, 1634, 8000016, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, '', '', 12340);

DELETE FROM `creature_loot_template` WHERE  `entry` IN (45993, 45992, 49897, 49903);
DELETE FROM `reference_loot_template` WHERE  `entry`=45993;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES 
(45993, 59512, 0, 1, 1, 1, 1),
(45993, 59516, 0, 1, 1, 1, 1),
(45993, 59519, 0, 1, 1, 1, 1),
(45993, 63534, 0, 1, 1, 1, 1),
(45993, 63535, 0, 1, 1, 1, 1),
(45993, 63536, 0, 1, 1, 1, 1),
(45993, 63531, 0, 1, 1, 1, 1),
(45993, 63532, 0, 1, 1, 1, 1),
(45993, 63533, 0, 1, 1, 1, 1),
(45993, 59517, 0, 1, 1, 1, 1),
(45993, 59518, 0, 1, 1, 1, 1),
(45993, 59515, 0, 1, 1, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE `entry` IN (8000016, 8000015);
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `mincountOrRef`, `maxcount`) VALUES 
(8000016, 1, -45993, 3),
(8000015, 1, -45993, 6);