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
#ifndef PIDUINO_TERMIONOTIFIER_H
#define PIDUINO_TERMIONOTIFIER_H

#include <string>
#include <piduino/global.h>

/**
 *  @defgroup piduino_terminalnotifier Read Notifier
 *  @{
 */

namespace Piduino {

  /**
   * @class TerminalNotifier
   * @brief
   */
  class TerminalNotifier {
    public:
      TerminalNotifier ();
      virtual ~TerminalNotifier();

      bool start (int fd);
      void terminate();
      bool isRunning() const;

      size_t available() const;

      size_t read (char * buf, size_t len, long msTimeout = 0);
      size_t read (std::string & str, long msTimeout = 0);
      bool read (char & c, long msTimeout = 0);

      size_t peek (char * buf, size_t len, long msTimeout = 0);
      size_t peek (std::string & str, long msTimeout = 0);
      bool peek (char & c, long msTimeout = 0);

    protected:
      class Private;
      TerminalNotifier (Private &dd);
      std::shared_ptr<Private> d_ptr;

    private:
      PIMP_DECLARE_PRIVATE (TerminalNotifier)
  };

}
/**
 *  @}
 */

/* ========================================================================== */
#endif /* PIDUINO_TERMIONOTIFIER_H defined */
