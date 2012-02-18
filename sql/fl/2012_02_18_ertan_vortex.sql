UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `modelid1`=11686, `modelid2`=0, `faction_A`=16, `faction_H`=16, `unit_flags`=33554434, `flags_extra`=2, `ScriptName`='npc_ertan_vortex' WHERE  `entry`=46007;
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES 
(46007, '86267 0');
INSERT INTO `creature_onkill_reward` (`creature_id`, `CurrencyId1`, `CurrencyCount1`) VALUES 
(43879, 395, 7000),
(43878, 395, 3000);