UPDATE `creature_template` SET 
    `mindmg` = '240', 
    `maxdmg` = '280', 
    `attackpower` = ROUND((`mindmg` + `maxdmg`) / 4 * 7), 
    `mindmg` = ROUND(`mindmg` - `attackpower` / 7), 
    `maxdmg` = ROUND(`maxdmg` - `attackpower` / 7) 
  WHERE (`entry` = '45450');
UPDATE `creature_template` SET `minlevel`='41', `maxlevel`='41' WHERE (`entry`='45450');
UPDATE `creature_template` SET `baseattacktime`='1970', `rangeattacktime`='2010' WHERE (`entry`='45450');
UPDATE `creature_template` SET `dynamicflags`='1' WHERE (`entry`='45450');
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`='6' WHERE (`entry`='45450') AND (`item`='61387');
UPDATE `creature_template` SET `faction_A`='44', `faction_H`='44' WHERE (`entry`='45450');