DELETE FROM `creature_loot_template` WHERE `entry` IN (42188, 49654);
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES 
(42188, 55802, 0, 1, 1, 1, 1),
(42188, 55803, 0, 1, 1, 1, 1),
(42188, 55804, 0, 1, 1, 1, 1),
(42188, 55810, 0, 1, 1, 1, 1),
(42188, 55811, 0, 1, 1, 1, 1),
(49654, 56338, 0, 1, 1, 1, 1),
(49654, 56339, 0, 1, 1, 1, 1),
(49654, 56340, 0, 1, 1, 1, 1),
(49654, 56341, 0, 1, 1, 1, 1),
(49654, 56342, 0, 1, 0, 1, 1);

DELETE FROM `creature_onkill_reward` WHERE `creature_id` IN (42188, 49654, 42333, 49624);
INSERT INTO `creature_onkill_reward` (`creature_id`, `CurrencyId1`, `CurrencyCount1`) VALUES 
(49654, 395, 7000),
(42188, 395, 3000),
(49624, 395, 7000),
(42333, 395, 3000);

UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=0, `lootmode`=1, `groupid`=1 WHERE  `entry`IN (42333,49624);

DELETE FROM `smart_scripts` WHERE `entryorguid` = 42333;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(42333, 0, 0, 0, 0, 0, 100, 30, 14000, 14000, 45000, 46000, 11, 79002, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Azil'),
(42333, 0, 1, 0, 0, 0, 100, 30, 2000, 2000, 21000, 22000, 11, 79345, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Azil'),
(42333, 0, 2, 0, 0, 0, 100, 30, 14000, 14000, 19000, 20000, 11, 79340, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Azil'),
(42333, 0, 3, 0, 0, 0, 100, 30, 45000, 47000, 34000, 36000, 11, 79351, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Azil');