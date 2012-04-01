DELETE FROM `spell_proc_event` WHERE `entry` IN (51127, 51123, 51128);
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES 
(51123, 1, 15, 0, 0, 0, 4, 0, 2, 100, 0),
(51127, 1, 15, 0, 0, 0, 4, 0, 3, 100, 0),
(51128, 1, 15, 0, 0, 0, 4, 0, 5, 100, 0);