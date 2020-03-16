#include "catch2/catch.hpp"
#include "Mdt/UicNumber/Algorithm"
#include <string>

using Mdt::UicNumber::UicNumber11DigitArray;
using Mdt::UicNumber::int8FromChar;
using Mdt::UicNumber::charFromInt8;
using Mdt::UicNumber::toInt;
using Mdt::UicNumber::onceDigitFromValueBase10;
using Mdt::UicNumber::tensDigitFromValueBase10;
using Mdt::UicNumber::hundredsDigitFromValueBase10;
using Mdt::UicNumber::thousandsDigitFromValueBase10;
using Mdt::UicNumber::tenThousandsDigitFromValueBase10;
using Mdt::UicNumber::hundredThousandsDigitFromValueBase10;
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

UicNumber11DigitArray uicNumber11DigitArrayFromString(const std::string & uic)
{
  using Mdt::UicNumber::toChar;

  return Mdt::UicNumber::Impl::uicNumber11DigitArrayFromString(uic, toChar);
}


TEST_CASE("int8FromChar")
{
  SECTION("0")
  {
    REQUIRE( int8FromChar('0') == 0 );
  }
  SECTION("1")
  {
    REQUIRE( int8FromChar('1') == 1 );
  }
  SECTION("2")
  {
    REQUIRE( int8FromChar('2') == 2 );
  }
  SECTION("3")
  {
    REQUIRE( int8FromChar('3') == 3 );
  }
  SECTION("5")
  {
    REQUIRE( int8FromChar('5') == 5 );
  }
  SECTION("9")
  {
    REQUIRE( int8FromChar('9') == 9 );
  }
}

TEST_CASE("charFromInt8")
{
  SECTION("0")
  {
    REQUIRE( charFromInt8(0) == '0' );
  }
  SECTION("5")
  {
    REQUIRE( charFromInt8(5) == '5' );
  }
  SECTION("9")
  {
    REQUIRE( charFromInt8(9) == '9' );
  }
}

TEST_CASE("toInt")
{
  SECTION("00")
  {
    REQUIRE( toInt("00", 0, 2) == 0 );
  }

  SECTION("85")
  {
    REQUIRE( toInt("85", 0, 2) == 85 );
  }

  SECTION("7560253")
  {
    REQUIRE( toInt("7560253", 0, 7) == 7560253 );
  }

  SECTION("94857560253 94")
  {
    REQUIRE( toInt("94857560253", 0, 2) == 94 );
  }

  SECTION("94857560253 85")
  {
    REQUIRE( toInt("94857560253", 2, 2) == 85 );
  }

  SECTION("94857560253 7560253")
  {
    REQUIRE( toInt("94857560253", 4, 7) == 7560253 );
  }
}

TEST_CASE("onceDigitFromValueBase10")
{
  SECTION("0")
  {
    REQUIRE( onceDigitFromValueBase10(0) == 0 );
  }

  SECTION("1")
  {
    REQUIRE( onceDigitFromValueBase10(1) == 1 );
  }

  SECTION("9")
  {
    REQUIRE( onceDigitFromValueBase10(9) == 9 );
  }

  SECTION("10")
  {
    REQUIRE( onceDigitFromValueBase10(10) == 0 );
  }

  SECTION("11")
  {
    REQUIRE( onceDigitFromValueBase10(11) == 1 );
  }

  SECTION("12")
  {
    REQUIRE( onceDigitFromValueBase10(12) == 2 );
  }

  SECTION("19")
  {
    REQUIRE( onceDigitFromValueBase10(19) == 9 );
  }

  SECTION("123")
  {
    REQUIRE( onceDigitFromValueBase10(123) == 3 );
  }

  SECTION("1234")
  {
    REQUIRE( onceDigitFromValueBase10(1234) == 4 );
  }
}

TEST_CASE("tensDigitFromValueBase10")
{
  SECTION("0")
  {
    REQUIRE( tensDigitFromValueBase10(0) == 0 );
  }

  SECTION("9")
  {
    REQUIRE( tensDigitFromValueBase10(9) == 0 );
  }

  SECTION("10")
  {
    REQUIRE( tensDigitFromValueBase10(10) == 1 );
  }

  SECTION("11")
  {
    REQUIRE( tensDigitFromValueBase10(11) == 1 );
  }

  SECTION("12")
  {
    REQUIRE( tensDigitFromValueBase10(12) == 1 );
  }

  SECTION("19")
  {
    REQUIRE( tensDigitFromValueBase10(19) == 1 );
  }

  SECTION("20")
  {
    REQUIRE( tensDigitFromValueBase10(20) == 2 );
  }

  SECTION("99")
  {
    REQUIRE( tensDigitFromValueBase10(99) == 9 );
  }

  SECTION("100")
  {
    REQUIRE( tensDigitFromValueBase10(100) == 0 );
  }

  SECTION("101")
  {
    REQUIRE( tensDigitFromValueBase10(101) == 0 );
  }

  SECTION("123")
  {
    REQUIRE( tensDigitFromValueBase10(123) == 2 );
  }

  SECTION("1234")
  {
    REQUIRE( tensDigitFromValueBase10(1234) == 3 );
  }
}

