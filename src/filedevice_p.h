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

#ifndef PIDUINO_FILEDEVICE_PRIVATE_H
#define PIDUINO_FILEDEVICE_PRIVATE_H

#include <string>
#include <ext/stdio_filebuf.h>
#include <mutex>
#include <piduino/filedevice.h>
#include "iodevice_p.h"

namespace Piduino {

  /**
   * @class FileDevice::Private
   * @brief
   */
  class FileDevice::Private  : public IoDevice::Private {

    public:
      Private (FileDevice * q);
      virtual ~Private();

      virtual bool open (OpenMode mode, int additionalPosixFlags = 0);
      virtual void close();

      virtual int ioctl (int req);
      virtual int ioctl (int req, void *);
      
      virtual int poll (bool *selectForRead, bool *selectForWrite,
                        bool checkRead, bool checkWrite,
                        int msecs);

      inline void lock() {
        mutex.lock();
      }

      inline void unlock() {
        mutex.unlock();
      }

      int fd;
      __gnu_cxx::stdio_filebuf<char> iosbuf;
      std::iostream stream;
      std::string path;
      std::mutex mutex;

      PIMP_DECLARE_PUBLIC (FileDevice)
  };
}

/* ========================================================================== */
#endif /* PIDUINO_FILEDEVICE_PRIVATE_H defined */
