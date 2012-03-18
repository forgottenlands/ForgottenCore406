-- Innkeeper Geno
UPDATE `creature_template` SET `unit_flags`='32768' WHERE (`entry`='49783');
UPDATE `creature_template` SET `dynamicflags`='8' WHERE (`entry`='49783');
UPDATE `creature_template` SET `npcflag`='66177' WHERE (`entry`='49783');
UPDATE `creature_template` SET `ScriptName`='npc_innkeeper' WHERE (`entry`='49783');
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES ('49783', '58256');
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES ('49783', '58257');
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES ('49783', '58260');
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES ('49783', '58261');
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES ('49783', '58268');
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES ('49783', '58269');
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES ('49783', '58274');
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES ('49783', '58275');
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES ('49783', '58280');

-- Innkeeper Lutz
UPDATE `creature_template` SET `unit_flags`='32768' WHERE (`entry`='49498');
UPDATE `creature_template` SET `dynamicflags`='8' WHERE (`entry`='49498');
UPDATE `creature_template` SET `npcflag`='66177' WHERE (`entry`='49498');
UPDATE `creature_template` SET `ScriptName`='npc_innkeeper' WHERE (`entry`='49498');

-- Innkeeper Krum
UPDATE `creature_template` SET `unit_flags`='32768' WHERE (`entry`='49747');
UPDATE `creature_template` SET `dynamicflags`='8' WHERE (`entry`='49747');
UPDATE `creature_template` SET `npcflag`='66177' WHERE (`entry`='49747');
UPDATE `creature_template` SET `ScriptName`='npc_innkeeper' WHERE (`entry`='49747');
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES ('49747', '58256');
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES ('49747', '58257');
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES ('49747', '58260');
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES ('49747', '58261');
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES ('49747', '58268');
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES ('49747', '58269');
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES ('49747', '58274');
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES ('49747', '58275');
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES ('49747', '58280');

-- Innkeeper Nerius
UPDATE `creature_template` SET `unit_flags`='32768' WHERE (`entry`='43141');
UPDATE `creature_template` SET `dynamicflags`='8' WHERE (`entry`='43141');
UPDATE `creature_template` SET `npcflag`='66177' WHERE (`entry`='43141');
UPDATE `creature_template` SET `ScriptName`='npc_innkeeper' WHERE (`entry`='43141');
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES ('43141', '58256');
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES ('43141', '58260');
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES ('43141', '58274');
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES ('43141', '58279');

-- Innkeeper Nerius Fake 4.2.0
DELETE FROM `creature_template` WHERE (`entry`='47108');

-- Innkeeper Turk
UPDATE `creature_template` SET `unit_flags`='32768' WHERE (`entry`='49762');
UPDATE `creature_template` SET `dynamicflags`='8' WHERE (`entry`='49762');
UPDATE `creature_template` SET `npcflag`='66177' WHERE (`entry`='49762');
UPDATE `creature_template` SET `ScriptName`='npc_innkeeper' WHERE (`entry`='49762');
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES ('49762', '58256');
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES ('49762', '58257');
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES ('49762', '58260');
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES ('49762', '58261');
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES ('49762', '58268');
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES ('49762', '58269');
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES ('49762', '58274');
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES ('49762', '58275');
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES ('49762', '58280');

-- Zun'Ja
UPDATE `creature_template` SET `unit_flags`='32768' WHERE (`entry`='42908');
UPDATE `creature_template` SET `dynamicflags`='8' WHERE (`entry`='42908');
UPDATE `creature_template` SET `npcflag`='66177' WHERE (`entry`='42908');
UPDATE `creature_template` SET `ScriptName`='npc_innkeeper' WHERE (`entry`='42908');
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES ('42908', '58256');
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES ('42908', '58260');
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES ('42908', '58274');
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES ('42908', '58279');
