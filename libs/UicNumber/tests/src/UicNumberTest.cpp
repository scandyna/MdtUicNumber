#include "catch2/catch.hpp"
#include "Mdt/UicNumber/UicNumber"

#include <iostream>

using Mdt::UicNumber::TypeCode;
using Mdt::UicNumber::CountryCode;
using Mdt::UicNumber::UicNumber11DigitArray;
using Mdt::UicNumber::UicNumber12CharDigitArray;
using Mdt::UicNumber::toString;


TEST_CASE("UicNumberfromString")
{
  SECTION("94 85 7 560 253")
  {
    const auto uicNumber = Mdt::UicNumber::fromString("94 85 7 560 253");
    REQUIRE( uicNumber.typeCode() == TypeCode::ElectricMultipleUnit );
    REQUIRE( uicNumber.countryCode() == CountryCode::Switzerland );
    REQUIRE( uicNumber.variableBlock() == 7560253 );
    REQUIRE( uicNumber.checkDigit() == 7 );
  }

  SECTION("00 00 0 000 000")
  {
    const auto uicNumber = Mdt::UicNumber::fromString("00 00 0 000 000");
    REQUIRE( uicNumber.typeCode() == TypeCode::Unknown );
    REQUIRE( uicNumber.countryCode() == CountryCode::Unknown );
    REQUIRE( uicNumber.variableBlock() == 0 );
  }
}

TEST_CASE("to11DigitArray")
{
  const auto uicNumber = Mdt::UicNumber::fromString("94 85 7 560 253");
  REQUIRE( uicNumber.to11DigitArray() == UicNumber11DigitArray{9,4,8,5,7,5,6,0,2,5,3} );
}

TEST_CASE("to12CharDigitArray")
{
  const auto uicNumber = Mdt::UicNumber::fromString("94 85 7 560 253");
  REQUIRE( uicNumber.to12CharDigitArray() == UicNumber12CharDigitArray{'9','4','8','5','7','5','6','0','2','5','3','7'} );
}

TEST_CASE("toString")
{
  SECTION("94 85 7 560 253-7")
  {
    const auto uicNumber = Mdt::UicNumber::fromString(" 9485 7 560253");
    REQUIRE( toString(uicNumber) == std::string("94 85 7 560 253-7") );
  }

  SECTION("50 85 3943 862-4")
  {
    const auto uicNumber = Mdt::UicNumber::fromString("50 8539 43 862 ");
    REQUIRE( toString(uicNumber) == std::string("50 85 3943 862-4") );
  }
}
