-- Planetary Band
UPDATE `item_template` SET `RandomSuffix`=429 WHERE (`entry`=63494);
DELETE FROM `item_enchantment_template` WHERE (`entry`=429);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (429, 213, 17);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (429, 212, 17);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (429, 211, 17);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (429, 214, 17);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (429, 215, 16);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (429, 216, 16);

-- Tempest Keeper Belt / Lightning Well Belt / Soul Breath Belt / Gale Rouser Belt
UPDATE `item_template` SET `RandomSuffix`=434 WHERE (`entry`=63497);
UPDATE `item_template` SET `RandomSuffix`=434 WHERE (`entry`=63496);
UPDATE `item_template` SET `RandomSuffix`=434 WHERE (`entry`=63498);
UPDATE `item_template` SET `RandomSuffix`=434 WHERE (`entry`=63495);
DELETE FROM `item_enchantment_template` WHERE (`entry`=434);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (434, 186, 25);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (434, 185, 25);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (434, 187, 25);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (434, 188, 25);

-- Thunder wall Belt
UPDATE `item_template` SET `RandomSuffix`=424 WHERE (`entry`=63491);
DELETE FROM `item_enchantment_template` WHERE (`entry`=424);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (424, 177, 33);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (424, 178, 33);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES (424, 179, 34);


-- Zotac fix
UPDATE `item_template` SET `RandomSuffix`=428 WHERE  `entry`=63490;
DELETE FROM `item_enchantment_template` WHERE `entry` IN (428, 426, 438, 441);
INSERT INTO `item_enchantment_template` (`entry`, `ench`, `chance`) VALUES 
(426, 207, 33), -- Permafrost Signet
(426, 208, 33),
(426, 209, 34),
(428, 169, 25), -- Sky Strider Belt
(428, 170, 25),
(428, 171, 25),
(428, 172, 25),
(438, 195, 25), -- Star Chaser Belt Wind Stalker Belt
(438, 196, 25),
(438, 197, 25),
(438, 198, 25),
(441, 216, 25), -- Mistral Circle
(441, 217, 25),
(441, 218, 25),
(441, 219, 25);
