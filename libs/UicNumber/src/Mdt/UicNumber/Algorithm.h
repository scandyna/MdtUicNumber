/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_UIC_NUMBER_ALGORITHM_H
#define MDT_UIC_NUMBER_ALGORITHM_H

#include <cctype>

namespace Mdt{ namespace UicNumber{

  /*! \brief See how far we can get with tag dispatching
   *
   * See iterator hierarchy
   */
  

  /*! \brief Get the characters that are not allowed for a UIC number in a string
   */
  

  /*! \brief Check if \a c is a digit
   */
  bool isDigit(char c)
  {
    return std::isdigit(static_cast<unsigned char>(c));
  }


  /*! \brief Validate the content of a string
   *
   * A UIC number can only contain:
   * - Digits
   * - Spaces
   * - A hyphen before the check digit
   */
  template<typename StringType>
  bool validateStringContent(const StringType & uicNumberString)
  {
  }

  /*! \brief Remove all spaces and hyphen in a string
   *
   * \note This function blindly removes spaces and hyphens,
   *   regardless of the position and count of hyphens.
   * \sa validateStringContent()
   * \todo std::remove_if , std::is_space ? WWW QString here ! Maybe should be a argument ! IsSpaceFunc
   */
  template<typename StringType>
  void removeSpacesAndHypthen(StringType & uicNumberString)
  {
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
