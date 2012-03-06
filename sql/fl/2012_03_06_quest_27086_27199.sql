-- QUEST: ASHES TO ASHES
-- Andorhal Force-Commander
UPDATE `creature_template` SET `minlevel`='40' WHERE (`entry`='44450');
UPDATE `creature_template` SET `maxlevel`='40' WHERE (`entry`='44450');
UPDATE `creature_template` SET `faction_A`='2202' WHERE (`entry`='44450');
UPDATE `creature_template` SET `faction_H`='2202' WHERE (`entry`='44450');
UPDATE `creature_template` SET `unit_flags`='32768' WHERE (`entry`='44450');
UPDATE `creature_template` SET `dynamicflags`='33556480' WHERE (`entry`='44450');
UPDATE `creature_template` SET `type_flags`='4096' WHERE (`entry`='44450');
UPDATE `creature_template` SET `MovementType`='1' WHERE (`entry`='44450');
UPDATE `creature_template` SET 
    `mindmg` = '200', 
    `maxdmg` = '260', 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE (`entry` = '44450');


-- Deathguard War-Captain
UPDATE `creature_template` SET `minlevel`='40' WHERE (`entry`='44449');
UPDATE `creature_template` SET `maxlevel`='40' WHERE (`entry`='44449');
UPDATE `creature_template` SET `faction_A`='2213' WHERE (`entry`='44449');
UPDATE `creature_template` SET `faction_H`='2213' WHERE (`entry`='44449');
UPDATE `creature_template` SET `unit_flags`='32768' WHERE (`entry`='44449');
UPDATE `creature_template` SET `dynamicflags`='33556480' WHERE (`entry`='44449');
UPDATE `creature_template` SET `type_flags`='4096' WHERE (`entry`='44449');
UPDATE `creature_template` SET `MovementType`='1' WHERE (`entry`='44449');
UPDATE `creature_template` SET 
    `mindmg` = '200', 
    `maxdmg` = '260', 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE (`entry` = '44449');
  
 
 -- Spawn
INSERT INTO `creature` VALUES ('15581939', '44449', '0', '1', '1', '0', '0', '1384.22', '-1615.8', '64.2645', '1.45394', '180', '0', '0', '3048', '0', '0', '0', '0', '0', '0');
INSERT INTO `creature` VALUES ('15581938', '44449', '0', '1', '1', '0', '0', '1439.98', '-1550.77', '56.0982', '1.37304', '180', '0', '0', '3048', '0', '0', '0', '0', '0', '0');
INSERT INTO `creature` VALUES ('15581936', '44449', '0', '1', '1', '0', '0', '1338.23', '-1585.55', '59.4789', '6.28178', '180', '0', '0', '3048', '0', '0', '0', '0', '0', '0');
INSERT INTO `creature` VALUES ('15581935', '44449', '0', '1', '1', '0', '0', '1420.42', '-1603.63', '71.0027', '1.87256', '180', '0', '0', '3048', '0', '0', '0', '0', '0', '0');
INSERT INTO `creature` VALUES ('15581940', '44450', '0', '1', '1', '0', '0', '1327.6', '-1377.36', '46.1544', '4.14785', '180', '0', '0', '3048', '0', '0', '0', '0', '0', '0');
INSERT INTO `creature` VALUES ('15581941', '44450', '0', '1', '1', '0', '0', '1427.64', '-1420.14', '55.6425', '5.35108', '180', '0', '0', '3048', '0', '0', '0', '0', '0', '0');
INSERT INTO `creature` VALUES ('15581942', '44450', '0', '1', '1', '0', '0', '1502.2', '-1438.63', '65.4981', '5.1618', '180', '0', '0', '3048', '0', '0', '0', '0', '0', '0');
INSERT INTO `creature` VALUES ('15581943', '44450', '0', '1', '1', '0', '0', '1311.04', '-1442.79', '50.4263', '6.07286', '180', '0', '0', '3048', '0', '0', '0', '0', '0', '0');

 