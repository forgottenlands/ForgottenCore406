-- Varie Quest e NPC 42467
UPDATE `creature_template` SET `npcflag`='3' WHERE (`entry`='42467');

INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES ('42467', '26871');
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES ('42467', '26328');
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES ('42467', '26376');
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES ('42467', '26377');
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES ('42467', '26426');

INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES ('42467', '26869');
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES ('42467', '26436');
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES ('42467', '26376');
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES ('42467', '26377');
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES ('42467', '26426');