-- Quest Words of power
UPDATE `creature_template` SET `unit_flags`='0' WHERE (`entry`='26073'); -- 33555200
UPDATE `creature_template` SET `unit_flags`='0' WHERE (`entry`='26076');

-- Quest The prototype console
INSERT INTO `gameobject_involvedrelation` (`id`, `quest`) VALUES ('191761', '12889');

-- caverna eastern plaguelands
DELETE FROM `creature` WHERE (`guid`='54412');

--Quest the abyssal ride
UPDATE `quest_template` SET `Method`='0' WHERE (`entry`='25371');