#include <Mdt/UicNumber/UicNumber>
#include <iostream>

int main()
{
  const auto uicNumber = Mdt::UicNumber::fromString("94 85 7 560 253");

  std::cout << "UIC number: " << Mdt::UicNumber::toString(uicNumber) << std::endl;
}
