#include "catch2/catch.hpp"
#include "Mdt/UicNumber/AlgorithmQt"
#include <QString>
#include <QLatin1String>
#include <QChar>
#include <QLatin1Char>

using Mdt::UicNumber::toCharQt;
using Mdt::UicNumber::removeSpacesAndDashes;

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

TEST_CASE("validateStringContent")
{
  REQUIRE( validateStringContent("01 23 4567 890-1") );
  REQUIRE( !validateStringContent("AB 23 4567 890-1") );
}

TEST_CASE("removeSpacesAndDashes")
{
  SECTION("empty")
  {
    QString uic;
    removeSpacesAndDashes(uic);
    REQUIRE( uic.isEmpty() );
  }

  SECTION(" 01 23 4567 890-1 ")
  {
    QString uic = QLatin1String(" 01 23 4567 890-1 ");
    removeSpacesAndDashes(uic);
    REQUIRE( uic == QLatin1String("012345678901") );
  }
}

