-- FIX NORTHREND LACKS OF MINERAL

-- Fix Mineral Spawn in Sholazar
UPDATE `pool_gameobject` SET `chance`=0 WHERE (`pool_entry` BETWEEN 10800 AND 10911);
UPDATE `pool_template` SET `max_limit`=2 WHERE (`entry` BETWEEN 10800 AND 10911);

-- Fix Mineral Spawn in IceCrown
UPDATE `pool_gameobject` SET `chance`=0 WHERE (`pool_entry` BETWEEN 11400 AND 11634);
UPDATE `pool_template` SET `max_limit`=2 WHERE (`entry` BETWEEN 11400 AND 11634);

-- Fix Mineral Spawn in Borean Tundra
UPDATE `pool_gameobject` SET `chance`=0 WHERE (`pool_entry` BETWEEN 10000 AND 10090);
UPDATE `pool_template` SET `max_limit`=2 WHERE (`entry` BETWEEN 10000 AND 10090);

-- Fix Mineral Spawn in ZulDrak
UPDATE `pool_gameobject` SET `chance`=0 WHERE (`pool_entry` BETWEEN 10650 AND 10742);
UPDATE `pool_template` SET `max_limit`=2 WHERE (`entry` BETWEEN 10650 AND 10742);

-- Fix Mineral Spawn in Grizzly Hills
UPDATE `pool_gameobject` SET `chance`=0 WHERE (`pool_entry` BETWEEN 10300 AND 10360);
UPDATE `pool_template` SET `max_limit`=2 WHERE (`entry` BETWEEN 10300 AND 10360);

-- Fix Mineral Spawn in Storm Peaks
UPDATE `pool_gameobject` SET `chance`=0 WHERE (`pool_entry` BETWEEN 11150 AND 11259);
UPDATE `pool_template` SET `max_limit`=2 WHERE (`entry` BETWEEN 11150 AND 11259);

-- Fix Mineral Spawn in Wintergrasp
UPDATE `pool_gameobject` SET `chance`=0 WHERE (`pool_entry` BETWEEN 5617 AND 5661);
UPDATE `pool_template` SET `max_limit`=2 WHERE (`entry` BETWEEN 5617 AND 5661);

-- Fix Mineral Spawn in Howling Fjord
UPDATE `pool_gameobject` SET `chance`=0 WHERE (`pool_entry` BETWEEN 10165 AND 10249);
UPDATE `pool_template` SET `max_limit`=2 WHERE (`entry` BETWEEN 10165 AND 10249);