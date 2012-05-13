UPDATE `item_template` SET `RequiredDisenchantSkill`='425' WHERE (`entry`='60245');
UPDATE `item_template` SET `DisenchantID`='60245' WHERE (`entry`='60245');
DELETE FROM `disenchant_loot_template` WHERE `entry`=60245 AND `item`=52722;
INSERT INTO `disenchant_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `mincountOrRef`, `maxcount`) VALUES ('60245', '52722', '100', '1', '3');


UPDATE `item_template` SET `RequiredDisenchantSkill`='425' WHERE (`entry`='59465');
UPDATE `item_template` SET `DisenchantID`='59465' WHERE (`entry`='59465');
DELETE FROM `disenchant_loot_template` WHERE `entry`=59465 AND `item`=52722;
INSERT INTO `disenchant_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `mincountOrRef`, `maxcount`) VALUES ('59465', '52722', '100', '1', '2');