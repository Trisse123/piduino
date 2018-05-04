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
#ifndef _PIDUINO_DATABASE_H_
#define _PIDUINO_DATABASE_H_

#include <string>
#include <memory>
#include <iostream>
#include <cppdb/frontend.h>
#include <piduino/soc.h>

/**
 *  @defgroup piduino_database Database
 *
 *  Les informations concernant la carte cible sont stockées dans une base de
 *  données.
 *  @{
 */

namespace Piduino {

  class Database : public cppdb::session {

    public:
      class Board {
        public:

          // -------------------------------------------------------------------
          //
          //                      Database::Board::Family Class
          //
          // -------------------------------------------------------------------
          class Family {
            public:

              enum Id {
                RaspberryPi = 0,
                NanoPi,
                OrangePi,
                BananaPi,
                // Add New item here and update board_family table in database !

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

          // -------------------------------------------------------------------
          //
          //                     Database::Board::Model Class
          //
          // -------------------------------------------------------------------
          class Model {
            public:

              enum Id {
                RaspberryPiA = 0,
                RaspberryPiB,
                RaspberryPiAPlus,
                RaspberryPiBPlus,
                RaspberryPiComputeModule,
                RaspberryPi2,
                RaspberryPiZero,
                RaspberryPi3,
                RaspberryPiZeroW,
                RaspberryPiComputeModule3,
                NanoPiNeo,
                NanoPiNeoAir,
                NanoPiM1,
                NanoPiM1Plus,
                NanoPiNeo2,
                NanoPiNeoPlus2,

                // Add New item here and update board_model table in database !

                //---
                Unknown = -1
              };

              Model (Id i = Unknown) {
                setId (i);
              }
              virtual ~Model() {}

              inline Id id() const {
                return _id;
              }

              inline const std::string & name() const {
                return _name;
              }

              inline const Family & family() const {
                return _family;
              }

              inline const SoC & soc() const {
                return _soc;
              }

              void setId (Id i);

            private:
              Id _id;
              std::string _name;
              Family _family;
              SoC _soc;
          };

          // -------------------------------------------------------------------
          //
          //                      Database::Board Class
          //
          // -------------------------------------------------------------------

          Board (int cpuinfoBoardRevision = -1);
          Board (const std::string & armbianBoardTag);
          virtual ~Board();

          bool probingSystem();
          bool setRevision (int rev);
          bool setTag (const std::string & armbianBoardTag);

          inline long long id() const {
            return _id;
          }

          inline const std::string & name() const {
            return model().name();
          }

          inline const std::string & tag() const {
            return _tag;
          }

          inline int revision() const {
            return _revision;
          }

          inline const Family & family() const {
            return model().family();
          }

          inline const SoC & soc() const {
            return model().soc();
          }

          inline float pcbRevision() const {
            return _pcb_revision;
          }

          inline long long gpioId() const {
            return _gpio_id;
          }

          inline const Model & model() const {
            return _model;
          }

          inline const Manufacturer & manufacturer() const {
            return _manufacturer;
          }

          inline unsigned long totalRam() const {
            return _ram;
          }

          inline bool found() const {
            return _found;
          }

          friend std::ostream& operator<< (std::ostream& os, const Board& c);

        private:
          long long _id;
          Model _model;
          Manufacturer _manufacturer;
          long long _gpio_id; // Révision du GPIO
          float _pcb_revision;
          int _revision;
          bool _found;
          std::string _tag;
          long _ram; // RAM en Mo
      };

      // -----------------------------------------------------------------------
      //
      //                      Database Class
      //
      // -----------------------------------------------------------------------
      Database (const std::string & connectionInfo = std::string());
      Database (int cpuinfoBoardRevision, const std::string & connectionInfo = std::string());
      Database (const std::string & armbianBoardTag, const std::string & connectionInfo = std::string());
      virtual ~Database();

      static std::string findConnectionInfo (const std::string & connectionInfo = std::string());

      void setConnectionInfo (const std::string & connectionInfo);

      inline const std::string& connectionInfo() const {
        return _cinfo;
      }

      inline const Board & board() const {
        return *_board;
      }

    private:
      std::shared_ptr<Board> _board;
      std::string _cinfo;
  };

  // ---------------------------------------------------------------------------
  //
  //                      Piduino Database Global Object
  //
  // ---------------------------------------------------------------------------
  extern Database db; ///< Piduino Database Global Object
  /**
   * @}
   */
}
/**
 *  @}
 */

/* ========================================================================== */
#endif /*_PIDUINO_DATABASE_H_ defined */
