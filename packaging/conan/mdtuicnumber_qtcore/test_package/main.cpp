#include <Mdt/UicNumber/UicNumberQt>
#include <QLatin1String>
#include <QString>
#include <QDebug>

int main()
{
  const auto uicNumber = Mdt::UicNumber::fromQString( QLatin1String("94 85 7 560 253") );

  qDebug() << "UIC number: " << Mdt::UicNumber::toQString(uicNumber);
}
