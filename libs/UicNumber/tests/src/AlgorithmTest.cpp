#include "catch2/catch.hpp"
#include "Mdt/UicNumber/Algorithm"
#include <string>

using Mdt::UicNumber::isDigit;
using Mdt::UicNumber::isSpace;
using Mdt::UicNumber::isAllowedChar;

bool validateStringContent(const std::string & uic)
{
  return Mdt::UicNumber::validateStringContent(uic);
}

void removeSpacesAndDashes(std::string & uic)
{
  Mdt::UicNumber::removeSpacesAndDashes(uic);
}


TEST_CASE("isSpace")
{
  REQUIRE( isSpace(' ') );
  REQUIRE( !isSpace('0') );
  REQUIRE( !isSpace('a') );
}

TEST_CASE("isDigit")
{
  REQUIRE( isDigit('0') );
  REQUIRE( isDigit('1') );
  REQUIRE( isDigit('2') );
  REQUIRE( isDigit('3') );
  REQUIRE( isDigit('4') );
  REQUIRE( isDigit('5') );
  REQUIRE( isDigit('6') );
  REQUIRE( isDigit('7') );
  REQUIRE( isDigit('8') );
  REQUIRE( isDigit('9') );
  REQUIRE( !isDigit('a') );
  REQUIRE( !isDigit('A') );
  REQUIRE( !isDigit(' ') );
}

TEST_CASE("isAllowedChar")
{
  REQUIRE( isAllowedChar('1') );
  REQUIRE( isAllowedChar(' ') );
  REQUIRE( isAllowedChar('-') );
  REQUIRE( !isAllowedChar('A') );
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
    std::string uic;
    removeSpacesAndDashes(uic);
    REQUIRE( uic.empty() );
  }

  SECTION("space")
  {
    std::string uic = " ";
    removeSpacesAndDashes(uic);
    REQUIRE( uic == "" );
  }

  SECTION("dash")
  {
    std::string uic = "-";
    removeSpacesAndDashes(uic);
    REQUIRE( uic == "" );
  }

  SECTION("1")
  {
    std::string uic = "1";
    removeSpacesAndDashes(uic);
    REQUIRE( uic == "1" );
  }

  SECTION("12")
  {
    std::string uic = "12";
    removeSpacesAndDashes(uic);
    REQUIRE( uic == "12" );
  }

  SECTION("1-2")
  {
    std::string uic = "1-2";
    removeSpacesAndDashes(uic);
    REQUIRE( uic == "12" );
  }

  SECTION(" 01 23 4567 890-1 ")
  {
    std::string uic = " 01 23 4567 890-1 ";
    removeSpacesAndDashes(uic);
    REQUIRE( uic == "012345678901" );
  }
}
