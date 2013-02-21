-- Halfus Heroic Loot
DELETE FROM `reference_loot_template` WHERE `entry` IN (42168, 42169);
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(42168, 65134, 0, 1, 1, 1, 1),
(42168, 65138, 0, 1, 1, 1, 1),
(42168, 65133, 0, 1, 1, 1, 1),
(42168, 65141, 0, 1, 1, 1, 1),
(42168, 65139, 0, 1, 1, 1, 1),
(42168, 65144, 0, 1, 1, 1, 1),
(42168, 65142, 0, 1, 1, 1, 1),
(42168, 65136, 0, 1, 1, 1, 1),
(42168, 65137, 0, 1, 1, 1, 1),
(42168, 65135, 0, 1, 1, 1, 1),
(42168, 65143, 0, 1, 1, 1, 1),
(42168, 65140, 0, 1, 1, 1, 1),
(42169, 67423, 0, 1, 1, 1, 1),
(42169, 67424, 0, 1, 1, 1, 1),
(42169, 67425, 0, 1, 1, 1, 1);

UPDATE `creature_template` SET `dmg_multiplier`=70 WHERE  `entry`=46211 LIMIT 1;
UPDATE `creature_template` SET `dmg_multiplier`=65 WHERE  `entry`=46209 LIMIT 1;
UPDATE `creature_template` SET `dmg_multiplier`=45 WHERE  `entry`=46210 LIMIT 1;
UPDATE `creature_template` SET `Health_mod`=615 WHERE  `entry`=46210 LIMIT 1;
UPDATE `creature_template` SET `flags_extra`=1 WHERE  `entry`=46210 LIMIT 1;
UPDATE `creature_template` SET `flags_extra`=1 WHERE  `entry`=46211 LIMIT 1;