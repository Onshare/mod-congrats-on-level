CREATE TABLE IF NOT EXISTS `mod_congrats_on_level_items` (
    `level` tinyint unsigned NOT NULL DEFAULT 0,
    `money` int unsigned NOT NULL DEFAULT 0,
    `spell` int unsigned NOT NULL DEFAULT 0,
    `learn` boolean NOT NULL DEFAULT false,
    `itemId1` int unsigned NOT NULL DEFAULT 0,
    `itemId2` int unsigned NOT NULL DEFAULT 0,
    `race` tinyint unsigned NOT NULL DEFAULT 0,
    `class` tinyint unsigned NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

DELETE FROM `mod_congrats_on_level_items`;
INSERT INTO `mod_congrats_on_level_items` (`level`, `money`, `spell`, `learn`, `itemId1`, `itemId2`, `race`, `class`) VALUES
(2, 2, 20217, 0, 21841, 21841, 0, 0),
(10, 10, 20217, 0, 21841, 21841, 0, 0),
(20, 20, 20217, 0, 0, 69301, 0, 0),
(30, 30, 20217, 0, 69003, 69004, 0, 0),
(40, 40, 20217, 0, 69005, 69006, 0, 0),
(50, 50, 20217, 0, 69007, 69008, 0, 0),
(60, 60, 20217, 0, 0, 69009, 0, 0),
(70, 70, 20217, 0, 0, 69010, 0, 0),
(80, 100, 20217, 0, 69001, 69002, 0, 0);
