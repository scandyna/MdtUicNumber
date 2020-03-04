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
    void removeSpacesAndHypthens(StringType & uicNumberString, ToChar toChar)
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
   * - A hyphen before the check digit
   */
  inline
  bool validateStringContent(const std::string & uicNumberString)
  {
    return Impl::validateStringContent(uicNumberString, toChar);
  }

  /*! \brief Remove all spaces and hyphen in a string
   *
   * \note This function blindly removes spaces and hyphens,
   *   regardless of the position and count of hyphens.
   * \sa validateStringContent()
   */
  inline
  void removeSpacesAndHypthens(std::string & uicNumberString)
  {
    Impl::removeSpacesAndHypthens(uicNumberString, toChar);
  }

  /*! \brief Validate a UIC number string
   *
   * A valid UIC number contains either 11 digits (check digit missing)
   * or 12 digits.
   * It can optionaly contain a hyphen before the check digit.
   * Spaces are also alowed at arbitrary places.
   *
   * Here are examples of accepted UIC numbers, each digit represented as \a 0 .
   * Note that \a 0 are not accepted for some blocks:
   * \code
   * 00 00 00 00 000
   * 00 00 00 00 000-0
   * 00 00 0000 000
   * 00 00 0000 000-0
   * \endcode
   *
   * \code
   * const std::string uicNumber = "94 85 7 560 253";
   * const auto validationState = Mdt::UicNumber::validateUicNumberString(uicNumber);
   * if( !validationState.isValid() ){
   *   switch( validationState.error() ){
   *      
   *   }
   *   outputError( "Given UIC number is not valid, reason: " + validationState.errorMessage() );
   * }
   * \endcode
   *
   * \code
   * const std::string uicNumber = "94 85 7 560 253";
   * const auto validationState = ;
   * if( !Mdt::UicNumber::validateUicNumberString(uicNumber) ){
   *   outputError("Given UIC number is not valid");
   * }
   * \endcode
   *
   * \tparam StringType A STL compatible string ......
   * \todo Comparator ?
   */
  template<typename StringType>
  bool validateUicNumberString(const StringType & uicNumberString)
  {
  }

}} // namespace Mdt{ namespace UicNumber{

#endif // #ifndef MDT_UIC_NUMBER_ALGORITHM_H
