DELETE FROM `areatrigger_scripts` WHERE `entry`=6625;
DELETE FROM `areatrigger_scripts` WHERE `entry`=6626;
DELETE FROM `areatrigger_scripts` WHERE `entry`=6627;
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES (6625, 'at_bt_council_1');
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES (6626, 'at_bt_council_2');
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES (6627, 'at_bt_council_3');

UPDATE `creature_template` SET `ScriptName`='boss_feludius' WHERE `entry`=43687;
UPDATE `creature_template` SET `ScriptName`='boss_ignacious' WHERE `entry`=43686;
UPDATE `creature_template` SET `ScriptName`='boss_arion' WHERE `entry`=43688;
UPDATE `creature_template` SET `ScriptName`='boss_terrastra' WHERE `entry`=43689;
UPDATE `creature_template` SET `ScriptName`='boss_elementium_monstrosity' WHERE `entry`=43735;
UPDATE `creature_template` SET `ScriptName`='npc_violent_cyclone' WHERE `entry`=44747;
UPDATE `creature_template` SET `ScriptName`='npc_bt_gravity_well' WHERE `entry`=44824;
UPDATE `creature_template` SET `ScriptName`='npc_liquid_ice' WHERE `entry`=45452;
UPDATE `creature_template` SET `ScriptName`='npc_ascendant_council_plume_stalker' WHERE `entry`=45420;
UPDATE `creature_template` SET `ScriptName`='npc_eruption_target' WHERE `entry`=44845;

DELETE FROM `spell_script_names` WHERE `spell_id`=82746;
DELETE FROM `spell_script_names` WHERE `spell_id`=92506;
DELETE FROM `spell_script_names` WHERE `spell_id`=92507;
DELETE FROM `spell_script_names` WHERE `spell_id`=92508;
DELETE FROM `spell_script_names` WHERE `spell_id`=83300;
DELETE FROM `spell_script_names` WHERE `spell_id`=83067;
DELETE FROM `spell_script_names` WHERE `spell_id`=92469;
DELETE FROM `spell_script_names` WHERE `spell_id`=92470;
DELETE FROM `spell_script_names` WHERE `spell_id`=92471;
DELETE FROM `spell_script_names` WHERE `spell_id`=83565;
DELETE FROM `spell_script_names` WHERE `spell_id`=92544;
DELETE FROM `spell_script_names` WHERE `spell_id`=92545;
DELETE FROM `spell_script_names` WHERE `spell_id`=92546;
DELETE FROM `spell_script_names` WHERE `spell_id`=83675;
DELETE FROM `spell_script_names` WHERE `spell_id`=83087;
DELETE FROM `spell_script_names` WHERE `spell_id`=83498;
DELETE FROM `spell_script_names` WHERE `spell_id`=92476;
DELETE FROM `spell_script_names` WHERE `spell_id`=92477;
DELETE FROM `spell_script_names` WHERE `spell_id`=92478;
DELETE FROM `spell_script_names` WHERE `spell_id`=83581;
DELETE FROM `spell_script_names` WHERE `spell_id`=84918;
DELETE FROM `spell_script_names` WHERE `spell_id`=82285;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (82746, 'spell_feludius_glaciate');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (92506, 'spell_feludius_glaciate');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (92507, 'spell_feludius_glaciate');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (92508, 'spell_feludius_glaciate');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (83300, 'spell_arion_chain_lightning');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (83067, 'spell_arion_thundershock');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (92469, 'spell_arion_thundershock');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (92470, 'spell_arion_thundershock');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (92471, 'spell_arion_thundershock');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (83565, 'spell_terrastra_quake');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (92544, 'spell_terrastra_quake');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (92545, 'spell_terrastra_quake');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (92546, 'spell_terrastra_quake');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (83675, 'spell_terrastra_eruption');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (83087, 'spell_arion_disperse');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (83498, 'spell_arion_lashing_winds');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (92476, 'spell_arion_lashing_winds');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (92477, 'spell_arion_lashing_winds');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (92478, 'spell_arion_lashing_winds');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (83581, 'spell_terrastra_grounded');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (84918, 'spell_monstrosity_cryogenic_aura');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (82285, 'spell_elemental_statis');

