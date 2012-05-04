-- Val'kyr incursion
UPDATE `creature_template` SET `minlevel`='39', `maxlevel`='40' WHERE (`entry`='45239');
UPDATE `creature_template` SET 
    `mindmg` = '260', 
    `maxdmg` = '290', 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE (`entry` = '45239');
UPDATE `creature_template` SET `Health_mod`='1' WHERE (`entry`='45239');
UPDATE `creature_template` SET `faction_A`='974', `faction_H`='974' WHERE (`entry`='45239');
UPDATE `creature_template` SET `unit_flags`='32832', `dynamicflags`='33556480' WHERE (`entry`='45239');
INSERT INTO `creature` VALUES ('15582533', '45239', '0', '1', '1', '0', '0', '1332.48', '-1513.6', '59.071', '5.3833', '180', '0', '0', '42', '0', '0', '0', '0', '0', '0');
INSERT INTO `creature` VALUES ('15582534', '45239', '0', '1', '1', '0', '0', '1411.87', '-1550.21', '54.3959', '6.06189', '180', '0', '0', '42', '0', '0', '0', '0', '0', '0');
INSERT INTO `creature` VALUES ('15582535', '45239', '0', '1', '1', '0', '0', '1447.6', '-1528.11', '55.9224', '1.55056', '180', '0', '0', '42', '0', '0', '0', '0', '0', '0');
INSERT INTO `creature` VALUES ('15582536', '45239', '0', '1', '1', '0', '0', '1452.56', '-1489.54', '56.8666', '3.50463', '180', '0', '0', '42', '0', '0', '0', '0', '0', '0');
INSERT INTO `creature` VALUES ('15582537', '45239', '0', '1', '1', '0', '0', '1423.53', '-1446.6', '54.6521', '2.21972', '180', '0', '0', '42', '0', '0', '0', '0', '0', '0');
