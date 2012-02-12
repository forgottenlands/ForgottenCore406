-- Loot
DELETE FROM `creature_loot_template` WHERE `entry` IN (43214, 49538);
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES 
(43214, 55797, 0, 1, 1, 1, 1),
(43214, 55798, 0, 1, 1, 1, 1),
(43214, 55799, 0, 1, 1, 1, 1),
(43214, 55800, 0, 1, 1, 1, 1),
(43214, 55801, 0, 1, 1, 1, 1),
(43214, 63043, 0.8, 1, 2, 1, 1),
(49538, 56333, 0, 1, 0, 1, 1),
(49538, 56334, 0, 1, 0, 1, 1),
(49538, 56335, 0, 1, 0, 1, 1),
(49538, 56336, 0, 1, 0, 1, 1),
(49538, 56337, 0, 1, 0, 1, 1),
(49538, 63043, 0.9, 1, 2, 1, 1);

-- Justice Points
DELETE FROM `creature_onkill_reward` WHERE `creature_id` IN (43214, 49538);
INSERT INTO `creature_onkill_reward` (`creature_id`, `CurrencyId1`, `CurrencyCount1`) VALUES 
(43214, 395, 3000),
(49538, 395, 7000);