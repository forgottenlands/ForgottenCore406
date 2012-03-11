DELETE FROM `gameobject` WHERE `guid` IN(189283);
DELETE FROM `gameobject` WHERE `id` IN(/*Deletes gobs that are spawned through this script*/207834, 402092, 204929, 203306,/*Deletes unofficial gobs*/ 202211, 205079, 24388, 203083, 20720, 402368, 185218, 185216, 185217) AND `map` = 669;

INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
-- Onyxia Elevator
(207834, 669, 15, 2, -109.87, -223.157, 11.5354, 1.79425, 0, 0, 0.781537, 0.623858, 300, 1, 1),
-- Pre-Boss Gate
(402092, 669, 15, 1, -270.2, -224.415, 190.316, 3.1307, 0, 0, 0.999985, 0.00544851, 300, 0, 1),
-- Finkles Cage
(204929, 669, 15, 1, -115.558, 45.1754, 71, 3.05438, 0, 0, 0.999049, 0.0435902, 300, 0, 1),
-- Maloriaks Cauldron
(203306, 669, 15, 1, -105.803, -485.729, 73.4583, 3.08822, 0, 0, 0.999644, 0.0266813, 300, 0, 1),

-- Atramedes Door
(402368, 669, 15, 1, 53.670784, -224.593292, 94.5037, 3.130350, 0, 0, 0.999629, 0.0272188, 300, 0, 1);


DELETE FROM `creature` WHERE (`id` IN(44418, 44202, 41377)) AND (`map` = 669);
INSERT INTO `creature` (`id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
-- Finkle and Bil o tron
(44418, 669, 15, 1, 0, 0, -110.376, 37.4967, 72.0576, 4.31101, 300, 0, 0, 77490, 0, 0, 0, 0, 0, 0),
(44202, 669, 15, 1, 0, 0, -115.956, 42.477, 72.0559, 4.65658, 300, 0, 0, 774900, 0, 0, 0, 0, 0, 0),
-- Release Abberations Trigger
(41377, 669, 15, 1, 0, 0, -75.8496, -427.989, 73.247, 3.44959, 300, 0, 0, 85892, 0, 0, 0, 0, 0, 0);

-- Modifys existing spawnpositions
REPLACE INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
-- Maloriak
(1082133, 41378, 669, 15, 1, 0, 0, -106.063, -464.796, 73.4545, 1.53706, 300, 0, 0, 86579136, 0, 0, 0, 0, 0, 0);

REPLACE INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `data24`, `data25`, `data26`, `data27`, `data28`, `data29`, `data30`, `data31`, `AIName`, `ScriptName`, `WDBVerified`) VALUES
(402092, 0, 9946, 'BLACKROCKV2_PORTCULLIS_02', '','','',1375, 32, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, '', '', 13623),
(203716, 11, 10407, 'Blackwing Descent Elevator', '', '', '', 0, 40, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 13623),
(207834, 11, 10363, 'Doodad_BlackWingV2_Elevator_Onyxia01', '', '', '', 0, 40, 1, 0, 0, 0, 0, 0, 0, 13333, 0, 0, 0, 0, 748, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 13623),
(402368, 0, 10463, 'BLACKWING_PORTCULLIS', '', '', '', 1375, 32, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, '', '', 13623),
(203306, 10, 9554, 'Doodad_BlackrockV2_LabRoom_Cauldron01', '', '', '', 0, 16, 0.73, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 13623);

UPDATE `gameobject` SET `spawnMask` = 15 WHERE `map` = 669;

-- Magmaw (Blackwing Descent) Updates

DELETE FROM `vehicle_accessory` WHERE `entry` = 41570;
INSERT INTO `vehicle_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`)
VALUES (41570, 42347, 0, 0, 'Magmaws Head');
UPDATE `creature_template` SET `VehicleId`=522	 WHERE `entry`=41570 LIMIT 1;
UPDATE `creature_template` SET `IconName`='' WHERE `entry`=41570 LIMIT 1;

-- Notes to find the right VehicleID
-- 1443 Kopf oben aber nicht sichtbar
-- 1442 sehr gut aber kopf verdreht sitzt richtig und so
-- 1511,1519,1531 noch besser kopf ist blos zu weit oben 9551
-- 1512 Kopf ist weiter unten schaut abe rnach oben
-- 1514 Kopf zu weit unten aber nicht viel 9560
-- 1524 zu weit rechts

UPDATE `creature_template` SET `AIName`='', `ScriptName`='boss_magmaw' WHERE `entry`=41570 LIMIT 1;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 41570;

-- Updates Magmaws Head
UPDATE `creature_template` SET `faction_A`=16, `faction_H`=16 WHERE `entry`=42347 LIMIT 1;
UPDATE `creature_template` SET `VehicleId`=516	 WHERE `entry`=42347 LIMIT 1;

UPDATE `creature_template` SET `AIName`='', `ScriptName`='mob_magmaws_head' WHERE `entry`=42347 LIMIT 1;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 42347;
UPDATE `creature_template` SET `IconName`='vehichleCursor' WHERE `entry`=42347 LIMIT 1;

-- Adds the launch hook ability to the Magmaw Head vehicle
UPDATE `creature_template` SET `spell1`=77917 WHERE `entry`=41570 LIMIT 1;

-- Delete non Blizzlike spawned ads
DELETE FROM `creature` WHERE `guid` IN(6521578, 6521576) AND `id` = 42362;

-- Adds Ingition Aura to the Ignation Trigger
REPLACE INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`)
VALUES (49447, 0, 0, 0, 0, 0, '92131 0');

