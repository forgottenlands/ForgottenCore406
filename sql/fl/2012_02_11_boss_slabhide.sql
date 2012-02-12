-- Stalagmite display
UPDATE `gameobject_template` SET `displayId`=10085 WHERE  `entry`=204337;
-- Boss template
UPDATE `creature_template` SET `AIName`='', `InhabitType`=1, `ScriptName`='boss_slabhide' WHERE  `entry`=43214;
UPDATE `creature_template` SET `InhabitType`=1 WHERE  `entry`=49538;
-- boss Spawn
REPLACE INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(1088259, 43214, 725, 3, 1, 0, 0, 1295.43, 1229.27, 247.058, 3.65643, 86400, 0, 0, 2450848, 0, 0, 0, 0, 0, 0);
-- Trigger template
UPDATE `creature_template` SET `modelid2`=0, `modelid3`=0, `modelid4`=0 WHERE  `entry`=43357;
UPDATE `creature_template` SET `modelid2`=0, `modelid3`=0, `modelid4`=0 WHERE  `entry`=43159;
-- Lava fissure template 
UPDATE `creature_template` SET `ScriptName`='npc_lava_fissure',`faction_A`=16, `faction_H`=16, `minlevel`=85, `maxlevel`=85 WHERE  `entry`=43242;
-- Stalactite summoner
INSERT INTO `creature_template` (`entry`, `modelid1`, `name`, `minlevel`, `maxlevel`, `faction_A`, `faction_H`, `ScriptName`) VALUES 
(200000, 11686, 'Stalactite Summoner', 85, 85, 35, 35, 'npc_stalactite_summoner');
-- Stalactite trigger
UPDATE `creature_template` SET `faction_A`=16, `faction_H`=16, `Health_mod`=1000, `ScriptName`='npc_stalactite_base' WHERE  `entry`=43159;
UPDATE `creature_template` SET `flags_extra`=2 WHERE  `entry`=43159;
UPDATE `creature_template` SET `flags_extra`=2 WHERE  `entry`=43242;