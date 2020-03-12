#include "catch2/catch.hpp"
#include "Mdt/UicNumber/AlgorithmQt"
#include <QString>
#include <QLatin1String>
#include <QChar>
#include <QLatin1Char>

using Mdt::UicNumber::toIntQt;
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

TEST_CASE("toIntQt")
{
  SECTION("00")
  {
    REQUIRE( toIntQt(QLatin1String("00"), 0, 2) == 0 );
  }

  SECTION("85")
  {
    REQUIRE( toIntQt(QLatin1String("85"), 0, 2) == 85 );
  }

  SECTION("7560253")
  {
    REQUIRE( toIntQt(QLatin1String("7560253"), 0, 7) == 7560253 );
  }

  SECTION("94857560253 94")
  {
    REQUIRE( toIntQt(QLatin1String("94857560253"), 0, 2) == 94 );
  }

  SECTION("94857560253 85")
  {
    REQUIRE( toIntQt(QLatin1String("94857560253"), 2, 2) == 85 );
  }

  SECTION("94857560253 7560253")
  {
    REQUIRE( toIntQt(QLatin1String("94857560253"), 4, 7) == 7560253 );
  }

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

