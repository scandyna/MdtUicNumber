/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_UIC_NUMBER_UIC_NUMBER_11_DIGIT_ARRAY_H
#define MDT_UIC_NUMBER_UIC_NUMBER_11_DIGIT_ARRAY_H

#include <array>
#include <cstdint>

namespace Mdt{ namespace UicNumber{

  /*! \brief Represents a UIC number in the form of 11 integer digits without the check digit
   */
  using UicNumber11DigitArray = std::array<int8_t, 11>;

}} // namespace Mdt{ namespace UicNumber{

#endif // #ifndef MDT_UIC_NUMBER_UIC_NUMBER_11_DIGIT_ARRAY_H
