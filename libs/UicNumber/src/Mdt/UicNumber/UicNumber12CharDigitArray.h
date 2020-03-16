/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_UIC_NUMBER_UIC_NUMBER_12_CHAR_DIGIT_ARRAY_H
#define MDT_UIC_NUMBER_UIC_NUMBER_12_CHAR_DIGIT_ARRAY_H

#include <array>

namespace Mdt{ namespace UicNumber{

  /*! \brief Represents a UIC number in the form of 12 char digits
   */
  using UicNumber12CharDigitArray = std::array<char, 12>;

}} // namespace Mdt{ namespace UicNumber{

#endif // #ifndef MDT_UIC_NUMBER_UIC_NUMBER_12_CHAR_DIGIT_ARRAY_H
