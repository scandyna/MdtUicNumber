/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_UIC_NUMBER_UIC_NUMBER_H
#define MDT_UIC_NUMBER_UIC_NUMBER_H

namespace Mdt{ namespace UicNumber{

  /*! \brief Represents a 12 digit UIC number
   *
   * A UIC number 3 main blocks:
   * - The international block, digits 1-4
   * - The national block, digits 5-11
   * - A check digit, digit 12
   *
   * The international block is composed of a type code and a country code.
   * The UIC number can finaly be representad by 4 blocks:
   * - The type code, digits 1-2
   * - The country code, digits 3-4
   * - The national block, digits 5-11
   * - A check digit, digit 12
   *
   * \sa https://en.wikipedia.org/wiki/UIC_identification_marking_for_tractive_stock
   * \todo See if the class has to be a template, think not (can have function templates for StringType)
   */
  class UicNumber
  {
   public:

    /*! \brief Validate a UIC number string
     *
     * \tparam StringType A STL compatible string ......
     * \todo Comparator ?
     * \todo Mybe in algorithm..
     */
    template<typename StringType>
    static
    bool validate(const StringType & uicNumberString)
    {
    }

   private:

    
  };

}} // namespace Mdt{ namespace UicNumber{

#endif // #ifndef MDT_UIC_NUMBER_UIC_NUMBER_H
