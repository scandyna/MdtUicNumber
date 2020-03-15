#include <Mdt/UicNumber/UicNumberQt>
#include <QLatin1String>
#include <QString>
#include <QDebug>

int main()
{
  const QString uicNumber = QLatin1String("94 85 7 560 253");
  qDebug() << "Validate " << uicNumber;

  Mdt::UicNumber::validateUicNumberStringFormat_except(uicNumber);

  return 0;
}
