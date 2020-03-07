#include "catch2/catch.hpp"
#include "Mdt/UicNumber/StringFormatValidationStateQt"

using Mdt::UicNumber::StringFormatValidationErrorCode;

TEST_CASE("errorMessageQString")
{
  REQUIRE( !Mdt::UicNumber::errorMessageQString(StringFormatValidationErrorCode::UnallowedChar).isEmpty() );
}
