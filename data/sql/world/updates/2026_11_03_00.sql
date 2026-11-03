CREATE TABLE IF NOT EXISTS `playerbots_race_template` (
  `race` tinyint unsigned NOT NULL,
  `name_race` tinyint unsigned DEFAULT NULL COMMENT 'Race whose bot names this race uses, 0 for generic names. NULL: its kin_race in player_race_template',
  `mounts` varchar(255) NOT NULL DEFAULT '' COMMENT 'Mount spells, space separated. Sorted by speed; spells the DBCs lack are skipped, and a speed with none uses the home race''s mounts',
  PRIMARY KEY (`race`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='Bot-only settings of custom races. Races only need a row to differ from their home and kin';
