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
#include "StringFormatValidationState.h"
#include "StringFormatValidationError.h"
#include <string>
#include <cstdint>
#include <iterator>
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

    TypeCode mTypeCode;
    CountryCode mCountryCode;
    int8_t mCheckDigit = -1;
    int32_t mVariableBlock;
  };

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
    StringFormatValidationState validateUicNumberStringFormat(StringType uicNumberString, ToChar toChar)
    {
      if( !validateStringContent(uicNumberString, toChar) ){
        return StringFormatValidationState(StringFormatValidationErrorCode::UnallowedChar);
      }
      removeSpacesAndDashes(uicNumberString, toChar);
      if( !stringCounts11or12chars(uicNumberString) ){
        return StringFormatValidationState(StringFormatValidationErrorCode::WrongDigitCount);
      }
      return StringFormatValidationState(StringFormatValidationErrorCode::NoError);
    }

    /*! \internal
     */
    template<typename StringType, typename ToChar>
    void validateUicNumberStringFormat_except(StringType uicNumberString, ToChar toChar)
    {
      const auto state = validateUicNumberStringFormat(uicNumberString, toChar);
      if( !state.isValid() ){
        throw StringFormatValidationError( state.errorCode() );
      }
    }

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

  /*! \brief Validate a UIC number string format
   *
   * A valid UIC number contains either 11 digits (check digit missing)
   * or 12 digits.
   * It can optionally contain a dash before the check digit.
   * Spaces are also alowed at arbitrary places.
   *
   * Here are examples of accepted UIC numbers, each digit represented as \a 0 .
   * \code
   * 00 00 00 00 000
   * 00 00 00 00 000-0
   * 00 00 0000 000
   * 00 00 0000 000-0
   * \endcode
   *
   * Note that this function accepts many spaces and hyphens at arbitrary places.
   * Those inputs will also be accepted:
   * \code
   * 00 0 0 000 00 0 0
   * 00 00 00-00 000
   * 00000000000
   * \endcode
   *
   * Example:
   * \code
   * const std::string uicNumber = "94 85 7 560 253";
   * const auto validationState = Mdt::UicNumber::validateUicNumberStringFormat(uicNumber);
   * if( !validationState.isValid() ){
   *   switch( validationState.errorCode() ){
   *     case StringFormatValidationErrorCode::WrongDigitCount:
   *       outputError("Given UIC number contains not the correct count of digits (can be either 11 or 12)");
   *       break;
   *     default:
   *       outputError( "Given UIC number is not valid, reason: %1", validationState.errorMessage() );
   *   }
   * }
   * \endcode
   *
   * This function can also be used as it returned a bool:
   * \code
   * const std::string uicNumber = "94 85 7 560 253";
   * if( !Mdt::UicNumber::validateUicNumberStringFormat(uicNumber) ){
   *   outputError("Given UIC number is not valid");
   * }
   * \endcode
   *
   * \sa validateUicNumberStringFormat_except()
   * \sa UicNumber
   */
  inline
  StringFormatValidationState validateUicNumberStringFormat(const std::string & uicNumberString)
  {
    return Impl::validateUicNumberStringFormat(uicNumberString, toChar);
  }

  /*! \brief Validate a UIC number string format
   *
   * This function is the same as validateUicNumberStringFormat()
   * but trows a exception if \a uicNumber has not a correct format.
   *
   * Example:
   * \code
   * const std::string uicNumber = "94 85 7 560 253";
   * try{
   *   validateUicNumberStringFormat_except(uicNumber);
   * }catch(const StringFormatValidationError & validationError){
   *   switch( validationError.errorCode() ){
   *     case StringFormatValidationErrorCode::WrongDigitCount:
   *       outputError("Given UIC number contains not the correct count of digits (can be either 11 or 12)");
   *       break;
   *     default:
   *       outputError( "Given UIC number is not valid, reason: %1", validationError.what() );
   *   }
   * }
   * \endcode
   *
   * \exception StringFormatValidationError
   * \sa validateUicNumberStringFormat()
   * \sa UicNumber
   */
  inline
  void validateUicNumberStringFormat_except(const std::string & uicNumberString)
  {
    Impl::validateUicNumberStringFormat_except(uicNumberString, toChar);
  }

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

}} // namespace Mdt{ namespace UicNumber{

#endif // #ifndef MDT_UIC_NUMBER_UIC_NUMBER_H
