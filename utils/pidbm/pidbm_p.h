/* Copyright © 2020 Pascal JEAN, All rights reserved.
 *
 * Piduino pidbm is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Piduino pidbm is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Piduino pidbm.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include <cppdb/frontend.h>
#include "pidbm.h"


class Pidbm::Private {

  public:
    Private (Pidbm * q);
    Private (Pidbm * q, int argc, char **argv);
    virtual ~Private();

    Pidbm * const q_ptr;

    Popl::OptionParser op;
    bool opHelp;
    bool opWarranty;
    bool opVersion;

    std::string cinfo;
    mutable cppdb::session db;

    static const std::string Authors;
    static const std::string Website;
    PIMP_DECLARE_PUBLIC (Pidbm)
};

/* ========================================================================== */
