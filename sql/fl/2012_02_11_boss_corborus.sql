UPDATE `creature_template` SET `AIName`='', `ScriptName`='boss_corborus' WHERE  `entry`=43438;
DELETE FROM `smart_scripts` WHERE  `entryorguid`=43438;

-- Loot
DELETE FROM `creature_loot_template` WHERE `entry` IN (43438, 49642);
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES 
(39665, 55278, 0, 1, 1, 1, 1),
(39665, 55279, 0, 1, 1, 1, 1),
(39665, 55776, 0, 1, 1, 1, 1),
(39665, 55777, 0, 1, 1, 1, 1),
(39665, 55778, 0, 1, 1, 1, 1),
(43438, 55792, 0, 1, 1, 1, 1),
(43438, 55793, 0, 1, 1, 1, 1),
(43438, 55794, 0, 1, 1, 1, 1),
(43438, 55795, 0, 1, 1, 1, 1),
(43438, 55796, 0, 1, 1, 1, 1),
(49642, 52506, 0, 1, 1, 1, 1),
(49642, 56328, 0, 1, 1, 1, 1),
(49642, 56329, 0, 1, 1, 1, 1),
(49642, 56330, 0, 1, 1, 1, 1),
(49642, 56331, 0, 1, 1, 1, 1),
(49642, 56332, 0, 1, 1, 1, 1);

-- Justice Points
DELETE FROM `creature_onkill_reward` WHERE `creature_id` IN (43438, 49642);
INSERT INTO `creature_onkill_reward` (`creature_id`, `CurrencyId1`, `CurrencyCount1`) VALUES 
(43438, 395, 3000),
(49642, 395, 7000);