DELETE FROM `creature_text` WHERE `entry` = 43687;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`)
VALUES (43687, 0, 0, 'You dare invade our lord\'s sanctum?', 1, 0, 0, 0, 0, 20162, 'VO_BT_Feludius_Event01');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`)
VALUES (43687, 1, 0, 'Perish!', 1, 0, 0, 0, 0, 20163, 'VO_BT_Feludius_Event02');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`)
VALUES (43687, 2, 0, 'I will freeze the blood in your veins!', 1, 0, 0, 0, 0, 20164, 'VO_BT_Feludius_Event03');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`)
VALUES (43687, 3, 0, 'But now, witness true power...', 1, 0, 0, 0, 0, 20165, 'VO_BT_Feludius_Event04');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`)
VALUES (43687, 4, 0, 'BEHOLD YOUR DOOM!', 1, 0, 0, 0, 0, 20166, 'VO_BT_Feludius_Event05');

DELETE FROM `creature_text` WHERE `entry` = 43686;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`)
VALUES (43686, 0, 0, 'You will die for your insolence!', 1, 0, 0, 0, 0, 20285, 'VO_BT_Ignacious_Event01');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`)
VALUES (43686, 1, 0, 'More fuel for the fire!', 1, 0, 0, 0, 0, 20286, 'VO_BT_Ignacious_Event02');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`)
VALUES (43686, 2, 0, 'BURN!', 1, 0, 0, 0, 0, 20287, 'VO_BT_Ignacious_Event03');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`)
VALUES (43686, 3, 0, '...the fury of the elements!', 1, 0, 0, 0, 0, 20288, 'VO_BT_Ignacious_Event04');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`)
VALUES (43686, 4, 0, 'BEHOLD YOUR DOOM!', 1, 0, 0, 0, 0, 20289, 'VO_BT_Ignacious_Event05');

DELETE FROM `creature_text` WHERE `entry` = 43688;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`)
VALUES (43688, 0, 0, 'Enough of this foolishness!', 1, 0, 0, 0, 0, 20237, 'VO_BT_Arion_Event01');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`)
VALUES (43688, 1, 0, 'Merely a whisper in the wind...', 1, 0, 0, 0, 0, 20238, 'VO_BT_Arion_Event02');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`)
VALUES (43688, 2, 0, 'Wind, hear my call!', 1, 0, 0, 0, 0, 20239, 'VO_BT_Arion_Event03');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`)
VALUES (43688, 3, 0, 'An impressive display...', 1, 0, 0, 0, 0, 20240, 'VO_BT_Arion_Event04');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`)
VALUES (43688, 4, 0, 'BEHOLD YOUR DOOM!', 1, 0, 0, 0, 0, 20241, 'VO_BT_Arion_Event05');

DELETE FROM `creature_text` WHERE `entry` = 43689;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`)
VALUES (43689, 0, 0, 'The soil welcomes your bones!', 1, 0, 0, 0, 0, 21842, 'VO_BT_Terrastra_Event01');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`)
VALUES (43689, 1, 0, 'We will handle them!', 1, 0, 0, 0, 0, 21843, 'VO_BT_Terrastra_Event02');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`)
VALUES (43689, 2, 0, 'The earth will devour you!', 1, 0, 0, 0, 0, 21844, 'VO_BT_Terrastra_Event03');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`)
VALUES (43689, 3, 0, '...to have made it this far.', 1, 0, 0, 0, 0, 21845, 'VO_BT_Terrastra_Event04');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`)
VALUES (43689, 4, 0, 'BEHOLD YOUR DOOM!', 1, 0, 0, 0, 0, 21846, 'VO_BT_Terrastra_Event05');

DELETE FROM `creature_text` WHERE `entry` = 43735;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`)
VALUES (43735, 0, 0, 'BEHOLD YOUR DOOM!', 1, 0, 0, 0, 0, 20396, 'VO_BT_Monstrosity_Event01');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`)
VALUES (43735, 1, 0, 'Annihilate...', 1, 0, 0, 0, 0, 20397, 'VO_BT_Monstrosity_Event02');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`)
VALUES (43735, 2, 0, 'Eradicate...', 1, 0, 0, 0, 0, 20398, 'VO_BT_Monstrosity_Event03');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`)
VALUES (43735, 3, 0, 'Impossible...', 1, 0, 0, 0, 0, 20399, 'VO_BT_Monstrosity_Event04');
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`)
VALUES (43735, 4, 0, 'FEEL THE POWER!', 1, 0, 0, 0, 0, 20400, 'VO_BT_Monstrosity_Event05');