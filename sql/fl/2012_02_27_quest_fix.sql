-- Airfive's quests Fix

-- The Mosh'Ogg Bounty
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES ('4027635', '204087', '0', '1', '1', '-12497.4', '-1011.32', '56.09', '1.40306', '0', '0', '0.645387', '0.763856', '60', '0', '1');

-- The Abandoned Crypt
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES ('4027610', '205258', '0', '1', '1', '1060.84', '-1894.76', '31.7768', '4.7377', '0', '0', '0.698101', '-0.716', '300', '0', '1');
INSERT INTO `gameobject_questrelation` (`id`, `quest`) VALUES ('205258', '27171');
INSERT INTO `gameobject_involvedrelation` (`id`, `quest`) VALUES ('205258', '27170');

