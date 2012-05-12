-- Aquaticform speed fix
INSERT INTO `character_spell` (SELECT guid,5421,1,0 FROM `characters` WHERE CLASS = 11);

-- Spd buff for aquaticform
INSERT INTO playercreateinfo_spell VALUES(0,11,5421,"Aquatic Form Speed Buff");

-- item cond fix
REPLACE INTO conditions(sourcetypeorreferenceid,sourceentry,conditiontypeorreference,conditionvalue1,conditionvalue2) VALUES (18,56798,24,1,41360); -- item cant be used on players