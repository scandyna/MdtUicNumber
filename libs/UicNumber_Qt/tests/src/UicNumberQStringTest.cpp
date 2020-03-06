/****************************************************************************
 **
 ** MdtUicNumber - A C++ library to work with UIC numbers
 **
 ** Copyright (C) 2020-2020 Philippe Steinmann.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU Lesser General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU Lesser General Public License for more details.
 **
 ** You should have received a copy of the GNU Lesser General Public License
 ** along with this program.  If not, see <https://www.gnu.org/licenses/>.
 **
 ****************************************************************************/
#include "catch2/catch.hpp"
#include "Mdt/UicNumber/UicNumberQt.h"
#include <QString>
#include <QLatin1String>

bool validateUicNumberStringFormat(const char * uic)
{
  return Mdt::UicNumber::validateUicNumberStringFormat( QLatin1String(uic) );
}


TEST_CASE("validateUicNumberStringFormat")
{
  REQUIRE( !validateUicNumberStringFormat("") );
  REQUIRE( !validateUicNumberStringFormat("A") );
  REQUIRE( !validateUicNumberStringFormat("5") );
  REQUIRE( validateUicNumberStringFormat("94 85 7 560 253-7") );
}

TEST_CASE("UicNumberfromQString")
{
  SECTION("94 85 7 560 253")
  {
    const auto uicNumber = Mdt::UicNumber::fromQString( QLatin1String("94 85 7 560 253") );
//     REQUIRE( uicNumber.isValid() );
  }
}
