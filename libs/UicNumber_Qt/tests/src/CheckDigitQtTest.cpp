#include "catch2/catch.hpp"
#include "Mdt/UicNumber/CheckDigitAlgorithmQt.h"
#include <QString>
#include <QLatin1String>

using Mdt::UicNumber::computeCheckDigitFromQString;

TEST_CASE("computeCheckDigitFromQString")
{
  SECTION("94 85 7 560 253-7")
  {
    REQUIRE( computeCheckDigitFromQString( QLatin1String("94 85 7 560 253") ) == 7 );
  }
}
