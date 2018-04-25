/* Copyright © 2018 Pascal JEAN, All rights reserved.
 * This file is part of the Piduino Library.
 *
 * The Piduino Library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * The Piduino Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with the Piduino Library; if not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PIDUINO_ARDUINO_H_
#define _PIDUINO_ARDUINO_H_

#include <piduino/gpio.h>
#include <piduino/clock.h>
#ifndef __DOXYGEN__
enum ArduinoPinMode {
  INPUT = Piduino::Pin::ModeInput,
  OUTPUT = Piduino::Pin::ModeOutput,
  INPUT_PULLUP,
  INPUT_PULLDOWN // Not supported by Arduino !
};
enum ArduinoIntEdge {
  // LOW & HIGH unsupported !
  CHANGE = Piduino::Pin::EdgeBoth,
  RISING = Piduino::Pin::EdgeRising,
  FALLING = Piduino::Pin::EdgeFalling
};
typedef Piduino::Pin::Isr Isr;
#define digitalPinToInterrupt(p) (p)
#else

/**
 *  @defgroup piduino_arduino Arduino
 *
 *  Ce module permet de programmer avec Piduino en utilisant une syntaxe proche d'Arduino.
 */

/**
 *  @addtogroup piduino_arduino
 *  @{
 */

/**
 * @enum ArduinoPinMode
 * @brief Mode d'utilisation d'une broche digitale
 */
enum ArduinoPinMode {
  INPUT,  ///< entrée sans résistance de tirage
  OUTPUT, ///< sortie
  INPUT_PULLUP,  ///< entrée avec résistance de tirage à l'état haut
  INPUT_PULLDOWN ///< entrée avec résistance de tirage à l'état bas, mode supplémentaire non disponible dans Arduino
};

/**
 * @enum ArduinoIntEdge
 * @brief Type de front déclenchant une interrption
 *
 * @warning le déclenchement sur niveau logique bas et haut (LOW/HIGH)
 * ne sont pas pris en charge
 */
enum ArduinoIntEdge {
  // LOW & HIGH unsupported !
  CHANGE, ///< front montant et descendant
  RISING, ///< front montant
  FALLING ///< front descendant
};

/**
 * @brief Transforme un numéro de broche en numéro d'interruption
 *
 * Cette macro est présente uniquement pour la compatibilté Arduino car elle
 * ne fait que recopier le numéro de broche.
 */
#define digitalPinToInterrupt(p)

/**
 * @brief Routine d'interruption
 *
 * Une routine d'interruption ne prend et ne renvoie aucun paramètre.
 */
typedef void (* Isr) (void);

#endif /* __DOXYGEN__ */

/**
 * @enum ArduinoBool
 * @brief Valeur binaire
 */
enum ArduinoBool {
  HIGH = true,  ///< état haut
  LOW = false   ///< état bas
};

// Digital pins ----------------------------------------------------------------
/**
 * @brief Modification du mode d'une broche digitale
 *
 *  https://www.arduino.cc/en/Tutorial/DigitalPins
 */
void pinMode (int pin, ArduinoPinMode mode);

/**
 * @brief Modification d'une broche digitale
 *
 *  https://www.arduino.cc/en/Tutorial/DigitalPins
 */
void digitalWrite (int pin, int value);

/**
 * @brief Lecture d'une broche digitale
 *
 *  https://www.arduino.cc/en/Tutorial/DigitalPins
 */
int digitalRead (int pin);

/**
 * @brief Basculement de l'état  d'une broche digitale
 *
 *  @warning Non disponible dans Arduino !
 */
void digitalToggle (int pin); // Not supported by Arduino !

// Interrupts ------------------------------------------------------------------
/**
 * @brief Installe une routine d'interruption (Isr)
 * 
 * https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
 */
void attachInterrupt (int pin, Isr isr, ArduinoIntEdge mode);

/**
 * @brief Désinstalle une routine d'interruption (Isr)
 * 
 * https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
 */
void detachInterrupt (int pin);

// Time ------------------------------------------------------------------------
/**
 * @brief Pause pour une durée en millisecondes
 * @param ms durée de la pause en ms, -1 pour endormir le thread
 */
void delay (unsigned long ms);

/**
 * @brief Pause pour une durée en microsecondes
 * @param ms durée de la pause en us, -1 pour endormir le thread
 */
void delayMicroseconds (unsigned long us);

/**
 * @brief Nombre de millisecondes depuis le lancement du programme
 */
unsigned long millis();

/**
 * @brief Nombre de microsecondes depuis le lancement du programme
 */
unsigned long micros();

/**
* @}
*/

/* ========================================================================== */
#endif /*_PIDUINO_ARDUINO_H_ defined */
