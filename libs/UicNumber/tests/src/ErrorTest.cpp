#include "catch2/catch.hpp"
#include "Mdt/UicNumber/StringFormatValidationState"

using Mdt::UicNumber::StringFormatValidationErrorCode;
using Mdt::UicNumber::StringFormatValidationState;


TEST_CASE("StringFormatValidationState")
{
  SECTION("NoError")
  {
    StringFormatValidationState state(StringFormatValidationErrorCode::NoError);
    REQUIRE( state.isValid() );
    REQUIRE( state );
  }

  SECTION("WrongDigitCount")
  {
    StringFormatValidationState state(StringFormatValidationErrorCode::WrongDigitCount);
    REQUIRE( !state.isValid() );
    REQUIRE( !state );
  }

  SECTION("UnallowedChar")
  {
    StringFormatValidationState state(StringFormatValidationErrorCode::UnallowedChar);
    REQUIRE( !state.isValid() );
    REQUIRE( !state );
  }
}
