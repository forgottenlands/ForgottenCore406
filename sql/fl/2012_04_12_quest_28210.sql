-- quest 28210
INSERT INTO `creature` VALUES ('15605111', '48022', '1', '1', '1', '0', '0', '-10359.4', '-824.821', '131.419', '5.02809', '300', '0', '0', '84', '0', '0', '0', '0', '0', '0');
UPDATE `creature_template` SET `minlevel`='82', `maxlevel`='82', `exp`='2' WHERE (`entry`='48022');
UPDATE `creature_template` SET `Health_mod`='8' WHERE (`entry`='48022');