TEST_CASE("hundredsDigitFromValueBase10")
{
  SECTION("0")
  {
    REQUIRE( hundredsDigitFromValueBase10(0) == 0 );
  }

  SECTION("9")
  {
    REQUIRE( hundredsDigitFromValueBase10(9) == 0 );
  }

  SECTION("99")
  {
    REQUIRE( hundredsDigitFromValueBase10(99) == 0 );
  }

  SECTION("100")
  {
    REQUIRE( hundredsDigitFromValueBase10(100) == 1 );
  }

  SECTION("101")
  {
    REQUIRE( hundredsDigitFromValueBase10(101) == 1 );
  }

  SECTION("123")
  {
    REQUIRE( hundredsDigitFromValueBase10(123) == 1 );
  }

  SECTION("246")
  {
    REQUIRE( hundredsDigitFromValueBase10(246) == 2 );
  }

  SECTION("1234")
  {
    REQUIRE( hundredsDigitFromValueBase10(1234) == 2 );
  }

  SECTION("2468")
  {
    REQUIRE( hundredsDigitFromValueBase10(2468) == 4 );
  }

  SECTION("12345")
  {
    REQUIRE( hundredsDigitFromValueBase10(12345) == 3 );
  }
}

TEST_CASE("thousandsDigitFromValueBase10")
{
  SECTION("0")
  {
    REQUIRE( thousandsDigitFromValueBase10(0) == 0 );
  }

  SECTION("999")
  {
    REQUIRE( thousandsDigitFromValueBase10(999) == 0 );
  }

  SECTION("1000")
  {
    REQUIRE( thousandsDigitFromValueBase10(1000) == 1 );
  }

  SECTION("1001")
  {
    REQUIRE( thousandsDigitFromValueBase10(1001) == 1 );
  }

  SECTION("123")
  {
    REQUIRE( thousandsDigitFromValueBase10(123) == 0 );
  }

  SECTION("1234")
  {
    REQUIRE( thousandsDigitFromValueBase10(1234) == 1 );
  }

  SECTION("12345")
  {
    REQUIRE( thousandsDigitFromValueBase10(12345) == 2 );
  }
}

TEST_CASE("tenThousandsDigitFromValueBase10")
{
  SECTION("0")
  {
    REQUIRE( tenThousandsDigitFromValueBase10(0) == 0 );
  }

  SECTION("9999")
  {
    REQUIRE( tenThousandsDigitFromValueBase10(9999) == 0 );
  }

  SECTION("10'000")
  {
    REQUIRE( tenThousandsDigitFromValueBase10(10000) == 1 );
  }

  SECTION("10'001")
  {
    REQUIRE( tenThousandsDigitFromValueBase10(10001) == 1 );
  }

  SECTION("123")
  {
    REQUIRE( tenThousandsDigitFromValueBase10(123) == 0 );
  }

  SECTION("1'234")
  {
    REQUIRE( tenThousandsDigitFromValueBase10(1234) == 0 );
  }

  SECTION("12'345")
  {
    REQUIRE( tenThousandsDigitFromValueBase10(12345) == 1 );
  }

  SECTION("123'456")
  {
    REQUIRE( tenThousandsDigitFromValueBase10(123456) == 2 );
  }
}

TEST_CASE("hundredThousandsDigitFromValueBase10")
{
  SECTION("0")
  {
    REQUIRE( hundredThousandsDigitFromValueBase10(0) == 0 );
  }

  SECTION("999")
  {
    REQUIRE( hundredThousandsDigitFromValueBase10(999) == 0 );
  }

  SECTION("99'999")
  {
    REQUIRE( hundredThousandsDigitFromValueBase10(99999) == 0 );
  }

  SECTION("100'000")
  {
    REQUIRE( hundredThousandsDigitFromValueBase10(100000) == 1 );
  }

  SECTION("100'001")
  {
    REQUIRE( hundredThousandsDigitFromValueBase10(100001) == 1 );
  }

  SECTION("100'002")
  {
    REQUIRE( hundredThousandsDigitFromValueBase10(100'002) == 1 );
  }

  SECTION("123")
  {
    REQUIRE( hundredThousandsDigitFromValueBase10(123) == 0 );
  }

  SECTION("1'234")
  {
    REQUIRE( hundredThousandsDigitFromValueBase10(1234) == 0 );
  }

  SECTION("12'345")
  {
    REQUIRE( hundredThousandsDigitFromValueBase10(12345) == 0 );
  }

  SECTION("123'456")
  {
    REQUIRE( hundredThousandsDigitFromValueBase10(123456) == 1 );
  }

  SECTION("1'234'567")
  {
    REQUIRE( hundredThousandsDigitFromValueBase10(1234567) == 2 );
  }
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

TEST_CASE("uicNumber11DigitArrayFromString")
{
  SECTION("94 85 7 560 253")
  {
    REQUIRE( uicNumber11DigitArrayFromString("94 85 7 560 253") == UicNumber11DigitArray{9,4,8,5,7,5,6,0,2,5,3} );
  }

  SECTION("94 85 7 560 253-7")
  {
    REQUIRE( uicNumber11DigitArrayFromString("94 85 7 560 253-7") == UicNumber11DigitArray{9,4,8,5,7,5,6,0,2,5,3} );
  }
}
