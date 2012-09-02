DELETE FROM `spell_script_names` WHERE  `spell_id`=86105 AND `ScriptName`='spell_warl_Jinx';
DELETE FROM `spell_script_names` WHERE  `spell_id`=85547 AND `ScriptName`='spell_warl_Jinx';
DELETE FROM `spell_script_names` WHERE  `spell_id`=1490 AND `ScriptName`='spell_warl_Curse_of_the_Elements';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (1490, 'spell_warl_curse_of_the_elements');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (702, -85547, 0, 'Jinx rank 1: Curse removes jinx');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (18223, -85547, 0, 'Jinx rank 1: Curse removes jinx');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (1714, -85547, 0, 'Jinx rank 1: Curse removes jinx');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (702, -85547, 2, 'Jinx rank 1: cannot override the curse');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (18223, -85547, 2, 'Jinx rank 1: cannot override the curse');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (1714, -85547, 2, 'Jinx rank 1: cannot override the curse');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (702, -86105, 0, 'Jinx rank 2: Curse removes jinx');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (18223, -86105, 0, 'Jinx rank 2: Curse removes jinx');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (1714, -86105, 0, 'Jinx rank 2: Curse removes jinx');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (702, -86105, 2, 'Jinx rank 2: cannot override the curse');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (18223, -86105, 2, 'Jinx rank 2: cannot override the curse');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (1714, -86105, 2, 'Jinx rank 2: cannot override the curse');