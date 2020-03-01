#include "catch2/catch.hpp"
#include "Mdt/UicNumber/Algorithm"
#include <string>

using Mdt::UicNumber::isDigit;

TEST_CASE("isDigit")
{
  REQUIRE( isDigit('0') );
}

bool validateUicNumberString(const std::string & uic)
{
  return Mdt::UicNumber::validateUicNumberString(uic);
}

TEST_CASE("validateUicNumberString")
{
  REQUIRE( !validateUicNumberString("") );
  REQUIRE( !validateUicNumberString("A") );
  REQUIRE( !validateUicNumberString("5") );
  REQUIRE( validateUicNumberString("94 85 7 560 253-7") );
}
