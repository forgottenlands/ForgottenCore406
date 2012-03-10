-- Aradne
UPDATE `creature_template` SET `minlevel`='40', `maxlevel`='40' WHERE (`entry`='45235');
UPDATE `creature_template` SET 
    `mindmg` = '280', 
    `maxdmg` = '310', 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE (`entry` = '45235');
UPDATE `creature_template` SET `Health_mod`='6' WHERE (`entry`='45235');
UPDATE `creature_template` SET `faction_A`='974', `faction_H`='974' WHERE (`entry`='45235');
UPDATE `creature_template` SET `unit_flags`='32832', `dynamicflags`='33556480' WHERE (`entry`='45235');
INSERT INTO `creature` VALUES ('15582999', '45235', '0', '1', '1', '0', '0', '1298.41', '-1321.05', '99.2618', '5.89695', '300', '0', '0', '10668', '0', '0', '0', '0', '0', '0');
