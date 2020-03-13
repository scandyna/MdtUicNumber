/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_UIC_NUMBER_TYPE_CODE_H
#define MDT_UIC_NUMBER_TYPE_CODE_H

#include <cstdint>

namespace Mdt{ namespace UicNumber{

  /*! \brief UIC number type code
   *
   * \sa typeCodeFromInt()
   * \sa https://en.wikipedia.org/wiki/UIC_identification_marking_for_tractive_stock
   * \sa https://en.wikipedia.org/wiki/UIC_wagon_numbers
   * \sa http://www.dansk-jernbanearkiv.dk/uic438/u438.htm
   * \sa http://www.railfaneurope.net/misc/uicnum.html
   */
  enum class TypeCode : int8_t
  {
    Unknown = 0,                                /*!< 00: unknown type code */
    FreightWagonOneGaugeEurOwnRail = 01,        /*!< 01: Non bogie freight wagons for one gauge, EUROP-pool, owned by railway */
    FreightWagonBogieOneGaugeEurOwnRail = 11,   /*!< 11: Bogie freight wagons for one gauge, EUROP-pool, owned by railway */
    PassengerWagonDomesticUse = 50,             /*!< 50: Passenger wagons for domestic use only */
    PassengerWagonRicPpwOneGauge = 51,          /*!< 51: RIC/PPW-traffic. Passenger wagons for one gauge only. Non air-coditioned.
                                                         (Inclusive RIC-wagons for automobile transport) */
    PassengerWagonRicPpwGauges_1435_1524 = 52,  /*!< 52: RIC/PPW-traffic. Passenger wagons for two gauges (1435/1524). Non air-conditioned.  */
    PassengerWagonRicPpwGauges_1435_1672 = 54,  /*!< 54: RIC/PPW-traffic. Passenger wagons for two gauges (1435/1672). Non air-conditioned. */
    MiscellaneousTractiveUnit = 90,             /*!< 90: Miscellaneous (tractive unit not otherwise classified, e.g. steam locomotive) */
    ElectricLocomotive = 91,                    /*!< 91: Electric locomotive */
    DieselLocomotive = 92,                      /*!< 92: Diesel locomotive */
    HighSpeedElectricMultipleUnit = 93,         /*!< 93: Electric multiple unit (high speed) [power car or trailer] */
    ElectricMultipleUnit = 94,                  /*!< 94: Electric multiple unit (not high speed) [power car or trailer] */
    DieselMultipleUnit = 95,                    /*!< 95: Diesel multiple unit [power car or trailer] */
    SpecialisedTrailer  = 96,                   /*!< 96: Specialised trailer */
    ElectricShunter = 97,                       /*!< 97: Electric shunter */
    DieselShunter = 98,                         /*!< 98: Diesel shunter */
    SpecialTractiveVehicle = 99                 /*!< 99: Special vehicle (e.g. Departmental tractive unit) */
  };

  /*! \brief Get a type code from a int
   */
  inline
  constexpr TypeCode typeCodeFromInt(int8_t v) noexcept
  {
    switch(v){
      case 01:
        return TypeCode::FreightWagonOneGaugeEurOwnRail;
      case 11:
        return TypeCode::FreightWagonBogieOneGaugeEurOwnRail;
      case 50:
        return TypeCode::PassengerWagonDomesticUse;
      case 51:
        return TypeCode::PassengerWagonRicPpwOneGauge;
      case 52:
        return TypeCode::PassengerWagonRicPpwGauges_1435_1524;
      case 54:
        return TypeCode::PassengerWagonRicPpwGauges_1435_1672;
      case 90:
        return TypeCode::MiscellaneousTractiveUnit;
      case 91:
        return TypeCode::ElectricLocomotive;
      case 92:
        return TypeCode::DieselLocomotive;
      case 93:
        return TypeCode::HighSpeedElectricMultipleUnit;
      case 94:
        return TypeCode::ElectricMultipleUnit;
      case 95:
        return TypeCode::DieselMultipleUnit;
      case 96:
        return TypeCode::SpecialisedTrailer;
      case 97:
        return TypeCode::ElectricShunter;
      case 98:
        return TypeCode::DieselShunter;
      case 99:
        return TypeCode::SpecialTractiveVehicle;
    }
    return TypeCode::Unknown;
  }

}} // namespace Mdt{ namespace UicNumber{

#endif // #ifndef MDT_UIC_NUMBER_TYPE_CODE_H
