INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES 
(80524, 'spell_gen_jade_crystal');

UPDATE `quest_template` SET `NextQuestId`=26871 WHERE  `entry`=26426 LIMIT 1;
UPDATE `quest_template` SET `RewRepValue1`=1400000 WHERE  `entry`=26871 LIMIT 1;
UPDATE `creature_template` SET `npcflag`=3, `ScriptName`='npc_tawn_winterbluff' WHERE  `entry`=44674 LIMIT 1;