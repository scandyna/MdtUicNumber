#include "catch2/catch.hpp"
#include "Mdt/UicNumber/StringFormatValidationQt.h"
#include <QString>
#include <QLatin1String>

using Mdt::UicNumber::StringFormatValidationError;
using Mdt::UicNumber::StringFormatValidationErrorCode;
using Mdt::UicNumber::validateUicNumberStringFormat_except;

bool validateUicNumberStringFormat(const char * uic)
{
  return Mdt::UicNumber::validateUicNumberStringFormat( QLatin1String(uic) );
}


TEST_CASE("validateUicNumberStringFormat")
{
  REQUIRE( !validateUicNumberStringFormat("") );
  REQUIRE( !validateUicNumberStringFormat("A") );
  REQUIRE( !validateUicNumberStringFormat("5") );
  REQUIRE( validateUicNumberStringFormat("94 85 7 560 253-7") );
}

TEST_CASE("validateUicNumberStringFormat_except")
{
  bool excpetionThrown = false;

  try{
    validateUicNumberStringFormat_except( QLatin1String("560 253") );
  }catch(const StringFormatValidationError & error){
    excpetionThrown = true;
    REQUIRE( error.errorCode() == StringFormatValidationErrorCode::WrongDigitCount );
  }
  REQUIRE( excpetionThrown );
}