UPDATE `creature_template` SET `faction_A`=16, `faction_H`=16 WHERE `entry`=49447 LIMIT 1;
UPDATE `creature_template` SET `scale`=4 WHERE `entry`=49447 LIMIT 1;
UPDATE `creature_template` SET `modelid1`=11686, `modelid2`=0 WHERE `entry`=49447 LIMIT 1;

-- Spell Scriptnames
REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(78941, 'spell_parasitic_infection');

-- Lava parasites
UPDATE `creature_template` SET `faction_A`=16, `faction_H`=16 WHERE `entry`=41806 LIMIT 1;
UPDATE `creature_template` SET `Health_mod`=2, `exp`=3 WHERE `entry`=41806 LIMIT 1;

-- Lava Parisites Trigger
UPDATE `creature_template` SET `AIName`='', `ScriptName`='mob_pillar_of_flame_trigger' WHERE `entry`=41843 LIMIT 1;
UPDATE `creature_template` SET `faction_A`=16, `faction_H`=16 WHERE `entry`=41843 LIMIT 1;
UPDATE `creature_template` SET `modelid1`=11686, `modelid2`=0 WHERE `entry`=41843 LIMIT 1;

-- Lava Parasite
SET @ENTRY := 41806;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,33,0,100,0,0,1,1,1,11,78941,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Parasitic Infection");

-- Nefarian Helper
UPDATE `creature_template` SET `faction_A`=16, `faction_H`=16 WHERE `entry`=49427 LIMIT 1;
UPDATE `creature_template` SET `minlevel`=88, `maxlevel`=88 WHERE `entry`=49427 LIMIT 1;
UPDATE `creature_template` SET `AIName`='', `ScriptName`='mob_nefarian_helper_heroic' WHERE `entry`=49427 LIMIT 1;
UPDATE `creature_template` SET `InhabitType`=7 WHERE `entry`=49427 LIMIT 1;

-- Blazing Bone Construct
UPDATE `creature_template` SET `faction_A`=16, `faction_H`=16 WHERE `entry`=49416 LIMIT 1;

SET @ENTRY := 49416;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,2,0,100,0,20,20,0,0,11,92177,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Blazing Bone Construct cast Armageddon at 20% HP");

