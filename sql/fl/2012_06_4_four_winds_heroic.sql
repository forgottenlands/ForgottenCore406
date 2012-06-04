UPDATE `creature_template` SET `minlevel`=88, `maxlevel`=88, `exp`=3, `faction_A`=14, `faction_H`=14, `mindmg`=1225.5, `maxdmg`=1544.7, `attackpower`=1651, `dmg_multiplier`=9, `minrangedmg`=1160.9, `maxrangedmg`=1328.1, `rangedattackpower`=255, `MovementType`=1, `InhabitType`=7, `flags_extra`=1 WHERE  `entry` IN (50098, 50108, 50118, 50095, 50105, 50115, 50103, 50113, 50123);
UPDATE `creature_template` SET `difficulty_entry_1`=50095, `difficulty_entry_2`=50105, `difficulty_entry_3`=50115 WHERE `entry`=45872;
UPDATE `creature_template` SET `difficulty_entry_1`=50098, `difficulty_entry_2`=50108, `difficulty_entry_3`=50118 WHERE `entry`=45871;
UPDATE `creature_template` SET `difficulty_entry_1`=50103, `difficulty_entry_2`=50113, `difficulty_entry_3`=50123 WHERE `entry`=45870;
UPDATE `creature_template` SET `lootid`=50098 WHERE `entry`=50098;
UPDATE `creature_template` SET `lootid`=50108 WHERE `entry`=50108;
UPDATE `creature_template` SET `lootid`=50118 WHERE `entry`=50118;

DELETE FROM `creature_loot_template` WHERE `entry` IN (50108, 50098, 50118);
INSERT INTO `creature_loot_template` (`entry`, `item`, `mincountOrRef`, `maxcount`) VALUES 
(50098, 1, -45871, 6),
(50108, 1, -50108, 3),
(50118, 1, -50108, 6);

DELETE FROM `reference_loot_template` WHERE `entry` = 50108;
INSERT INTO `reference_loot_template` (`entry`, `item`) VALUES 
(50108, 63494),
(50108, 63495),
(50108, 63497),
(50108, 63496),
(50108, 63498),
(50108, 63491),
(50108, 63489),
(50108, 63490),
(50108, 63492),
(50108, 63493),
(50108, 63488);