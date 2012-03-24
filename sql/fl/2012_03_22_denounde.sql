DELETE FROM `spell_proc_event` WHERE `entry` IN (31825, 85510);
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES 
(31825, 2, 10, 0, 0, 0, 81920, 0, 0, 25, 0),
(85510, 2, 10, 0, 0, 0, 81920, 0, 0, 50, 0);