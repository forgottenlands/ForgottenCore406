UPDATE `creature_template` SET `ScriptName`='boss_siamat' WHERE  `entry`=44819;
UPDATE `creature_template` SET `ScriptName`='npc_servant_of_siamat' WHERE  `entry`=45269;
UPDATE `creature_template` SET `ScriptName`='npc_minion_of_siamat' WHERE  `entry`=44704;
UPDATE `creature_template` SET `ScriptName`='npc_cloud_storm' WHERE  `entry`=44541;
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `faction_A`=16, `faction_H`=16, `modelid1`=31687, `modelid2`=0 WHERE  `entry`=44541;

INSERT INTO `creature_onkill_reward` (`creature_id`, `CurrencyId1`, `CurrencyCount1`, `RewOnKillRepFaction1`, `RewOnKillRepFaction2`, `MaxStanding1`, `RewOnKillRepValue1`, `MaxStanding2`, `RewOnKillRepValue2`, `TeamDependent`) VALUES 
(51088, 395, 7000, 1177, 1178, 7, 400, 7, 400, 1),
(44819, 395, 3000, 1177, 1178, 7, 300, 7, 300, 1);