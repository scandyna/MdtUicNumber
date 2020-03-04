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
// #include <QLatin1Char>
#include <QString>

namespace Mdt{ namespace UicNumber{

  /*! \internal
   */
  inline
  char toCharQt(QChar c) noexcept
  {
    return c.toLatin1();
  }

  /*! \brief Validate the content of a string
   *
   * \sa validateStringContent(const std::string &)
   */
  inline
  bool validateStringContent(const QString & uicNumberString)
  {
    return Impl::validateStringContent(uicNumberString, toCharQt);
  }

  /*! \brief Remove all spaces and hyphen in a string
   *
   * \sa removeSpacesAndHypthen(std::string &)
   */
  inline
  void removeSpacesAndHypthens(QString & uicNumberString)
  {
    Impl::removeSpacesAndHypthens(uicNumberString, toCharQt);
  }

}} // namespace Mdt{ namespace UicNumber{

#endif // #ifndef MDT_UIC_NUMBER_ALGORITHM_QT_H
