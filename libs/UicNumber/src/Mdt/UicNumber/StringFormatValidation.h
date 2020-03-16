/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_UIC_NUMBER_STRING_FORMAT_VALIDATION_H
#define MDT_UIC_NUMBER_STRING_FORMAT_VALIDATION_H

#include "StringFormatValidationState.h"
#include "StringFormatValidationError.h"
#include "Algorithm.h"

namespace Mdt{ namespace UicNumber{

  namespace Impl{

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

}} // namespace Mdt{ namespace UicNumber{

#endif // #ifndef MDT_UIC_NUMBER_STRING_FORMAT_VALIDATION_H
