#include "catch2/catch.hpp"
#include "Mdt/UicNumber/UicNumber"

using Mdt::UicNumber::TypeCode;
using Mdt::UicNumber::CountryCode;


TEST_CASE("UicNumberfromString")
{
  SECTION("94 85 7 560 253")
  {
    const auto uicNumber = Mdt::UicNumber::fromString("94 85 7 560 253");
    REQUIRE( uicNumber.typeCode() == TypeCode::ElectricMultipleUnit );
    REQUIRE( uicNumber.countryCode() == CountryCode::Switzerland );
    REQUIRE( uicNumber.variableBlock() == 7560253 );
  }

  SECTION("00 00 0 000 000")
  {
    const auto uicNumber = Mdt::UicNumber::fromString("00 00 0 000 000");
    REQUIRE( uicNumber.typeCode() == TypeCode::Unknown );
    REQUIRE( uicNumber.countryCode() == CountryCode::Unknown );
    REQUIRE( uicNumber.variableBlock() == 0 );
  }
}
