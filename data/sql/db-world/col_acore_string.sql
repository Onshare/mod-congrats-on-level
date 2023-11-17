SET @ENTRY:=60000;
DELETE FROM `acore_string` WHERE `entry` BETWEEN @ENTRY+0 AND @ENTRY+1;
INSERT INTO `acore_string` (`entry`, `content_default`, `locale_koKR`, `locale_frFR`, `locale_deDE`, `locale_zhCN`, `locale_zhTW`, `locale_esES`, `locale_esMX`, `locale_ruRU`) VALUES
(@ENTRY+0, '欢迎来到魔兽世界。', '', '', '', '', '', '欢迎来到魔兽世界。', '欢迎来到魔兽世界。', '');
