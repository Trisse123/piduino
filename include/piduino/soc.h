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

#ifndef _PIDUINO_SOC_H_
#define _PIDUINO_SOC_H_

#include <string>
#include <piduino/manufacturer.h>

/**
 *  @defgroup piduino_soc SoC
 *
 *  Ce module fournit informations concernant les microcontrôleurs.
 *  @{
 */

namespace Piduino {

  class SoC {
    public:

      // -----------------------------------------------------------------------
      //
      //                            SoC::Family Class
      //
      // -----------------------------------------------------------------------
      class Family {
        public:

          enum Id {
            BroadcomBcm2835 = 0,
            AllwinnerH,
            // Add New item here and update soc_family table in database,
            // then add device driver source in src/arch !

            //---
            Unknown = -1
          };

          Family (Id i = Unknown) {
            setId (i);
          }
          virtual ~Family() {}

          inline Id id() const {
            return _id;
          }

          inline const std::string &name() const {
            return _name;
          }

          void setId (Id i);

        private:
          Id _id;
          std::string _name;
      };

      // -----------------------------------------------------------------------
      //
      //                              SoC Class
      //
      // -----------------------------------------------------------------------
      enum Id {

        Bcm2708 = 0,
        Bcm2709,
        Bcm2710,
        H3,
        H5,
        // Add New item here and update soc table in database !

        //---
        Unknown = -1
      };

      SoC (Id i = Unknown) {
        setId (i);
      }
      virtual ~SoC() {}

      inline Id id() const {
        return _id;
      }

      inline const std::string & name() const {
        return _name;
      }

      inline const Family & family() const {
        return _family;
      }

      inline const Manufacturer & manufacturer() const {
        return _manufacturer;
      }

      void setId (Id i);

    private:
      Id _id;
      std::string _name;
      Family _family;
      Manufacturer _manufacturer;
  };
}
/**
 *  @}
 */

/* ========================================================================== */
#endif /*_PIDUINO_SOC_H_ defined */
