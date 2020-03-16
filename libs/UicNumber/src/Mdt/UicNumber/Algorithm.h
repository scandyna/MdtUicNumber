/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_UIC_NUMBER_ALGORITHM_H
#define MDT_UIC_NUMBER_ALGORITHM_H

#include "UicNumber11DigitArray.h"
#include <cctype>
#include <string>
#include <iterator>
#include <algorithm>
#include <cstdint>
#include <cassert>

namespace Mdt{ namespace UicNumber{

  /*! \internal
   */
  inline
  char toChar(char c) noexcept
  {
    return c;
  }

  /*! \brief Check if \a c is a space
   */
  inline
  bool isSpace(char c) noexcept
  {
    return std::isspace(static_cast<unsigned char>(c));
  }

  /*! \brief Check if \a c is a digit
   *
   * Only number characters [0-9] are considered as digits.
   */
  inline
  bool isDigit(char c) noexcept
  {
    return std::isdigit(static_cast<unsigned char>( toChar(c) ));
  }

  /*! \internal
   *
   * \pre \a c must represent a numeric value in base 10
   */
  inline
  int8_t int8FromChar(char c)
  {
    assert( isDigit(c) );

    return c - '0';
  }

  /*! \internal
   *
   * \pre \a i must represent a single digit [0-9]
   */
  inline
  char charFromInt8(int8_t i)
  {
    assert( i >= 0 );
    assert( i <= 9 );

    return i + '0';
  }

  /*! \internal
   */
  inline
  int toInt(const std::string & str, int position, int length)
  {
    assert( (position+length) <= static_cast<int>(str.length()) );

    return std::stoi(std::string(str, position, length), nullptr, 10);
  }

  /*! \brief Get the ones digit from \a value
   *
   * Examples:
   * \code
   * onceDigitFromValueBase10(1) == 1
   * onceDigitFromValueBase10(12) == 2
   * onceDigitFromValueBase10(123) == 3
   * \endcode
   */
  inline
  int onceDigitFromValueBase10(int value)
  {
    return value % 10;
  }

  /*! \brief Get the tens digit from \a value
   *
   * Examples:
   * \code
   * tensDigitFromValueBase10(1) == 0
   * tensDigitFromValueBase10(12) == 1
   * tensDigitFromValueBase10(123) == 2
   * \endcode
   */
  inline
  int tensDigitFromValueBase10(int value)
  {
    const int tens = value % 100;
    if(tens < 10){
      return 0;
    }
    return (tens - onceDigitFromValueBase10(value)) / 10;
  }

  /*! \brief Get the hundreds digit from \a value
   *
   * Examples:
   * \code
   * hundredsDigitFromValueBase10(1) == 0
   * hundredsDigitFromValueBase10(12) == 0
   * hundredsDigitFromValueBase10(123) == 1
   * hundredsDigitFromValueBase10(1234) == 2
   * \endcode
   */
  inline
  int hundredsDigitFromValueBase10(int value)
  {
    const int hundreds = value % 1000;
    if(hundreds < 100){
      return 0;
    }
    return (hundreds - tensDigitFromValueBase10(value)) / 100;
  }

  /*! \brief Get the thousands digit from \a value
   *
   * Examples:
   * \code
   * thousandsDigitFromValueBase10(1) == 0
   * thousandsDigitFromValueBase10(12) == 0
   * thousandsDigitFromValueBase10(123) == 0
   * thousandsDigitFromValueBase10(1234) == 1
   * thousandsDigitFromValueBase10(12345) == 2
   * \endcode
   */
  inline
  int thousandsDigitFromValueBase10(int value)
  {
    const int thousands = value % 10000;
    if(thousands < 1000){
      return 0;
    }
    return (thousands - hundredsDigitFromValueBase10(value)) / 1000;
  }

  /*! \brief Get the ten-thousands digit from \a value
   *
   * Examples:
   * \code
   * tenThousandsDigitFromValueBase10(123) == 0
   * tenThousandsDigitFromValueBase10(1234) == 0
   * tenThousandsDigitFromValueBase10(12345) == 1
   * tenThousandsDigitFromValueBase10(123456) == 2
   * \endcode
   */
  inline
  int tenThousandsDigitFromValueBase10(int value)
  {
    const int tenThousands = value % 100000;
    if(tenThousands < 10000){
      return 0;
    }
    return (tenThousands - thousandsDigitFromValueBase10(value)) / 10000;
  }

