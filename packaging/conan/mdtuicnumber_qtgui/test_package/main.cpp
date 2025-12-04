#include "Mdt/UicNumber/UicNumberValidator"
#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QTimer>

void showWidgetAndQuitApp(QWidget &widget)
{
  widget.show();
  QTimer::singleShot(20, &widget, &QWidget::hide);
  QTimer::singleShot(100, qApp, &QApplication::quit);
}


int main(int argc, char **argv)
{
  using Mdt::UicNumber::UicNumberValidator;

  QApplication app(argc, argv);

  QLineEdit edit;
  edit.setValidator( new UicNumberValidator(&edit) );
  showWidgetAndQuitApp(edit);

  return app.exec();
}
