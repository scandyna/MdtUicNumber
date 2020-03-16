/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_UIC_NUMBER_STRING_FORMAT_H
#define MDT_UIC_NUMBER_STRING_FORMAT_H

#include "UicNumber12CharDigitArray.h"
#include <string>

namespace Mdt{ namespace UicNumber{

  /*! \brief Format a UIC number to the tractive stock format
   */
  std::string toTractiveStockFormat(const UicNumber12CharDigitArray & digits)
  {
    std::string uicNumberString(17, ' ');

    uicNumberString[0] = digits[0];
    uicNumberString[1] = digits[1];

    uicNumberString[3] = digits[2];
    uicNumberString[4] = digits[3];

    uicNumberString[6] = digits[4];

    uicNumberString[8] = digits[5];
    uicNumberString[9] = digits[6];
    uicNumberString[10] = digits[7];

    uicNumberString[12] = digits[8];
    uicNumberString[13] = digits[9];
    uicNumberString[14] = digits[10];
    uicNumberString[15] = '-';
    uicNumberString[16] = digits[11];

    return uicNumberString;
  }

  /*! \brief Format a UIC number to the tractive stock format
   */
  std::string toPassengerCoachFormat(const UicNumber12CharDigitArray & digits)
  {
    std::string uicNumberString(16, ' ');

    uicNumberString[0] = digits[0];
    uicNumberString[1] = digits[1];

    uicNumberString[3] = digits[2];
    uicNumberString[4] = digits[3];

    uicNumberString[6] = digits[4];
    uicNumberString[7] = digits[5];
    uicNumberString[8] = digits[6];
    uicNumberString[9] = digits[7];

    uicNumberString[11] = digits[8];
    uicNumberString[12] = digits[9];
    uicNumberString[13] = digits[10];
    uicNumberString[14] = '-';
    uicNumberString[15] = digits[11];

    return uicNumberString;
  }

}} // namespace Mdt{ namespace UicNumber{

#endif // #ifndef MDT_UIC_NUMBER_STRING_FORMAT_H
