/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_UIC_NUMBER_STRING_FORMAT_VALIDATION_ERROR_CODE_H
#define MDT_UIC_NUMBER_STRING_FORMAT_VALIDATION_ERROR_CODE_H

namespace Mdt{ namespace UicNumber{

  /*! \brief UIC number string format error
   *
   * \sa validateUicNumberStringFormat()
   */
  enum class StringFormatValidationErrorCode
  {
    NoError,          /*!< No error */
    WrongDigitCount,  /*!< The count of digits is wrong (allowed are 11 or 12 digits */
    UnallowedChar     /*!< At least one unallowed char is present in the string */
  };

}} // namespace Mdt{ namespace UicNumber{

#endif // #ifndef MDT_UIC_NUMBER_STRING_FORMAT_VALIDATION_ERROR_CODE_H
