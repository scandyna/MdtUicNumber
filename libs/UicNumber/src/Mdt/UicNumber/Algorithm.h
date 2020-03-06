/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_UIC_NUMBER_ALGORITHM_H
#define MDT_UIC_NUMBER_ALGORITHM_H

#include <cctype>
#include <string>
#include <iterator>
#include <algorithm>
#include <cassert>

namespace Mdt{ namespace UicNumber{

  /*! \internal
   */
  inline
  char toChar(char c) noexcept
  {
    return c;
  }

  /*! \brief Check if \a c is a space
   */
  inline
  bool isSpace(char c) noexcept
  {
    return std::isspace(static_cast<unsigned char>(c));
  }

  /*! \brief Check if \a c is a digit
   *
   * Only number characters [0-9] are considered as digits.
   */
  inline
  bool isDigit(char c) noexcept
  {
    return std::isdigit(static_cast<unsigned char>( toChar(c) ));
  }

  /*! \brief Check if \a c is allowed in a UIC number string
   *
   * Allowed chars are:
   * - Digit
   * - Space
   * - Hyphen
   */
  inline
  bool isAllowedChar(char c) noexcept
  {
    return isDigit(c) || isSpace(c) || (c == '-');
  }

  /*! \brief Get the characters that are allowed for a UIC number in a string
   */


  namespace Impl{

    /*! \internal
     */
    template<typename StringType, typename ToChar>
    bool validateStringContent(const StringType & uicNumberString, ToChar toChar)
    {
      using CharType = typename StringType::value_type;

      const auto pred = [&toChar](CharType c){
        return isAllowedChar( toChar(c) );
      };
      return std::all_of(uicNumberString.cbegin(), uicNumberString.cend(), pred);
    }

    /*! \internal
     */
    template<typename StringType, typename ToChar>
    void removeSpacesAndDashes(StringType & uicNumberString, ToChar toChar)
    {
      using CharType = typename StringType::value_type;

      const auto pred = [&toChar](CharType ch){
        const char c = toChar(ch);
        return isSpace(c) || (c == '-');
      };
      const auto it = std::remove_if(uicNumberString.begin(), uicNumberString.end(), pred);
      const auto count = std::distance(uicNumberString.begin(), it);
      assert(count >= 0);
      // Both std::string and QString have resize, QString does not have erase
      uicNumberString.resize(count);
    }

  } // namespace Impl{


  /*! \brief Validate the content of a string
   *
   * A UIC number can only contain:
   * - Digits
   * - Spaces
   * - A dash before the check digit
   *
   * \todo Current implementation tolerates many hyphens at any places
   */
  inline
  bool validateStringContent(const std::string & uicNumberString)
  {
    return Impl::validateStringContent(uicNumberString, toChar);
  }

  /*! \brief Remove all spaces and dash in a string
   *
   * \note This function blindly removes spaces and hyphens,
   *   regardless of the position and count of hyphens.
   * \sa validateStringContent()
   */
  inline
  void removeSpacesAndDashes(std::string & uicNumberString)
  {
    Impl::removeSpacesAndDashes(uicNumberString, toChar);
  }


}} // namespace Mdt{ namespace UicNumber{

#endif // #ifndef MDT_UIC_NUMBER_ALGORITHM_H