  /*! \brief Get the hundred-thousands digit from \a value
   *
   * Examples:
   * \code
   * hundredThousandsDigitFromValueBase10(1'234) == 0
   * hundredThousandsDigitFromValueBase10(12'345) == 0
   * hundredThousandsDigitFromValueBase10(123'456) == 1
   * hundredThousandsDigitFromValueBase10(1'234'567) == 2
   * \endcode
   */
  inline
  int hundredThousandsDigitFromValueBase10(int value)
  {
    const int hundredThousands = value % 1000000;
    if(hundredThousands < 100000){
      return 0;
    }
    return (hundredThousands - tenThousandsDigitFromValueBase10(value)) / 100000;
  }

  /*! \brief Get the millions digit from \a value
   *
   * Examples:
   * \code
   * millionsDigitFromValueBase10(12'345) == 0
   * millionsDigitFromValueBase10(123'456) == 0
   * millionsDigitFromValueBase10(1'234'567) == 1
   * millionsDigitFromValueBase10(12'345'678) == 2
   * \endcode
   */
  inline
  int millionsDigitFromValueBase10(int value)
  {
    const int millions = value % 10000000;
    if(millions < 1000000){
      return 0;
    }
    return (millions - hundredThousandsDigitFromValueBase10(value)) / 1000000;
  }

  /*! \brief Check if \a c is allowed in a UIC number string
   *
   * Allowed chars are:
   * - Digit
   * - Space
   * - Hyphen
   */
  inline
  bool isAllowedChar(char c) noexcept
  {
    return isDigit(c) || isSpace(c) || (c == '-');
  }


  namespace Impl{

    /*! \internal
     */
    template<typename StringType>
    bool stringCounts11or12chars(const StringType & str) noexcept
    {
      return (str.size() == 11) || (str.size() == 12);
    }

    /*! \internal
     */
    template<typename StringType, typename ToChar>
    bool validateStringContent(const StringType & uicNumberString, ToChar toChar)
    {
      using CharType = typename StringType::value_type;

      const auto pred = [&toChar](CharType c){
        return isAllowedChar( toChar(c) );
      };
      return std::all_of(uicNumberString.cbegin(), uicNumberString.cend(), pred);
    }

    /*! \internal
     */
    template<typename StringType, typename ToChar>
    void removeSpacesAndDashes(StringType & uicNumberString, ToChar toChar)
    {
      using CharType = typename StringType::value_type;

      const auto pred = [&toChar](CharType ch){
        const char c = toChar(ch);
        return isSpace(c) || (c == '-');
      };
      const auto it = std::remove_if(uicNumberString.begin(), uicNumberString.end(), pred);
      const auto count = std::distance(uicNumberString.begin(), it);
      assert(count >= 0);
      // Both std::string and QString have resize, QString does not have erase
      uicNumberString.resize(count);
    }

    /*! \internal
     */
    template<typename StringType, typename ToChar>
    UicNumber11DigitArray uicNumber11DigitArrayFromString(StringType uicNumberString, ToChar toChar)
    {
      UicNumber11DigitArray digits;

      removeSpacesAndDashes(uicNumberString, toChar);
      assert( stringCounts11or12chars(uicNumberString) );

      for(int i = 0; i < 11; ++i){
        digits[i] = int8FromChar( toChar(uicNumberString[i]) );
      }

      return digits;
    }

  } // namespace Impl{


  /*! \brief Validate the content of a string
   *
   * A UIC number can only contain:
   * - Digits
   * - Spaces
   * - A dash before the check digit
   *
   * \todo Current implementation tolerates many hyphens at any places
   */
  inline
  bool validateStringContent(const std::string & uicNumberString)
  {
    return Impl::validateStringContent(uicNumberString, toChar);
  }

  /*! \brief Remove all spaces and dash in a string
   *
   * \note This function blindly removes spaces and hyphens,
   *   regardless of the position and count of hyphens.
   * \sa validateStringContent()
   */
  inline
  void removeSpacesAndDashes(std::string & uicNumberString)
  {
    Impl::removeSpacesAndDashes(uicNumberString, toChar);
  }

}} // namespace Mdt{ namespace UicNumber{

#endif // #ifndef MDT_UIC_NUMBER_ALGORITHM_H
