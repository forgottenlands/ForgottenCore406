UPDATE `creature_template` SET `npcflag`=1, `InhabitType`=5, `ScriptName`='npc_wind_tunnel' WHERE  `entry`=48092;
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES 
(48092, '89698 0');

INSERT INTO `creature` (`id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(48092, 755, 2, 1, 0, 0, -10939.7, -1288.88, 10.807, 3.07844, 300, 0, 0, 64496, 0, 0, 0, 0, 0, 0);
