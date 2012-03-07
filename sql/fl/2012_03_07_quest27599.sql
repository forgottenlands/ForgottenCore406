-- Can't take it with them
UPDATE `creature_template` SET `questItem1`='61923' WHERE (`entry`='46014');
UPDATE `creature_template` SET `lootid`='46014' WHERE (`entry`='46014');
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES ('46014', '61923', '-100');
UPDATE `creature_template` SET `Health_mod`='0.5' WHERE (`entry`='46014');
UPDATE `creature_template` SET `unit_flags`='0' WHERE (`entry`='46014');
UPDATE `creature_template` SET `faction_A`='16', `faction_H`='16' WHERE (`entry`='46014');
UPDATE `creature_template` SET `mindmg`='120', `maxdmg`='160' WHERE (`entry`='46014');