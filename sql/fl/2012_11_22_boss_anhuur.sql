-- Remove objects
DELETE FROM gameobject WHERE id IN (203136, 203133, 207218, 207219);

UPDATE `gameobject_template` SET `ScriptName`='go_beacon_of_light' WHERE  `entry`=207218;
UPDATE `gameobject_template` SET `ScriptName`='go_beacon_of_light' WHERE  `entry`=207219;

INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES 
(207218, 644, 2, 65534, -603.444, 330.832, 54.4361, 6.23812, 0, 0, 0.0225331, -0.999746, 300, 0, 1),
(207219, 644, 2, 65534, -677.818, 339.484, 54.2872, 3.17506, 0, 0, 0.99986, -0.0167333, 300, 0, 1);

UPDATE `creature_template` SET `InhabitType`=5 WHERE  `entry`=40183 LIMIT 1;
UPDATE `creature_template` SET `modelid1`=11686, `minlevel`=85, `maxlevel`=85, `faction_A`=16, `faction_H`=16, `speed_walk`=0, `speed_run`=0, `mindmg`=0, `maxdmg`=0, `attackpower`=0, `minrangedmg`=0, `maxrangedmg`=0, `InhabitType`=5, `flags_extra`=2 WHERE  `entry`=40283 LIMIT 1;