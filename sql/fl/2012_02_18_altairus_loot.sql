INSERT INTO `creature_onkill_reward` (`creature_id`, `CurrencyId1`, `CurrencyCount1`) VALUES 
(43874, 395, 7000),
(43873, 395, 3000);

DELETE FROM `creature` WHERE `id` = 45455;
INSERT INTO `creature` (`id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(45455, 657, 3, 1, 0, 0, -767.311, -47.424, 639.926, 3.24442, 86400, 0, 0, 42, 0, 0, 0, 0, 0, 0),
(45455, 657, 3, 1, 0, 0, -1197.39, 109.385, 740.706, 4.35563, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0);

INSERT INTO `creature_onkill_reward` (`creature_id`, `CurrencyId1`, `CurrencyCount1`) VALUES 
(43876, 395, 7000),
(43875, 395, 3000);

INSERT INTO `creature_onkill_reward` (`creature_id`, `RewOnKillRepFaction1`, `RewOnKillRepFaction2`, `MaxStanding1`, `RewOnKillRepValue1`, `MaxStanding2`, `RewOnKillRepValue2`, `TeamDependent`) VALUES 
(46450, 1177, 1178, 7, 11, 7, 11, 1),
(45916, 1177, 1178, 7, 11, 7, 11, 1),
(45918, 1177, 1178, 7, 11, 7, 11, 1),
(45920, 1177, 1178, 7, 11, 7, 11, 1),
(45923, 1177, 1178, 7, 11, 7, 11, 1),
(45925, 1177, 1178, 7, 11, 7, 11, 1),
(45927, 1177, 1178, 7, 11, 7, 11, 1),
(45929, 1177, 1178, 7, 11, 7, 11, 1),
(45936, 1177, 1178, 7, 11, 7, 11, 1),
(45931, 1177, 1178, 7, 11, 7, 11, 1);