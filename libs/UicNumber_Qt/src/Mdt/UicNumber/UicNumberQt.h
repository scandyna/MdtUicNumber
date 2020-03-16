/****************************************************************************
 **
 ** MdtUicNumber - A C++ library to work with UIC numbers
 **
 ** Copyright (C) 2020-2020 Philippe Steinmann.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU Lesser General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU Lesser General Public License for more details.
 **
 ** You should have received a copy of the GNU Lesser General Public License
 ** along with this program.  If not, see <https://www.gnu.org/licenses/>.
 **
 ****************************************************************************/
#ifndef MDT_UIC_NUMBER_UIC_NUMBER_QT_H
#define MDT_UIC_NUMBER_UIC_NUMBER_QT_H

#include "AlgorithmQt.h"
#include "StringFormatValidationQt.h"
#include "Mdt/UicNumber/UicNumber.h"
#include <QString>
#include <cassert>

namespace Mdt{ namespace UicNumber{

  /*! \brief Create a UIC number from a string
   *
   * \pre \a uicNumberString must have a valid format
   * \sa fromString()
   * \sa UicNumber
   */
  inline
  UicNumber fromQString(const QString & uicNumberString)
  {
    assert( validateUicNumberStringFormat(uicNumberString) );

    return Impl::fromString(uicNumberString, toCharQt, toIntQt);
  }

  /*! \brief Get a string representation of \a uicNumber
   *
   * \sa toString(const UicNumber &, StringFormatFunc)
   * \sa toQString(const UicNumber &)
   */
  template<typename StringFormatFunc>
  QString toQString(const UicNumber & uicNumber, StringFormatFunc fmt)
  {
    return QString::fromStdString( toString(uicNumber, fmt) );
  }

  /*! \brief Get a string representation of \a uicNumber
   *
   * This overload will choose a format regarding the type code
   *
   * \sa toQString(const UicNumber &, StringFormatFunc)
   */
  inline
  QString toQString(const UicNumber & uicNumber)
  {
    return QString::fromStdString( toString(uicNumber) );
  }

}} // namespace Mdt{ namespace UicNumber{

#endif // #ifndef MDT_UIC_NUMBER_UIC_NUMBER_QT_H