-- Omnotron Defense System (Blackwing Descent)

UPDATE `creature_template` SET `AIName`='', `ScriptName`='boss_omnotron' WHERE `entry`=42186 LIMIT 1;

UPDATE `creature_template` SET `AIName`='', `ScriptName`='boss_magmatron' WHERE `entry`=42178 LIMIT 1;
UPDATE `creature_template` SET `AIName`='', `ScriptName`='boss_toxitron' WHERE `entry`=42180 LIMIT 1;
UPDATE `creature_template` SET `AIName`='', `ScriptName`='boss_electron' WHERE `entry`=42179 LIMIT 1;
UPDATE `creature_template` SET `AIName`='', `ScriptName`='boss_arcanotron' WHERE `entry`=42166 LIMIT 1;

UPDATE `creature_template` SET `AIName`='', `ScriptName`='npc_poison_bomb' WHERE `entry`=42897 LIMIT 1;

DELETE FROM `smart_scripts` WHERE `entryorguid` IN(42178, 42180, 42179, 42166, 42186, 42186);

-- Trons
DELETE FROM `creature` WHERE `guid` IN(1082113, 1082115, 1082117, 1082119);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(1082115, 42180, 669, 15, 1, 0, 0, -333.731, -400.515, 214.008, 6.25277, 300, 0, 0, 25767600, 0, 0, 2, 0, 0, 0),
(1082117, 42179, 669, 15, 1, 0, 0, -341.526, -405.203, 213.975, 1.13984, 300, 0, 0, 25767600, 0, 0, 0, 0, 0, 0),
(1082119, 42166, 669, 15, 1, 0, 0, -316.568, -410.917, 214.043, 1.65822, 300, 0, 0, 25767600, 0, 0, 0, 0, 0, 0),
(1082113, 42178, 669, 15, 1, 0, 0, -307.968, -406.23, 214.008, 1.98808, 300, 0, 0, 25767600, 0, 0, 0, 0, 0, 0);

UPDATE `creature_template` SET `MovementType` = 2 WHERE `entry`=42180 LIMIT 1;

-- Omnotron
DELETE FROM `creature` WHERE `id` = 42186 AND `map` = 669;
INSERT INTO `creature` (`id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(42186, 669, 15, 1, 0, 0, -324.858, -419.466, 213.897, 1.56003, 300, 0, 1, 42000, 0, 0, 0, 0, 0, 0);

DELETE FROM `creature_template_addon` WHERE `entry` = 42186;
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`)
VALUES (42186, 0, 0, 0, 0, 0, '/* ToDo: Omnotron Visual Effect is Missing*/');

-- 57886 0 57887

-- Toxitron Waypoints
DELETE FROM `creature_addon` WHERE `guid` = 1082115;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(1082115,10821150, 0, 0, 0, 0, '');

DELETE FROM `waypoint_data` WHERE `id` = 10821150;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`) VALUES
(10821150, 1, -315.853, -400.56, 213.974, 1500, 0, 0, 100, 0),
(10821150, 2, -334.152, -400.321, 214.005, 1500, 0, 0, 100, 0);

-- Abilities
-- Toxitron

-- Chemical Cloud
DELETE FROM `creature_template_addon` WHERE `entry` = 42934;
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`)
VALUES (42934, 0, 0, 0, 0, 0, '91474 0');

UPDATE `creature_template` SET `unit_flags`=33554436, `type_flags`=1024 WHERE `entry`=42934 LIMIT 1;

-- Chimaeron (Blackwing Descent Updates)

-- Chimaeron sleep Aura
REPLACE INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(1082137, 0, 0, 0, 1, 0,'84186 0');

UPDATE `creature_template` SET `ScriptName`='boss_chimaeron' WHERE `entry` = 43296;
UPDATE `creature_model_info` SET `combat_reach`=8 WHERE `modelid`=33308 LIMIT 1;

