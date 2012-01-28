UPDATE `creature_template` SET `ScriptName`='boss_beauty', `AIName`='' WHERE `entry`=39700;
UPDATE `creature_template` SET `ScriptName`='npc_runty' WHERE `entry`=40015;

DELETE FROM `smart_scripts` where `entryorguid` IN(40008, 39700, 40011, 40013);

UPDATE `creature_template` SET `ScriptName`='npc_beauty_family' WHERE  `entry`=40008;
UPDATE `creature_template` SET `ScriptName`='npc_beauty_family' WHERE  `entry`=40011;
UPDATE `creature_template` SET `ScriptName`='npc_beauty_family' WHERE  `entry`=40013;

DELETE FROM `creature_onkill_reward` WHERE  `creature_id`=39701;