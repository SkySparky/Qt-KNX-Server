-- phpMyAdmin SQL Dump
-- version 3.4.5
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Feb 28, 2012 at 12:02 PM
-- Server version: 5.5.16
-- PHP Version: 5.3.8

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `knxandroid`
--
CREATE DATABASE `knxandroid` DEFAULT CHARACTER SET latin1 COLLATE latin1_swedish_ci;
USE `knxandroid`;

-- --------------------------------------------------------

--
-- Table structure for table `clients`
--

CREATE TABLE IF NOT EXISTS `clients` (
  `fld_id` int(11) NOT NULL AUTO_INCREMENT,
  `fld_username` text NOT NULL,
  `fld_password` text NOT NULL,
  `fld_project` text NOT NULL,
  `fld_data` mediumtext NOT NULL,
  PRIMARY KEY (`fld_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

--
-- Dumping data for table `clients`
--

INSERT INTO `clients` (`fld_id`, `fld_username`, `fld_password`, `fld_project`, `fld_data`) VALUES
(1, 'jaco', 'warwick', 'home1', '[GroupAddresses]\r\n1\\descr=Livingroom left lights\r\n1\\root=1\r\n1\\tags=livingroom\r\n1\\ga=0/0/1\r\n1\\type=dimmer\r\n2\\descr=Livingroom right lights\r\n2\\root=\r\n2\\tags=livingroom\r\n2\\ga=0/0/2\r\n2\\type=switch\r\n3\\descr=Outdoor\r\n3\\root=\r\n3\\tags=livingroom\r\n3\\ga=0/0/5\r\n3\\type=switch\r\n4\\descr=Left balcony\r\n4\\root=\r\n4\\tags=\r\n4\\ga=0/0/6\r\n4\\type=switch\r\n5\\descr=Front balcony\r\n5\\root=\r\n5\\tags=\r\n5\\ga=0/0/7\r\n5\\type=switch\r\n6\\descr=Kitchen upper light\r\n6\\root=\r\n6\\tags=kitchen\r\n6\\ga=0/0/8\r\n6\\type=switch\r\n7\\descr=Kitchen lower lights\r\n7\\root=\r\n7\\tags=kitchen\r\n7\\ga=0/0/9\r\n7\\type=switch\r\n8\\descr=Coridor\r\n8\\root=\r\n8\\tags=coridor\r\n8\\ga=0/0/10\r\n8\\type=switch\r\n9\\descr=Bathroom\r\n9\\root=\r\n9\\tags=\r\n9\\ga=0/0/11\r\n9\\type=switch\r\n10\\descr=WC\r\n10\\root=\r\n10\\tags=\r\n10\\ga=0/0/12\r\n10\\type=switch\r\n11\\descr=Bedroom\r\n11\\root=\r\n11\\tags=rooms\r\n11\\ga=0/0/13\r\n11\\type=switch\r\n12\\descr=Studio\r\n12\\root=\r\n12\\tags=rooms\r\n12\\ga=0/0/14\r\n12\\type=switch\r\n13\\descr=Studio balcony ligth\r\n13\\root=\r\n13\\tags=\r\n13\\ga=0/0/15\r\n13\\type=switch\r\n14\\descr=Guest room\r\n14\\root=\r\n14\\tags=rooms\r\n14\\ga=0/0/16\r\n14\\type=switch\r\n15\\descr=Patari\r\n15\\root=\r\n15\\tags=generic\r\n15\\ga=0/0/17\r\n15\\type=switch\r\n16\\descr=Office\r\n16\\root=1\r\n16\\tags=rooms\r\n16\\ga=0/0/18\r\n16\\type=switch\r\n17\\descr=Kitchen\r\n17\\root=1\r\n17\\tags=Home\r\n17\\ga=kitchen\r\n17\\type=tagbtn\r\n18\\descr=Livingroom\r\n18\\root=1\r\n18\\tags=Home\r\n18\\ga=livingroom\r\n18\\type=tagbtn\r\nsize=18\r\n');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
