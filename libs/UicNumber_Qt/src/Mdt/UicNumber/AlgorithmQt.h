/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_UIC_NUMBER_ALGORITHM_QT_H
#define MDT_UIC_NUMBER_ALGORITHM_QT_H

#include "Mdt/UicNumber/Algorithm.h"
#include <QChar>

namespace Mdt{ namespace UicNumber{


  /*! \brief Check if \a c is a digit
   *
   * \sa isDigit(char)
   */
  bool isDigit(QChar c)
  {
    return isDigit( c.toLatin1() );
  }



}} // namespace Mdt{ namespace UicNumber{

#endif // #ifndef MDT_UIC_NUMBER_ALGORITHM_QT_H
