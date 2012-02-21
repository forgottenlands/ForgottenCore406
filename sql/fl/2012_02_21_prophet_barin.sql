UPDATE `creature_template` SET `difficulty_entry_1`=48951 WHERE  `entry`=43612;
UPDATE `creature_template` SET `ScriptName`='' WHERE  `entry`=48906;
UPDATE `creature_template` SET `faction_A`=16, `faction_H`=16 WHERE  `entry`=43801;

INSERT INTO `creature_onkill_reward` (`creature_id`, `CurrencyId1`, `CurrencyCount1`, `RewOnKillRepFaction1`, `RewOnKillRepFaction2`, `MaxStanding1`, `RewOnKillRepValue1`, `MaxStanding2`, `RewOnKillRepValue2`, `TeamDependent`) VALUES 
(48951, 395, 7000, 1177, 1178, 7, 400, 7, 400, 1),
(43612, 395, 3000, 1177, 1178, 7, 300, 7, 300, 1);