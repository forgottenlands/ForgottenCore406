-- npc tyrande wispherwind PART 2
UPDATE `creature_template` SET `unit_class`='8' WHERE (`entry`='7999');
UPDATE `creature_template` SET `ScriptName`='' WHERE (`entry`='7999');
UPDATE `creature_template` SET `Health_mod`='800' WHERE (`entry`='7999');
UPDATE `creature_template` SET `unit_flags`='64', `dynamicflags`='8' WHERE (`entry`='7999');
UPDATE `creature_template` SET `minlevel`='73', `maxlevel`='73', `exp`='1' WHERE (`entry`='7999');
UPDATE `creature_template` SET `faction_A`='69', `faction_H`='69' WHERE (`entry`='7999');
UPDATE `creature_template` SET `speed_walk`='1.2', `unit_class`='2' WHERE (`entry`='7999');
UPDATE `creature_template` SET `type_flags`='12' WHERE (`entry`='7999');
UPDATE `creature_template` SET `RacialLeader`='0' WHERE (`entry`='7999');
UPDATE `creature_template` SET `WDBVerified`='12340' WHERE (`entry`='7999');