/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_UIC_NUMBER_STRING_FORMAT_VALIDATION_ERROR_H
#define MDT_UIC_NUMBER_STRING_FORMAT_VALIDATION_ERROR_H

#include "StringFormatValidationState.h"
#include <stdexcept>

namespace Mdt{ namespace UicNumber{

  /*! \brief UIC number string format error
   *
   * \sa validateUicNumberStringFormat_except()
   */
  class StringFormatValidationError : public std::logic_error
  {
   public:

    /*! \brief Construct a UIC number string format error
     */
    explicit StringFormatValidationError(StringFormatValidationErrorCode code)
     : logic_error( errorMessageString(code) ),
       mErrorCode(code)
    {
    }

    /*! \brief Get error code
     */
    StringFormatValidationErrorCode errorCode() const noexcept
    {
      return mErrorCode;
    }

  private:

    StringFormatValidationErrorCode mErrorCode;
  };

}} // namespace Mdt{ namespace UicNumber{

#endif // #ifndef MDT_UIC_NUMBER_STRING_FORMAT_VALIDATION_ERROR_H
