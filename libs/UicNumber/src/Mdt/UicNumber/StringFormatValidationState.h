/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_UIC_NUMBER_STRING_FORMAT_VALIDATION_STATE_H
#define MDT_UIC_NUMBER_STRING_FORMAT_VALIDATION_STATE_H

#include "StringFormatValidationErrorCode.h"
#include <string>

namespace Mdt{ namespace UicNumber{

  /*! \brief UIC number string format validation state
   *
   * \sa validateUicNumberStringFormat()
   * \sa errorMessageString()
   */
  class StringFormatValidationState
  {
   public:

    constexpr StringFormatValidationState() noexcept = delete;

    /*! \brief Construct a validation state
     */
    constexpr StringFormatValidationState(StringFormatValidationErrorCode code) noexcept
     : mErrorCode(code)
    {
    }

    /*! \brief Copy construct a validation state from \a other
     */
    constexpr StringFormatValidationState(const StringFormatValidationState & other) noexcept = default;

    /*! \brief Copy assign \a other to this validation state
     */
    constexpr StringFormatValidationState & operator=(const StringFormatValidationState & other) noexcept = default;

    /*! \brief Move construct a validation state from \a other
     */
    constexpr StringFormatValidationState(StringFormatValidationState && other) noexcept = default;

    /*! \brief Move assign \a other to this validation state
     */
    constexpr StringFormatValidationState & operator=(StringFormatValidationState && other) noexcept = default;

    /*! \brief Check if this validation state is valid
     */
    constexpr bool isValid() const noexcept
    {
      return mErrorCode == StringFormatValidationErrorCode::NoError;
    }

    /*! \brief Returns isValid()
     */
    constexpr operator bool() const noexcept
    {
      return isValid();
    }

    /*! \brief Get error code
     */
    constexpr StringFormatValidationErrorCode errorCode() const noexcept
    {
      return mErrorCode;
    }

   private:

    StringFormatValidationErrorCode mErrorCode;
  };


  /*! \brief Get a generic error message string from \a errorCode
   *
   * If you use Qt, consider using errorMessageQString(),
   * which returns a translated message.
   */
  inline
  std::string errorMessageString(StringFormatValidationErrorCode errorCode)
  {
    switch(errorCode){
      case StringFormatValidationErrorCode::NoError:
        return std::string();
      case StringFormatValidationErrorCode::WrongDigitCount:
        return "The count of digits is wrong (allowed are 11 or 12 digits";
      case StringFormatValidationErrorCode::UnallowedChar:
        return "At least one unallowed char is present in the string ";
    }
    return std::string();
  }

}} // namespace Mdt{ namespace UicNumber{

#endif // #ifndef MDT_UIC_NUMBER_STRING_FORMAT_VALIDATION_STATE_H
