UPDATE `creature_template` SET `mechanic_immune_mask`=0 WHERE  `entry`=39708;
UPDATE `creature_template` SET `mechanic_immune_mask`=0 WHERE  `entry`=39709;
UPDATE `creature_template` SET `mechanic_immune_mask`=0 WHERE  `entry`=39978;
UPDATE `creature_template` SET `mechanic_immune_mask`=0 WHERE  `entry`=39979;
UPDATE `creature_template` SET `mechanic_immune_mask`=0 WHERE  `entry`=39980;
UPDATE `creature_template` SET `mechanic_immune_mask`=0 WHERE  `entry`=39981;
UPDATE `creature_template` SET `mechanic_immune_mask`=0 WHERE  `entry`=39982;
UPDATE `creature_template` SET `mechanic_immune_mask`=0 WHERE  `entry`=39985;
UPDATE `creature_template` SET `mechanic_immune_mask`=0 WHERE  `entry`=39983;
UPDATE `creature_template` SET `mechanic_immune_mask`=0 WHERE  `entry`=39986;
UPDATE `creature_template` SET `mechanic_immune_mask`=0 WHERE  `entry`=39987;
UPDATE `creature_template` SET `mechanic_immune_mask`=0 WHERE  `entry`=39990;
UPDATE `creature_template` SET `mechanic_immune_mask`=0 WHERE  `entry`=39988;
UPDATE `creature_template` SET `mechanic_immune_mask`=0 WHERE  `entry`=39991;
UPDATE `creature_template` SET `mechanic_immune_mask`=0 WHERE  `entry`=40017;
UPDATE `creature_template` SET `mechanic_immune_mask`=0 WHERE  `entry`=40018;
UPDATE `creature_template` SET `mechanic_immune_mask`=0 WHERE  `entry`=40019;
UPDATE `creature_template` SET `mechanic_immune_mask`=0 WHERE  `entry`=40020;
UPDATE `creature_template` SET `mechanic_immune_mask`=0 WHERE  `entry`=40021;
UPDATE `creature_template` SET `mechanic_immune_mask`=0 WHERE  `entry`=40022;
UPDATE `creature_template` SET `mechanic_immune_mask`=0 WHERE  `entry`=40023;
UPDATE `creature_template` SET `mechanic_immune_mask`=0 WHERE  `entry`=40024;
UPDATE `creature_template` SET `mechanic_immune_mask`=0 WHERE  `entry`=50284;
UPDATE `creature_template` SET `mechanic_immune_mask`=0 WHERE  `entry`=50285;

INSERT INTO `creature_onkill_reward` (`creature_id`, `RewOnKillRepFaction1`, `RewOnKillRepFaction2`, `MaxStanding1`, `RewOnKillRepValue1`, `MaxStanding2`, `RewOnKillRepValue2`, `TeamDependent`) VALUES 
(39709, 1177, 1178, 7, 11, 7, 11, 1),
(39979, 1177, 1178, 7, 11, 7, 11, 1),
(39981, 1177, 1178, 7, 11, 7, 11, 1),
(39983, 1177, 1178, 7, 11, 7, 11, 1),
(39986, 1177, 1178, 7, 11, 7, 11, 1),
(39988, 1177, 1178, 7, 11, 7, 11, 1),
(39991, 1177, 1178, 7, 11, 7, 11, 1),
(40018, 1177, 1178, 7, 11, 7, 11, 1),
(40020, 1177, 1178, 7, 11, 7, 11, 1),
(40022, 1177, 1178, 7, 11, 7, 11, 1),
(40024, 1177, 1178, 7, 11, 7, 11, 1),
(40085, 1177, 1178, 7, 11, 7, 11, 1),
(39666, 1177, 1178, 7, 100, 7, 100, 1),
(39680, 1177, 1178, 7, 100, 7, 100, 1),
(39699, 1177, 1178, 7, 100, 7, 100, 1),
(39701, 1177, 1178, 7, 100, 7, 100, 1),
(39706, 1177, 1178, 7, 100, 7, 100, 1),
(50285, 1177, 1178, 7, 11, 7, 11, 1);

UPDATE `creature_template` SET `Health_mod`=0.5 WHERE  `entry`=40447 LIMIT 1;