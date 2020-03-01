#include "catch2/catch.hpp"
#include "Mdt/UicNumber/AlgorithmQt"
#include <QString>
#include <QLatin1String>
#include <QChar>
#include <QLatin1Char>

using Mdt::UicNumber::isDigit;

TEST_CASE("isDigit")
{
  REQUIRE( isDigit( QLatin1Char('0') ) );
}

bool validateUicNumberString(const char * uic)
{
  return Mdt::UicNumber::validateUicNumberString( QLatin1String(uic) );
}

TEST_CASE("validateUicNumberString")
{
  REQUIRE( !validateUicNumberString("") );
  REQUIRE( !validateUicNumberString("A") );
  REQUIRE( !validateUicNumberString("5") );
  REQUIRE( validateUicNumberString("94 85 7 560 253-7") );
}
