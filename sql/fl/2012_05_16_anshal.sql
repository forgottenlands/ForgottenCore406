UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `faction_A`=16, `faction_H`=16, `speed_walk`=0, `unit_flags`=6, `speed_run`=0 WHERE `entry`=46246;
UPDATE `creature_template` SET `modelid2`=0, `modelid3`=0, `modelid4`=0, `ScriptName`='npc_ravenous_creeper_trigger' WHERE  `entry`=45813;
UPDATE `creature_template` SET `difficulty_entry_1`=50100, `difficulty_entry_2`=50110, `difficulty_entry_3`=50120, `ScriptName`='npc_ravenous_creeper', `Health_mod`=103070 WHERE `entry`=45812;
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`, `faction_A`=14, `faction_H`=14, `mechanic_immune_mask`=16 WHERE `entry` IN (45812, 50100, 50110, 50120);
UPDATE `creature_template` SET `Health_mod`=343568 WHERE `entry`=50100; 
UPDATE `creature_template` SET `Health_mod`=206141 WHERE `entry`=50110;
UPDATE `creature_template` SET `Health_mod`=687136 WHERE `entry`=50120;  