-- Finkle Einhorn
UPDATE `creature_template` SET `npcflag` = 1, `ScriptName`='mob_finkle_einhorn' WHERE `entry` = 44202;

/*
REPLACE INTO `gossip_menu` (`entry`, `text_id`) VALUES
(60050, 310000);

DELETE FROM `npc_text` WHERE `ID` IN(310000);
INSERT INTO `npc_text`(`ID`,`text0_0`,`text0_1`) VALUES
(310000,'Leaping Leper Gnomes! You\'re a sight for sore eyes. I was worried the giant magma worm out front would deter visitors. Now that you\'re here you can give me a hand.','testtesttest');

REPLACE INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `action_script_id`, `box_coded`, `box_money`, `box_text`) VALUES
(60050, 0, 0, 'Leaping Leper Gnomes! You\'re a sight for sore eyes. I was worried the giant magma worm out front would deter visitors. Now that you\'re here you can give me a hand.', 0, 0, 0, 0, 0, 0, 0, NULL);
*/

-- Bile O Tron
UPDATE `creature_template` SET `ScriptName`='mob_bile_o_tron' WHERE `entry` = 44418;
UPDATE `creature_template` SET `InhabitType`=5 WHERE `entry` = 44418;

-- Maloriak (Blackwing Descent) Updates

UPDATE `creature_template` SET `AIName`='', `ScriptName`='boss_maloriak' WHERE `entry`=41378 LIMIT 1;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 41378;

UPDATE `creature_model_info` SET `combat_reach`=6 WHERE `modelid`=33186 LIMIT 1;

DELETE FROM `creature` WHERE `id` = 41440;

DELETE FROM `creature_template` WHERE `entry` = 41377;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES (41377, 0, 0, 0, 0, 0, 11686, 0, 0, 0, 'Release Abberations Trigger', '', '', 0, 83, 83, 0, 16, 16, 0, 1, 1.14286, 1, 0, 3.8, 3.8, 0, 46, 1, 0, 0, 1, 33554948, 0, 0, 0, 0, 0, 0, 1.9, 1.9, 5000, 10, 1024, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, '', 1);

-- Prime Subjects
UPDATE `creature_template` SET `faction_A`=16, `faction_H`=16, `rank`=2 WHERE `entry` = 41841;

-- Flash Freeze
UPDATE `creature_template` SET `ScriptName`='mob_flash_freeze_maloriak', `unit_flags`=518, `type_flags`=0, `minlevel`=88, `maxlevel`=88, `faction_A`=16, `faction_H`=16 , `modelid1`=11686, `modelid2`=0, `modelid3`=0, `modelid4`=0 WHERE `entry`=41576;

REPLACE INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`)
VALUES (41576, 0, 0, 0, 0, 0, '92980 0');

/*****
* Golem Sentry
*****/
SET @ENTRY := 42800;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,30,15000,15000,21000,24000,11,81055,1,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Golem Sentry - Electrical Discharge"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,30,7000,7000,13000,16000,11,81056,1,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Golem Sentry - Flash Bomb"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,30,12000,14000,38000,42000,11,81063,1,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Golem Sentry - Laser Strike");

-- Flash Bomb
SET @ENTRY := 43361;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,30,0,0,0,0,11,91885,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Flash Bomb");

UPDATE `creature_template` SET `unit_flags`=33554436, `type_flags`=1024 WHERE `entry`=43361 LIMIT 1;

-- Laser Strike (43362)
DELETE FROM `smart_scripts` WHERE `entryorguid`=43362;
DELETE FROM `creature_template_addon` WHERE `entry` = 43362;
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`)
VALUES (43362, 0, 0, 0, 0, 0, '81065 0 81066 0');

UPDATE `creature_template` SET `unit_flags`=33554436, `type_flags`=1024, `faction_H`=16, `faction_A`=16, AIName="" WHERE `entry`=43362 LIMIT 1;