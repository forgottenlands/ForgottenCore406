-- Spawns
DELETE FROM `creature` WHERE `id` IN (43735, 43689, 43688, 43686, 43687);
INSERT INTO `creature` (`id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(43735, 671, 15, 1, 0, 0, -1060.46, -582.656, 835.03, 0.027235, 300, 0, 0, 120839264, 0, 0, 0, 0, 0, 0),
(43689, 671, 15, 1, 0, 0, -1050.84, -562.55, 835.184, 5.78657, 300, 0, 0, 4261950, 2206000, 0, 0, 0, 0, 0),
(43688, 671, 15, 1, 0, 0, -1049.9, -605.693, 835.167, 0.606077, 300, 0, 0, 4564670, 2751000, 0, 0, 0, 0, 0),
(43686, 671, 15, 1, 0, 0, -1053.54, -598.477, 835.17, 0.226737, 300, 0, 0, 37964264, 0, 0, 0, 0, 0, 0),
(43687, 671, 15, 1, 0, 0, -1053.52, -569.392, 835.189, 5.93502, 300, 0, 0, 37964264, 0, 0, 0, 0, 0, 0);

-- Template updates
UPDATE `creature_template` SET `ScriptName`='boss_ascendants' WHERE  `entry`=43686 LIMIT 1;
UPDATE `creature_template` SET `ScriptName`='boss_ascendants' WHERE  `entry`=43687 LIMIT 1;
UPDATE `creature_template` SET `ScriptName`='boss_ascendants' WHERE  `entry`=43688 LIMIT 1;
UPDATE `creature_template` SET `flags_extra`=1, `ScriptName`='boss_ascendants' WHERE  `entry`=43689 LIMIT 1;
UPDATE `creature_template` SET `flags_extra`=1 WHERE  `entry`=43688 LIMIT 1;
UPDATE `creature_template` SET `flags_extra`=1 WHERE  `entry`=43687 LIMIT 1;
UPDATE `creature_template` SET `flags_extra`=1 WHERE  `entry`=43686 LIMIT 1;