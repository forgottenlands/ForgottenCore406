INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES 
(86788, 'spell_blackout'),
(92876, 'spell_blackout'),
(92877, 'spell_blackout'),
(92878, 'spell_blackout'),
(86840, 'spell_devouring_flame');
UPDATE `creature_template` SET `modelid1`=11686, `minlevel`=85, `maxlevel`=85, `exp`=3, `Health_mod`=20000, `flags_extra`=2 WHERE  `entry`=46588;