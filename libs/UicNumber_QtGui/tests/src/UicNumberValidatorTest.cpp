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
#include "UicNumberValidatorTest.h"
#include "Mdt/UicNumber/UicNumberValidator"
#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QTimer>
#include <QFont>
#include <QFontDatabase>
#include <QDebug>

#include <iostream>

using Mdt::UicNumber::UicNumberValidator;

void showWidgetForever(QWidget &widget)
{
  widget.show();
  while( widget.isVisible() ){
    QTest::qWait(500);
  }
}

void showWidgetAndQuitApp(QWidget &widget)
{
  widget.show();
  QTimer::singleShot(20, &widget, &QWidget::hide);
  QTimer::singleShot(100, qApp, &QApplication::quit);
}

/*
 * Tests
 */

void UicNumberValidatorTest::sandbox()
{
  QLineEdit edit;
  ///edit.setValidator( new UicNumberValidator(&edit) );
  showWidgetAndQuitApp(edit);
}

/*
 * Main
 */

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  QFontDatabase fontDatabase;
  std::cout << "************************************\n";
  std::cout << "application font: " << app.font().toString().toStdString() << "\n";
  std::cout << "************************************" << std::endl;

  qDebug() << "************************************";
  qDebug() << "font families: " << fontDatabase.families();
  qDebug() << "************************************";
  qDebug() << "application font: " << app.font();
  qDebug() << "************************************";

  UicNumberValidatorTest test;

  return QTest::qExec(&test, argc, argv);
}
