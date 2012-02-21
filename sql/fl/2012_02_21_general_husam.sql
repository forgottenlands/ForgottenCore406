INSERT INTO `creature_onkill_reward` (`creature_id`, `CurrencyId1`, `CurrencyCount1`, `RewOnKillRepFaction1`, `RewOnKillRepFaction2`, `MaxStanding1`, `RewOnKillRepValue1`, `MaxStanding2`, `RewOnKillRepValue2`, `TeamDependent`) VALUES 
(48932, 395, 7000, 1177, 1178, 7, 400, 7, 400, 1),
(44577, 395, 3000, 1177, 1178, 7, 300, 7, 300, 1);

UPDATE `creature_template` SET `AIName`='' WHERE  `entry`=44577;
DELETE FROM `smart_scripts` WHERE  `entryorguid`=44577;

