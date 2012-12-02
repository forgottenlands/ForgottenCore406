DELETE FROM `creature` WHERE `id` IN (44600, 44650, 44687);
INSERT INTO `creature` (`id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(44650, 671, 15, 1, 0, 0, -279.636, -664.18, 888.088, 3.50432, 86400, 0, 0, 101253, 194841, 0, 0, 0, 0, 0),
(44600, 671, 15, 1, 0, 0, -310.195, -726.538, 888.087, 4.9711, 86400, 0, 0, 15876, 0, 0, 0, 0, 0, 0),
(44687, 671, 15, 1, 0, 0, -270.258, -729.956, 908.986, 2.46551, 86400, 0, 0, 13230, 0, 0, 0, 0, 0, 0);


UPDATE `creature_template` SET `faction_A`=35, `faction_H`=35, `mindmg`=1111.5,  `Health_mod`=50, `unit_class`=1, `attackpower`=1613, `maxdmg`=1430.7, `AIName`='', `MovementType`=0, `ScriptName`='npc_halfus_dragon' WHERE  `entry` IN (44652, 44645, 44650, 44797);

DELETE FROM  `spell_script_names` WHERE `spell_id` IN (83603, 84593);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES 
(83603, 'spell_halfus_stone_touch'),
(84593, 'spell_halfus_stone_grip');

DELETE FROM  `reference_loot_template` WHERE `entry` = 42167;
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES 
(42167, 59469, 0, 1, 1, 1, 1),
(42167, 59470, 0, 1, 1, 1, 1),
(42167, 59471, 0, 1, 1, 1, 1),
(42167, 59472, 0, 1, 1, 1, 1),
(42167, 59473, 0, 1, 1, 1, 1),
(42167, 59474, 0, 1, 1, 1, 1),
(42167, 59475, 0, 1, 1, 1, 1),
(42167, 59476, 0, 1, 1, 1, 1),
(42167, 59481, 0, 1, 1, 1, 1),
(42167, 59482, 0, 1, 1, 1, 1),
(42167, 59483, 0, 1, 1, 1, 1),
(42167, 59484, 0, 1, 1, 1, 1);

DELETE FROM  `creature_loot_template` WHERE `entry` IN (44600, 46209);
INSERT INTO `creature_loot_template` (`entry`, `groupid`, `mincountOrRef`, `maxcount`) VALUES 
(44600, 1, -42167, 3),
(46209, 1, -42167, 6);