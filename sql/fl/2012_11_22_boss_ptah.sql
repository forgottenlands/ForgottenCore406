-- mob summoanto: 75339
UPDATE `creature_template` SET `modelid2`=11686, `modelid1`=11686, `minlevel`=85, `maxlevel`=85, `faction_A`=14, `faction_H`=14, `speed_walk`=0, `speed_run`=0, `mindmg`=0, `maxdmg`=0, 
`attackpower`=0, `dmg_multiplier`=1, `baseattacktime`=100000, `unit_flags`=33554432, `minrangedmg`=0, `maxrangedmg`=0, `flags_extra`=2, `ScriptName`='npc_earth_spike' WHERE  `entry`=44765;

UPDATE `creature_template` SET `faction_A`=14, `faction_H`=14, `speed_walk`=0, `speed_run`=0, `flags_extra`=2 WHERE  `entry`=40503 LIMIT 1;