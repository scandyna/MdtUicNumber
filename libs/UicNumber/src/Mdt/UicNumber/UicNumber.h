/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_UIC_NUMBER_UIC_NUMBER_H
#define MDT_UIC_NUMBER_UIC_NUMBER_H

#include "TypeCode.h"
#include "CountryCode.h"
#include "Algorithm.h"
#include "UicNumber11DigitArray.h"
#include "UicNumber12CharDigitArray.h"
#include "StringFormat.h"
#include "StringFormatValidation.h"
#include "CheckDigitAlgorithm.h"
#include <string>
#include <cstdint>
#include <algorithm>
#include <cassert>

namespace Mdt{ namespace UicNumber{

  /*! \brief Represents a 12 digit UIC number
   *
   * A UIC number is composed of 3 main blocks:
   * - The international block, digits 1-4
   * - A variable block, digits 5-11
   * - A check digit, digit 12
   *
   * The international block is composed of a type code and a country code.
   * The UIC number can finaly be representad by 4 blocks:
   * - The type code, digits 1-2
   * - The country code, digits 3-4
   * - The variable block, digits 5-11
   * - A check digit, digit 12
   *
   * \code
   * const std::string uicNumberString = "94 85 7 560 253";
   * if( !Mdt::UicNumber::validateUicNumberStringFormat(uicNumberString) ){
   *   return someError;
   * }
   * const auto uicNumber = Mdt::UicNumber::fromString(uicNumberString);
   * \endcode
   *
   * \sa validateUicNumberStringFormat()
   * \sa fromString()
   * \sa https://en.wikipedia.org/wiki/UIC_identification_marking_for_tractive_stock
   * \sa https://en.wikipedia.org/wiki/UIC_wagon_numbers
   */
  class UicNumber
  {
   public:


    /*! \brief Construct a UIC number
     *
     * \pre \a variableBlock must be in valid range ( 0 <= \a variableBlock <= 9999999 )
     */
    constexpr UicNumber(TypeCode typeCode, CountryCode countryCode, int32_t variableBlock) noexcept
     : mTypeCode(typeCode),
       mCountryCode(countryCode),
       mVariableBlock(variableBlock)
    {
      assert(variableBlock >= 0);
      assert(variableBlock <= 9999999);
      setCheckDigit();
    }

    /*! \brief Copy construct a UIC number from \a other
     */
    constexpr UicNumber(const UicNumber & other) noexcept = default;

    /*! \brief Copy assign \a other to this UIC number
     */
    constexpr UicNumber & operator=(const UicNumber & other) noexcept = default;

    /*! \brief Move construct a UIC number from \a other
     */
    constexpr UicNumber(UicNumber && other) noexcept = default;

    /*! \brief Move assign \a other to this UIC number
     */
    constexpr UicNumber & operator=(UicNumber && other) noexcept = default;

    /*! \brief Get type code
     */
    constexpr TypeCode typeCode() const noexcept
    {
      return mTypeCode;
    }

    /*! \brief Get country code
     */
    constexpr CountryCode countryCode() const noexcept
    {
      return mCountryCode;
    }

    /*! \brief Get variable block
     */
    constexpr int32_t variableBlock() const noexcept
    {
      return mVariableBlock;
    }

    /*! \brief Get the check digit
     */
    constexpr int8_t checkDigit() const noexcept
    {
      return mCheckDigit;
    }

    /*! \brief Get a 11 (numeric) digit array from this UIC number
     */
    UicNumber11DigitArray to11DigitArray() const noexcept
    {
      UicNumber11DigitArray digits;

      digits[0] = tensDigitFromValueBase10( static_cast<int>(mTypeCode) );
      digits[1] = onceDigitFromValueBase10( static_cast<int>(mTypeCode) );
      digits[2] = tensDigitFromValueBase10( static_cast<int>(mCountryCode) );
      digits[3] = onceDigitFromValueBase10( static_cast<int>(mCountryCode) );
      digits[4] = millionsDigitFromValueBase10(mVariableBlock);
      digits[5] = hundredThousandsDigitFromValueBase10(mVariableBlock);
      digits[6] = tenThousandsDigitFromValueBase10(mVariableBlock);
      digits[7] = thousandsDigitFromValueBase10(mVariableBlock);
      digits[8] = hundredsDigitFromValueBase10(mVariableBlock);
      digits[9] = tensDigitFromValueBase10(mVariableBlock);
      digits[10] = onceDigitFromValueBase10(mVariableBlock);

      return digits;
    }

