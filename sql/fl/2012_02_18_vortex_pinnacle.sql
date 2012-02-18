-- Trash levels
UPDATE `creature_template` SET `maxlevel`=83 WHERE  `entry`=45915;
UPDATE `creature_template` SET `maxlevel`=83 WHERE  `entry`=45912;
UPDATE `creature_template` SET `maxlevel`=83 WHERE  `entry`=45704;
-- Boss
UPDATE `creature_template` SET `AIName`='' WHERE  `entry`=43873;
UPDATE `creature_template` SET `AIName`='' WHERE  `entry`=43875;
UPDATE `creature_template` SET `AIName`='' WHERE  `entry`=43878;
UPDATE `creature_template` SET `ScriptName`='boss_asaad' WHERE  `entry`=43875;
UPDATE `creature_template` SET `ScriptName`='boss_grand_vizier_ertan' WHERE  `entry`=43878;
-- SmartAI delete
DELETE FROM `smart_scripts` WHERE  `entryorguid`=43873 AND `source_type`=0 AND `id`=0 AND `link`=0 LIMIT 1;
DELETE FROM `smart_scripts` WHERE  `entryorguid`=43875 AND `source_type`=0 AND `id`=0 AND `link`=0 LIMIT 1;
DELETE FROM `smart_scripts` WHERE  `entryorguid`=43875 AND `source_type`=0 AND `id`=1 AND `link`=0 LIMIT 1;
DELETE FROM `smart_scripts` WHERE  `entryorguid`=43875 AND `source_type`=0 AND `id`=2 AND `link`=0 LIMIT 1;
DELETE FROM `smart_scripts` WHERE  `entryorguid`=43878 AND `source_type`=0 AND `id`=0 AND `link`=0 LIMIT 1;
-- Instance script
UPDATE `instance_template` SET `script`='instance_vortex_pinnacle' WHERE  `map`=657;