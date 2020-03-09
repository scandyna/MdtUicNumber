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
#ifndef MDT_UIC_NUMBER_UIC_NUMBER_VALIDATOR_H
#define MDT_UIC_NUMBER_UIC_NUMBER_VALIDATOR_H

#include "mdt_uicnumber_qtgui_export.h"
#include <QValidator>

namespace Mdt{ namespace UicNumber{

  /*! \brief UIC number validator
   *
   * \code
   * uicNumberLineEdit->setValidator( new UicNumberValidator(uicNumberLineEdit) );
   * \endcode
   */
  class MDT_UICNUMBER_QTGUI_EXPORT UicNumberValidator : public QValidator
  {
   Q_OBJECT

   public:

    /*! \brief Constructor
     */
    explicit UicNumberValidator(QObject *parent = nullptr);

    /*! \brief Validate
     */
    State validate(QString &input, int &pos) const override;
  };

}} // namespace Mdt{ namespace UicNumber{

#endif // #ifndef MDT_UIC_NUMBER_UIC_NUMBER_VALIDATOR_H
