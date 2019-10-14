-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema cansat
-- -----------------------------------------------------
DROP SCHEMA IF EXISTS `cansat` ;

-- -----------------------------------------------------
-- Schema cansat
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `cansat` DEFAULT CHARACTER SET utf8 ;
USE `cansat` ;

-- -----------------------------------------------------
-- Table `cansat`.`data`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `cansat`.`data` ;

CREATE TABLE IF NOT EXISTS `cansat`.`data` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `time` DATETIME(2) NOT NULL,
  `elevation` DOUBLE NOT NULL,
  `latitud` DECIMAL(6) NOT NULL,
  `longitud` DECIMAL(6) NOT NULL,
  `acc_x` DOUBLE NOT NULL,
  `acc_y` DOUBLE NOT NULL,
  `acc_z` DOUBLE NOT NULL,
  `gyro_x` DOUBLE NOT NULL,
  `gyro_y` DOUBLE NOT NULL,
  `gyro_z` DOUBLE NOT NULL,
  `pressure` DECIMAL(4) NOT NULL,
  `temp` DECIMAL(4) NOT NULL,
  `altimeter` DOUBLE NOT NULL,
  `ppm_co2` INT NOT NULL,
  PRIMARY KEY (`id`))
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
