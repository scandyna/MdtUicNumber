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
#ifndef MDT_UIC_NUMBER_STRING_FORMAT_VALIDATION_QT_H
#define MDT_UIC_NUMBER_STRING_FORMAT_VALIDATION_QT_H

#include "AlgorithmQt"
#include "Mdt/UicNumber/StringFormatValidation.h"
#include <QString>

namespace Mdt{ namespace UicNumber{

  /*! \brief Validate a UIC number string
   *
   * \sa validateUicNumberStringFormat(const std::string &)
   * \sa UicNumber
   */
  inline
  StringFormatValidationState validateUicNumberStringFormat(const QString & uicNumberString)
  {
    return Impl::validateUicNumberStringFormat(uicNumberString, toCharQt);
  }

  /*! \brief Validate a UIC number string
   *
   * \sa validateUicNumberStringFormat_except(const std::string &)
   * \sa UicNumber
   */
  inline
  void validateUicNumberStringFormat_except(const QString & uicNumberString)
  {
    Impl::validateUicNumberStringFormat_except(uicNumberString, toCharQt);
  }

}} // namespace Mdt{ namespace UicNumber{

#endif // #ifndef MDT_UIC_NUMBER_STRING_FORMAT_VALIDATION_QT_H

