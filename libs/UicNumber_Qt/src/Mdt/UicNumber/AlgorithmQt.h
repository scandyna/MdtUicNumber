/****************************************************************************
 **
 ** MdtUicNumber - A C++ library to work with UIC numbers
 **
 ** Copyright (C) 2020-2025 Philippe Steinmann.
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
#ifndef MDT_UIC_NUMBER_ALGORITHM_QT_H
#define MDT_UIC_NUMBER_ALGORITHM_QT_H

#include "Mdt/UicNumber/Algorithm.h"
#include <QChar>
#include <QString>
#include <QStringView>
#include <cassert>

namespace Mdt{ namespace UicNumber{

  /*! \internal
   */
  inline
  char toCharQt(QChar c) noexcept
  {
    return c.toLatin1();
  }

  /*! \internal
   */
  inline
  int toIntQt(const QString & str, int position, int length)
  {
    assert(position >= 0);
    assert(length >= 0);
    assert( (position+length) <= str.length() );

    QStringView sv(str);

    return sv.sliced(position, length).toInt();
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
   * \sa removeSpacesAndDashes(std::string &)
   */
  inline
  void removeSpacesAndDashes(QString & uicNumberString)
  {
    Impl::removeSpacesAndDashes(uicNumberString, toCharQt);
  }


}} // namespace Mdt{ namespace UicNumber{

#endif // #ifndef MDT_UIC_NUMBER_ALGORITHM_QT_H
