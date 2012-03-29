-- NPC tyrande Whisperwind
UPDATE `creature_template` SET `minlevel`='88', `maxlevel`='88' WHERE (`entry`='7999');
UPDATE `creature_template` SET `mindmg`='1225.5', `maxdmg`='1544.7', `attackpower`='1651' WHERE (`entry`='7999');
UPDATE `creature_template` SET `baseattacktime`='2000' WHERE (`entry`='7999');
UPDATE `creature_template` SET `minrangedmg`='1160.9', `maxrangedmg`='1328.1', `rangedattackpower`='225', `type_flags`='76' WHERE (`entry`='7999');
UPDATE `creature_template` SET `unit_class`='1', `unit_flags`='32768', `dynamicflags`='2048' WHERE (`entry`='7999');
UPDATE `creature_template` SET `mingold`='700000', `maxgold`='750000', `InhabitType`='3', `RacialLeader`='1' WHERE (`entry`='7999');
UPDATE `creature_template` SET `ScriptName`='npc_tyrande_whisperwind' WHERE (`entry`='7999');