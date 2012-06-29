ALTER TABLE `character_cp_weekcap`
	CHANGE COLUMN `source` `source` SMALLINT(3) UNSIGNED NOT NULL DEFAULT '0' AFTER `guid`;