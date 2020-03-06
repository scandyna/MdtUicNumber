#include "catch2/catch.hpp"
#include "Mdt/UicNumber/UicNumber"

bool validateUicNumberStringFormat(const std::string & uic)
{
  return Mdt::UicNumber::validateUicNumberStringFormat(uic);
}


TEST_CASE("validateUicNumberStringFormat")
{
  SECTION("empty")
  {
    REQUIRE( !validateUicNumberStringFormat("") );
  }

  SECTION("A")
  {
    REQUIRE( !validateUicNumberStringFormat("A") );
  }

  SECTION("5")
  {
    REQUIRE( !validateUicNumberStringFormat("5") );
  }

  SECTION("94 85 7 56")
  {
    REQUIRE( !validateUicNumberStringFormat("94 85 7 56") );
  }

  SECTION("560 253")
  {
    REQUIRE( !validateUicNumberStringFormat("560 253") );
  }

  SECTION("560 253-7")
  {
    REQUIRE( !validateUicNumberStringFormat("560 253-7") );
  }

  SECTION("94 85 7 560 253")
  {
    REQUIRE( validateUicNumberStringFormat("94 85 7 560 253") );
  }

  SECTION("94 85 7 560 253-7")
  {
    REQUIRE( validateUicNumberStringFormat("94 85 7 560 253-7") );
  }

  SECTION("94 85 7 560 253-2")
  {
    REQUIRE( validateUicNumberStringFormat("94 85 7 560 253-2") );
  }

  SECTION("0 94 85 7 560 253-7")
  {
    REQUIRE( !validateUicNumberStringFormat("0 94 85 7 560 253-7") );
  }

  SECTION("00 00 00 00 000")
  {
    REQUIRE( validateUicNumberStringFormat("00 00 00 00 000") );
  }

  SECTION("00 00 00 00 000-0")
  {
    REQUIRE( validateUicNumberStringFormat("00 00 00 00 000-0") );
  }

  SECTION("0a 0c 00 00 000-0")
  {
    REQUIRE( !validateUicNumberStringFormat("0a 0c 00 00 000-0") );
  }

}

TEST_CASE("UicNumberfromString")
{
  SECTION("94 85 7 560 253")
  {
    const auto uicNumber = Mdt::UicNumber::fromString("94 85 7 560 253");
//     REQUIRE( uicNumber.isValid() );
  }
}
