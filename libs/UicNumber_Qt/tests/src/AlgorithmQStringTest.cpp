#include "catch2/catch.hpp"
#include "Mdt/UicNumber/AlgorithmQt"
#include <QString>
#include <QLatin1String>
#include <QChar>
#include <QLatin1Char>

// using Mdt::UicNumber::isDigit;
// using Mdt::UicNumber::isAllowedCharQt;

using Mdt::UicNumber::toCharQt;
using Mdt::UicNumber::removeSpacesAndHypthens;

bool validateUicNumberString(const char * uic)
{
  return Mdt::UicNumber::validateUicNumberString( QLatin1String(uic) );
}

bool validateStringContent(const char * uic)
{
  return Mdt::UicNumber::validateStringContent( QString::fromLatin1(uic) );
}

TEST_CASE("toCharQt")
{
  REQUIRE( toCharQt(QLatin1Char('0')) == '0' );
  REQUIRE( toCharQt(QLatin1Char('9')) == '9' );
  REQUIRE( toCharQt(QLatin1Char('A')) == 'A' );
}

// TEST_CASE("isDigitQt")
// {
//   REQUIRE( isDigit( QLatin1Char('0') ) );
//   REQUIRE( isDigit( QLatin1Char('5') ) );
//   REQUIRE( isDigit( QLatin1Char('9') ) );
//   REQUIRE( !isDigit( QLatin1Char('a') ) );
//   REQUIRE( !isDigit( QLatin1Char('A') ) );
//   REQUIRE( !isDigit( QLatin1Char(' ') ) );
// }

// TEST_CASE("isAllowedCharQt")
// {
//   REQUIRE( isAllowedCharQt( QLatin1Char('1') ) );
//   REQUIRE( isAllowedCharQt( QLatin1Char('9') ) );
//   REQUIRE( isAllowedCharQt( QLatin1Char(' ') ) );
//   REQUIRE( isAllowedCharQt( QLatin1Char('-') ) );
//   REQUIRE( !isAllowedCharQt( QLatin1Char('A') ) );
// }

TEST_CASE("validateStringContent")
{
  REQUIRE( validateStringContent("01 23 4567 890-1") );
  REQUIRE( !validateStringContent("AB 23 4567 890-1") );
}

TEST_CASE("removeSpacesAndHypthens")
{
  SECTION("empty")
  {
    QString uic;
    removeSpacesAndHypthens(uic);
    REQUIRE( uic.isEmpty() );
  }

  SECTION(" 01 23 4567 890-1 ")
  {
    QString uic = QLatin1String(" 01 23 4567 890-1 ");
    removeSpacesAndHypthens(uic);
    REQUIRE( uic == QLatin1String("012345678901") );
  }
}

TEST_CASE("validateUicNumberString")
{
  REQUIRE( !validateUicNumberString("") );
  REQUIRE( !validateUicNumberString("A") );
  REQUIRE( !validateUicNumberString("5") );
  REQUIRE( validateUicNumberString("94 85 7 560 253-7") );
}
