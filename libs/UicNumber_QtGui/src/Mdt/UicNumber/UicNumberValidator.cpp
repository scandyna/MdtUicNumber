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
#include "UicNumberValidator.h"
#include "Mdt/UicNumber/UicNumberQt.h"

namespace Mdt{ namespace UicNumber{

UicNumberValidator::UicNumberValidator(QObject *parent)
 : QValidator(parent)
{
}

QValidator::State UicNumberValidator::validate(QString &input, int &) const
{
  const auto formatValidationState = validateUicNumberStringFormat(input);

  switch( formatValidationState.errorCode() ){
    case StringFormatValidationErrorCode::WrongDigitCount:
      return QValidator::Intermediate;
    case StringFormatValidationErrorCode::UnallowedChar:
      return QValidator::Invalid;
    case StringFormatValidationErrorCode::NoError:
      break;
  }

  return QValidator::Acceptable;
}

}} // namespace Mdt{ namespace UicNumber{
