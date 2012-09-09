delimiter $$

CREATE TABLE `quest_completer` (
  `Entry` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `Enabled` mediumint(1) unsigned DEFAULT '1',
  `Commenti` text,
  PRIMARY KEY (`Entry`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1$$;


delimiter $$

CREATE TABLE `quest_completer_logs` (
  `guidPlayer` int(11) unsigned NOT NULL,
  `entryQuest` int(11) unsigned NOT NULL,
  `time` datetime DEFAULT NULL,
  PRIMARY KEY (`guidPlayer`,`entryQuest`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1$$

