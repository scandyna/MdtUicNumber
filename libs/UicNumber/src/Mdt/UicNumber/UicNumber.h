/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_UIC_NUMBER_UIC_NUMBER_H
#define MDT_UIC_NUMBER_UIC_NUMBER_H

#include "TypeCode.h"
#include "Algorithm.h"
#include "StringFormatValidationState.h"
#include "StringFormatValidationError.h"
#include <string>
#include <cassert>

namespace Mdt{ namespace UicNumber{

  /*! \brief Represents a 12 digit UIC number
   *
   * A UIC number 3 main blocks:
   * - The international block, digits 1-4
   * - The national block, digits 5-11
   * - A check digit, digit 12
   *
   * The international block is composed of a type code and a country code.
   * The UIC number can finaly be representad by 4 blocks:
   * - The type code, digits 1-2
   * - The country code, digits 3-4
   * - The national block, digits 5-11
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
   * \sa fromString()
   * \sa https://en.wikipedia.org/wiki/UIC_identification_marking_for_tractive_stock
   * \sa https://en.wikipedia.org/wiki/UIC_wagon_numbers
   */
  class UicNumber
  {
   public:


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
    template<typename StringType, typename ToChar>
    UicNumber fromString(StringType uicNumberString, ToChar toChar)
    {
      removeSpacesAndDashes(uicNumberString, toChar);
      assert( stringCounts11or12chars(uicNumberString) );

      return UicNumber();
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

    return Impl::fromString(uicNumberString, toChar);
  }

}} // namespace Mdt{ namespace UicNumber{

#endif // #ifndef MDT_UIC_NUMBER_UIC_NUMBER_H
