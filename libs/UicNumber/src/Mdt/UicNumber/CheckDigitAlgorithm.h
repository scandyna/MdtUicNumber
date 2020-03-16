/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_UIC_NUMBER_CHECK_DIGIT_ALGORITHM_H
#define MDT_UIC_NUMBER_CHECK_DIGIT_ALGORITHM_H

#include "UicNumber11DigitArray.h"
#include "StringFormatValidation.h"
#include <string>
#include <cstdint>
#include <numeric>
#include <cassert>

namespace Mdt{ namespace UicNumber{

  /*! \brief Compute the check digit for \a uicNumberDigits
   *
   * \sa https://en.wikipedia.org/wiki/Luhn_algorithm
   */
  inline
  int8_t computeCheckDigit(const UicNumber11DigitArray & uicNumberDigits) noexcept
  {
    bool processCurrentDigit = true;

    const auto op = [&processCurrentDigit](int currentResult, int8_t currentDigit) -> int
    {
      int8_t toSumDigitValue = currentDigit;
      if(processCurrentDigit){
        toSumDigitValue = 2*currentDigit;
        if(toSumDigitValue > 9){
          toSumDigitValue = toSumDigitValue - 9;
        }
      }
      processCurrentDigit = !processCurrentDigit;

      return toSumDigitValue + currentResult;
    };

    const int digitsProecessedSum = std::accumulate(uicNumberDigits.crbegin(), uicNumberDigits.crend(), 0, op);

    return (digitsProecessedSum * 9) % 10;
  }

  namespace Impl{

    /*! \internal
     */
    template<typename StringType, typename ToChar>
    int8_t computeCheckDigitFromString(const StringType & uicNumberString, ToChar toChar)
    {
      return computeCheckDigit( uicNumber11DigitArrayFromString(uicNumberString, toChar) );
    }

  } // namespace Impl{

  /*! \brief Compute the check digit for \a uicNumberString
   *
   * \pre \a uicNumberString must have a valid format
   * \sa validateUicNumberStringFormat()
   * \sa https://en.wikipedia.org/wiki/Luhn_algorithm
   * \sa https://en.wikipedia.org/wiki/UIC_wagon_numbers#Examples
   */
  inline
  int8_t computeCheckDigitFromString(const std::string & uicNumberString)
  {
    assert( validateUicNumberStringFormat(uicNumberString) );

    return Impl::computeCheckDigitFromString(uicNumberString, toChar);
  }


}} // namespace Mdt{ namespace UicNumber{

#endif // #ifndef MDT_UIC_NUMBER_CHECK_DIGIT_ALGORITHM_H
