-- HEROIC DROP

-- Planetary Band 
UPDATE `item_template` SET `RandomSuffix`=430 WHERE (`entry`=65373);
DELETE FROM `item_enchantment_template` WHERE (`entry`=430);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (430, 230, 17);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (430, 229, 17);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (430, 228, 17);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (430, 227, 17);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (430, 231, 16);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (430, 232, 16);

-- Tempest Keeper Belt / Lightning Well Belt / Soul Breath Belt / Gale Rouser Belt
UPDATE `item_template` SET `RandomSuffix`=433 WHERE (`entry`=65375);
UPDATE `item_template` SET `RandomSuffix`=433 WHERE (`entry`=65377);
UPDATE `item_template` SET `RandomSuffix`=433 WHERE (`entry`=65376);
UPDATE `item_template` SET `RandomSuffix`=433 WHERE (`entry`=65374);
DELETE FROM `item_enchantment_template` WHERE (`entry`=433);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (433, 191, 25);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (433, 192, 25);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (433, 193, 25);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (433, 194, 25);

-- Thunder wall Belt
UPDATE `item_template` SET `RandomSuffix`=423 WHERE (`entry`=65370);
DELETE FROM `item_enchantment_template` WHERE (`entry`=423);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (423, 180, 33);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (423, 181, 33);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (423, 182, 34);

-- Star Chaser Belt / Wind Stalker Belt
UPDATE `item_template` SET `RandomSuffix`=439 WHERE  `entry`=65371;
UPDATE `item_template` SET `RandomSuffix`=439 WHERE  `entry`=65368;
DELETE FROM `item_enchantment_template` WHERE `entry`=439;
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (439, 199, 25);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (439, 200, 25);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (439, 201, 25);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (439, 202, 25);

-- Permafrost Signet
UPDATE `item_template` SET `RandomSuffix`=427 WHERE (`entry`=65372);
DELETE FROM `item_enchantment_template` WHERE (`entry`=427);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (427, 224, 33);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (427, 225, 33);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (427, 226, 34);

-- Sky Strider Belt
UPDATE `item_template` SET `RandomSuffix`=419 WHERE  `entry`=65369;
DELETE FROM `item_enchantment_template` WHERE `entry`=419;
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (419, 173, 25);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (419, 174, 25);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (419, 175, 25);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (419, 176, 25);

-- Mistral Circle
UPDATE `item_template` SET `RandomSuffix`=440 WHERE (`entry`=65367);
DELETE FROM `item_enchantment_template` WHERE (`entry`=440);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (440, 233, 33);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (440, 234, 33);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (440, 235, 34);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (440, 236, 34);