    /*! \brief Get a 12 char digit array from this UIC number
     */
    UicNumber12CharDigitArray to12CharDigitArray() const noexcept
    {
      UicNumber12CharDigitArray charDigits;
      const UicNumber11DigitArray intDigits = to11DigitArray();

      std::transform(intDigits.cbegin(), intDigits.cend(), charDigits.begin(), charFromInt8);
      charDigits[11] = charFromInt8(mCheckDigit);

      return charDigits;
    }

//     /*! \brief
//      */
//     constexpr bool isValid() const noexcept
//     {
//       return false;
//     }

//     /*! \brief
//      */
//     constexpr bool isZero() const noexcept
//     {
//       return false;
//     }

   private:

    void setCheckDigit()
    {
      mCheckDigit = computeCheckDigit( to11DigitArray() );
    }

    TypeCode mTypeCode;
    CountryCode mCountryCode;
    int8_t mCheckDigit = -1;
    int32_t mVariableBlock;
  };

  namespace Impl{

    /*! \internal
     */
    template<typename StringType, typename ToChar, typename ToInt>
    UicNumber fromString(StringType uicNumberString, ToChar toChar, ToInt toInt)
    {
      removeSpacesAndDashes(uicNumberString, toChar);
      assert( stringCounts11or12chars(uicNumberString) );

      const int8_t typeCodeInt = toInt(uicNumberString, 0, 2);
      const TypeCode typeCode = typeCodeFromInt(typeCodeInt);

      const int8_t countryCodeInt = toInt(uicNumberString, 2, 2);
      const CountryCode countryCode = countryCodeFromInt(countryCodeInt);

      const int32_t variableBlock = toInt(uicNumberString, 4, 7);

      return UicNumber(typeCode, countryCode, variableBlock);
    }

  } // namespace Impl{


  /*! \brief Create a UIC number from a string
   *
   * \pre \a uicNumberString must have a valid format
   * \sa validateUicNumberStringFormat()
   * \sa UicNumber
   */
  inline
  UicNumber fromString(const std::string & uicNumberString)
  {
    assert( validateUicNumberStringFormat(uicNumberString) );

    return Impl::fromString(uicNumberString, toChar, toInt);
  }

  /*! \brief Get a string representation of \a uicNumber
   *
   * \a fmt is a functor with this signature:
   * \code
   * std::string myFormat(const UicNumber12CharDigitArray & digits);
   * \endcode
   *
   * Example of a fmt implementation:
   * \code
   * std::string myFormat(const UicNumber12CharDigitArray & digits)
   * {
   *   std::string uicNumberString(17, ' ');
   *
   *   uicNumberString[0] = digits[0];
   *   uicNumberString[1] = digits[1];
   *
   *   uicNumberString[3] = digits[2];
   *   uicNumberString[4] = digits[3];
   *
   *   uicNumberString[6] = digits[4];
   *
   *   uicNumberString[8] = digits[5];
   *   uicNumberString[9] = digits[6];
   *   uicNumberString[10] = digits[7];
   *
   *   uicNumberString[12] = digits[8];
   *   uicNumberString[13] = digits[9];
   *   uicNumberString[14] = digits[10];
   *   uicNumberString[15] = '-';
   *   uicNumberString[16] = digits[11];
   *
   *   return uicNumberString;
   * }
   * \endcode
   *
   * \sa toString(const UicNumber &)
   */
  template<typename StringFormatFunc>
  std::string toString(const UicNumber & uicNumber, StringFormatFunc fmt)
  {
    return fmt( uicNumber.to12CharDigitArray() );
  }

  /*! \brief Get a string representation of \a uicNumber
   *
   * This overload will choose a format regarding the type code
   *
   * \sa toString(const UicNumber &, StringFormatFunc)
   */
  inline
  std::string toString(const UicNumber & uicNumber)
  {
    switch( uicNumber.typeCode() ){
      case TypeCode::MiscellaneousTractiveUnit:
      case TypeCode::ElectricLocomotive:
      case TypeCode::DieselLocomotive:
      case TypeCode::HighSpeedElectricMultipleUnit:
      case TypeCode::ElectricMultipleUnit:
      case TypeCode::DieselMultipleUnit:
      case TypeCode::SpecialisedTrailer:
      case TypeCode::ElectricShunter:
      case TypeCode::DieselShunter:
      case TypeCode::SpecialTractiveVehicle:
        return toString(uicNumber, toTractiveStockFormat);
      default:
        break;
    }
    return toString(uicNumber, toPassengerCoachFormat);
  }

}} // namespace Mdt{ namespace UicNumber{

#endif // #ifndef MDT_UIC_NUMBER_UIC_NUMBER_H
