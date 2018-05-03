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

#include <piduino/gpiopin.h>
#include <piduino/database.h>

namespace Piduino {

// -----------------------------------------------------------------------------
//
//                       Pin::Descriptor Class
//
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
  bool
  Pin::Descriptor::insert () {
    cppdb::statement stat;
    long long pin_id;

    pin_id = findId();
    if (pin_id < 0) {
      // new pin

      if (id < 0) {

        stat = Piduino::db << "INSERT INTO gpio_pin(gpio_pin_type_id,logical_num,mcu_num,system_num) "
               "VALUES(?,?,?,?)" << type << num.logical << num.mcu << num.system;
      }
      else {

        stat = Piduino::db << "INSERT INTO gpio_pin(id,gpio_pin_type_id,logical_num,mcu_num,system_num) "
               "VALUES(?,?,?,?,?)" << id << type << num.logical << num.mcu << num.system;
      }
      stat.exec();
      id = stat.last_insert_id();
      for (auto n = name.begin(); n != name.end(); ++n) {

        insertModeName (n->first, n->second);
      }
      return true;
    }
    else {
      // already existing pin

      id = pin_id;
    }
    return false;
  }

// ---------------------------------------------------------------------------
  long long
  Pin::Descriptor::findId() const {
    cppdb::result res;

    for (auto it = name.begin(); it != name.end(); ++it) {

      // Recherche tous les gpio_pin_id correspondants au nom et au mode courant
      res = Piduino::db <<
            "SELECT gpio_pin_has_name.gpio_pin_id "
            " FROM gpio_pin_has_name "
            " INNER JOIN gpio_pin_name ON gpio_pin_has_name.gpio_pin_name_id = gpio_pin_name.id "
            " WHERE "
            "   gpio_pin_name.name=? AND "
            "   gpio_pin_has_name.gpio_pin_mode_id=?"
            << it->second << it->first;

      while (res.next()) {
        int match_count = 0;
        cppdb::result res2;
        long long gpio_pin_id;

        res >> gpio_pin_id;
        // Pour chaque gpio_pin_id, vérifier qu'il correspond aux éléments du map
        res2 = Piduino::db <<
               "SELECT gpio_pin_name.name,gpio_pin_has_name.gpio_pin_mode_id "
               "  FROM gpio_pin_has_name "
               "  INNER JOIN gpio_pin_name ON gpio_pin_has_name.gpio_pin_name_id=gpio_pin_name.id "
               "  WHERE gpio_pin_has_name.gpio_pin_id=?"
               << gpio_pin_id;
        while (res2.next()) {
          std::string n;
          Pin::Mode m;
          int i;

          res2 >> n >> i;
          m = static_cast<Pin::Mode> (i);
          if (name.count (m)) {
            if (name.at (m) == n) {
              match_count++;
            }
          }
        }
        if (match_count == name.size()) {
          return gpio_pin_id;
        }
      }
      break;
    }
    return -1;
  }

// ---------------------------------------------------------------------------
  long long
  Pin::Descriptor::findName (const std::string & n) const {
    cppdb::result res =
      Piduino::db << "SELECT id FROM gpio_pin_name WHERE name=?"
      << n << cppdb::row;
    if (!res.empty()) {
      long long i;
      res >> i;
      return i;
    }
    return -1;
  }

// ---------------------------------------------------------------------------
  bool
  Pin::Descriptor::hasModeName (Mode modeId, long long nameId) const {
    cppdb::result res =
      Piduino::db << 
      "SELECT gpio_pin_name_id "
      " FROM gpio_pin_has_name "
      " WHERE  gpio_pin_id=? AND "
      "   gpio_pin_name_id=? AND "
      "   gpio_pin_mode_id=?"
      << id << nameId << modeId << cppdb::row;
    return !res.empty();
  }

// ---------------------------------------------------------------------------
  void
  Pin::Descriptor::insertModeName (Mode m, const std::string & n) {
    cppdb::statement stat;
    long long name_id;

    name_id = findName (n);
    if (name_id < 0) {
      // new name

      stat = Piduino::db << "INSERT INTO gpio_pin_name(name) "
             "VALUES(?)" << n;
      stat.exec();
      name_id = stat.last_insert_id();
      stat.reset();
    }
    if (!hasModeName (m, name_id)) {

      stat = Piduino::db << "INSERT INTO gpio_pin_has_name(gpio_pin_id,gpio_pin_name_id,gpio_pin_mode_id) "
             "VALUES(?,?,?)" << id << name_id << m;
      stat.exec();
    }
  }

#if 0
// -----------------------------------------------------------------------------
  Pin::Descriptor::Descriptor (long long i) :
    type (Pin::TypeUnknown), id (i) {
    // Chargement depuis database
  }
#endif

}
/* ========================================================================== */