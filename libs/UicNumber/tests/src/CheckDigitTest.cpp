#include "catch2/catch.hpp"
#include "Mdt/UicNumber/CheckDigitAlgorithm.h"

using Mdt::UicNumber::UicNumber11DigitArray;
using Mdt::UicNumber::computeCheckDigit;
using Mdt::UicNumber::computeCheckDigitFromString;


TEST_CASE("computeCheckDigit")
{
  SECTION("94 85 7 560 253-7")
  {
    REQUIRE( computeCheckDigit({9,4,8,5,7,5,6,0,2,5,3}) == 7 );
  }

  SECTION("94 85 0 500 039-8")
  {
    REQUIRE( computeCheckDigit({9,4,8,5,0,5,0,0,0,3,9}) == 8 );
  }
}

TEST_CASE("computeCheckDigitFromString")
{
  SECTION("94 85 7 560 253-7")
  {
    REQUIRE( computeCheckDigitFromString("94 85 7 560 253") == 7 );
    REQUIRE( computeCheckDigitFromString("94 85 7 560 253-7") == 7 );
  }

  SECTION("50 85 39 43 862-4")
  {
    REQUIRE( computeCheckDigitFromString("50 85 39 43 862") == 4 );
  }

  SECTION("94 85 0 500 039-8")
  {
    REQUIRE( computeCheckDigitFromString("94 85 0 500 039") == 8 );
  }

  SECTION("94 85 0 514 010-3")
  {
    REQUIRE( computeCheckDigitFromString("94 85 0 514 010") == 3 );
  }

  SECTION("94 85 1 514 010-1")
  {
    REQUIRE( computeCheckDigitFromString("94 85 1 514 010") == 1 );
  }

  SECTION("94 85 2 514 010-9")
  {
    REQUIRE( computeCheckDigitFromString("94 85 2 514 010") == 9 );
  }

  SECTION("94 85 3 514 010-7")
  {
    REQUIRE( computeCheckDigitFromString("94 85 3 514 010") == 7 );
  }

  SECTION("94 85 4 514 010-5")
  {
    REQUIRE( computeCheckDigitFromString("94 85 4 514 010") == 5 );
  }

  SECTION("91 85 4 460 007-8")
  {
    REQUIRE( computeCheckDigitFromString("91 85 4 460 007") == 8 );
  }

  SECTION("91 85 4 450 010-4")
  {
    REQUIRE( computeCheckDigitFromString("91 85 4 450 010") == 4 );
  }

  /// \todo ADD Re 420 + Bt SBZ/DPZ
//   SECTION("94 85 0 000 000-0")
//   {
//     REQUIRE( computeCheckDigitFromString("94 85 0 000 000") == 0 );
//   }
// 
//   SECTION("94 85 0 000 000-0")
//   {
//     REQUIRE( computeCheckDigitFromString("94 85 0 000 000") == 0 );
//   }
// 
//   SECTION("94 85 0 000 000-0")
//   {
//     REQUIRE( computeCheckDigitFromString("94 85 0 000 000") == 0 );
//   }

  SECTION("21 81 2471 217-3")
  {
    REQUIRE( computeCheckDigitFromString("21 81 2471 217") == 3 );
  }

  SECTION("51 80 0843 001-0")
  {
    REQUIRE( computeCheckDigitFromString("51 80 0843 001") == 0 );
  }
}
