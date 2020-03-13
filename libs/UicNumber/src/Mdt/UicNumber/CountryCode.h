/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_UIC_NUMBER_COUNTRY_CODE_H
#define MDT_UIC_NUMBER_COUNTRY_CODE_H

#include <cstdint>

namespace Mdt{ namespace UicNumber{

  /*! \brief UIC number country code
   *
   * \sa countryCodeFromInt()
   * \sa https://en.wikipedia.org/wiki/List_of_UIC_country_codes
   * \sa https://en.wikipedia.org/wiki/UIC_identification_marking_for_tractive_stock
   * \sa https://en.wikipedia.org/wiki/UIC_wagon_numbers
   */
  enum class CountryCode : int8_t
  {
    Unknown = 0,        /*!< 00: unknown country */
    Germany = 80,       /*!< 80: Germany */
    Austria = 81,       /*!< 81: Austria */
    Italy = 83,         /*!< 83: Italy */
    Switzerland = 85,   /*!< 85: Switzerland */
    France = 87,        /*!< 87: France */
    Belgium = 88        /*!< 88: Belgium */
  };

  /*! \brief Get a country code from a int
   */
  inline
  constexpr CountryCode countryCodeFromInt(int8_t v) noexcept
  {
    switch(v){
      case 80:
        return CountryCode::Germany;
      case 81:
        return CountryCode::Austria;
      case 83:
        return CountryCode::Italy;
      case 85:
        return CountryCode::Switzerland;
      case 87:
        return CountryCode::France;
      case 88:
        return CountryCode::Belgium;
    }
    return CountryCode::Unknown;
  }

}} // namespace Mdt{ namespace UicNumber{

#endif // #ifndef MDT_UIC_NUMBER_COUNTRY_CODE_H
