-- _Quest: return of the Lich Hunter
UPDATE `creature_template` SET `ScriptName`='' WHERE (`entry`='28138');

DELETE FROM `gossip_menu_option` WHERE (`menu_id`='9741') AND (`id`='1');
UPDATE `gossip_menu_option` SET `id`='1' WHERE (`menu_id`='9741') AND (`id`='2');
UPDATE `gossip_menu_option` SET `id`='2' WHERE (`menu_id`='9741') AND (`id`='3');
UPDATE `gossip_menu_option` SET `id`='3' WHERE (`menu_id`='9741') AND (`id`='4');


