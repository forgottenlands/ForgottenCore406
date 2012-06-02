-- Fix flight masters around the Dark Portal in Outland 

-- Vlagga Freyfeather SAI
SET @NPC := 18930;
SET @GOSSIP_VLAGGA := 7938;
SET @SPELL_STAIR_OF_DESTINY_THRALLMAR := 34924;
DELETE FROM `creature_ai_scripts` WHERE `creature_id` =@NPC;
UPDATE `creature_template` SET `AIName`= "SmartAI" WHERE `entry` =@NPC;
DELETE FROM `smart_scripts` WHERE `entryorguid` =@NPC;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@NPC,0,0,0,62,0,100,0,@GOSSIP_VLAGGA,1,0,0,11,@SPELL_STAIR_OF_DESTINY_THRALLMAR,2,0,0,0,0,7,0,0,0,0,0,0,0,"Vlagga Freyfeather - On Gossip Select - Cast Stair of Destiny to Thrallmar"),
(@NPC,0,1,2,4,0,100,0,0,0,0,0,12,9297,4,30000,0,0,0,1,0,0,0,0,0,0,0,"Vlagga Freyfeather - On Aggro - Summon Enraged Wyvern"),
(@NPC,0,2,3,61,0,100,0,0,0,0,0,12,9297,4,30000,0,0,0,1,0,0,0,0,0,0,0,"Vlagga Freyfeather - On Aggro - Summon Enraged Wyvern"),
(@NPC,0,3,0,61,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Vlagga Freyfeather - On Aggro - Say Line 0");

-- Amish Wildhammer SAI
SET @NPC := 18931;
SET @GOSSIP_AMISH := 7939;
SET @SPELL_STAIR_OF_DESTINY_HONOR_HOLD := 34907;
DELETE FROM `creature_ai_scripts` WHERE `creature_id` =@NPC;
UPDATE `creature_template` SET `AIName`= "SmartAI" WHERE `entry` =@NPC;
DELETE FROM `smart_scripts` WHERE `entryorguid` =@NPC;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@NPC,0,0,0,62,0,100,0,@GOSSIP_AMISH,1,0,0,11,@SPELL_STAIR_OF_DESTINY_HONOR_HOLD,2,0,0,0,0,7,0,0,0,0,0,0,0,"Amish Wildhammer - On Gossip Select - Cast Stair of Destiny to Honor Hold"),
(@NPC,0,1,2,4,0,100,0,0,0,0,0,12,9526,4,30000,0,0,0,1,0,0,0,0,0,0,0,"Amish Wildhammer - On Aggro - Summon Enraged Gryphon"),
(@NPC,0,2,3,61,0,100,0,0,0,0,0,12,9526,4,30000,0,0,0,1,0,0,0,0,0,0,0,"Amish Wildhammer - On Aggro - Summon Enraged Gryphon"),
(@NPC,0,3,0,61,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Amish Wildhammer - On Aggro - Say Line 0");

-- Gossip inserts
DELETE FROM `gossip_menu` WHERE `entry`=@GOSSIP_AMISH;
DELETE FROM `npc_text` WHERE `ID` IN (9935,9991);
INSERT INTO `gossip_menu` (`entry`,`text_id`) VALUES (@GOSSIP_AMISH,10052);
DELETE FROM `gossip_menu_option` WHERE `menu_id` IN (@GOSSIP_AMISH,@GOSSIP_VLAGGA);
INSERT INTO `gossip_menu_option` (`menu_id`,`id`,`option_icon`,`option_text`,`option_id`,`npc_option_npcflag`,`action_menu_id`,`action_poi_id`,`box_coded`,`box_money`,`box_text`) VALUES
(@GOSSIP_AMISH,0,2,"Show me where I can fly.",4,8192,0,0,0,0,''),
(@GOSSIP_AMISH,1,2,"Send me to Honor Hold!",4,8192,0,0,0,0,''),
(@GOSSIP_VLAGGA,0,2,"Show me where I can fly.",4,8192,0,0,0,0,''),
(@GOSSIP_VLAGGA,1,2,"Send me to Thrallmar!",4,8192,0,0,0,0,'');

-- Gossip conditions
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=15 AND `SourceGroup` IN (@GOSSIP_AMISH,@GOSSIP_VLAGGA);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(15,@GOSSIP_AMISH,0,0,0, 8,0,10140,0,'',"Show gossip option 0 if player has rewarded quest Journey to Honor Hold"),
(15,@GOSSIP_AMISH,1,0,0,28,0,10140,0,'',"Show gossip option 1 if player has complete quest Journey to Honor Hold"),
(15,@GOSSIP_VLAGGA,0,0,0, 8,0,10289,0,'',"Show gossip option 0 if player has rewarded quest Journey to Thrallmar"),
(15,@GOSSIP_VLAGGA,1,0,0,28,0,10289,0,'',"Show gossip option 1 if player has complete quest Journey to Thrallmar");