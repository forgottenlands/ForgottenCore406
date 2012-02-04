DELETE FROM `spell_proc_event` WHERE `entry` IN (85416, 75806, 85043);
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES 
(85416, 1, 10, 0, 0, 0, 0, 65536, 0, 100, 0), -- Grafic spell
(75806, 1, 10, 0, 0, 0, 16, 0, 0, 10, 0), -- Effect Spell
(85043, 1, 10, 0, 0, 0, 16, 0, 0, 20, 0);
