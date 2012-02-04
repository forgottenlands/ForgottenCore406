DELETE FROM `spell_proc_event` WHERE `entry` IN (20911, 84628, 84629);
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES 
(20911, 0, 0, 0, 0, 0, 0, 112, 0, 0, 0),
(84628, 0, 0, 0, 0, 0, 0, 112, 0, 0, 0),
(84629, 0, 0, 0, 0, 0, 0, 112, 0, 0, 0);