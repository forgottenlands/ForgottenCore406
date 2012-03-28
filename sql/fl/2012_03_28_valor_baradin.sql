DELETE FROM `creature_onkill_reward` WHERE `creature_id` IN (47120, 51350);
INSERT INTO `creature_onkill_reward` (`creature_id`, `CurrencyId1`, `CurrencyCount1`, `RewOnKillRepFaction1`, `RewOnKillRepFaction2`, `MaxStanding1`, `RewOnKillRepValue1`, `MaxStanding2`, `RewOnKillRepValue2`, `TeamDependent`) VALUES 
(47120, 396, 7000, 1177, 1178, 7, 250, 7, 250, 1),
(51350, 396, 9000, 1177, 1178, 7, 250, 7, 250, 1);