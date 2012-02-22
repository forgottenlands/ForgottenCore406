UPDATE `creature_template` SET `flags_extra`=1, `ScriptName`='boss_lockmaw' WHERE  `entry`=43614;
UPDATE `creature` SET `spawnMask`=2, `spawndist`=0, `MovementType`=0 WHERE `id`=49045;

INSERT INTO `creature_onkill_reward` (`creature_id`, `CurrencyId1`, `CurrencyCount1`, `RewOnKillRepFaction1`, `RewOnKillRepFaction2`, `MaxStanding1`, `RewOnKillRepValue1`, `MaxStanding2`, `RewOnKillRepValue2`, `TeamDependent`) VALUES 
(49045, 395, 7000, 1177, 1178, 7, 400, 7, 400, 1),
(43614, 395, 3000, 1177, 1178, 7, 300, 7, 300, 1);