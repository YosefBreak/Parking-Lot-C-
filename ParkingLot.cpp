#include <algorithm>
#include "ParkingLot.h"

namespace MtmParkingLot {

    bool ParkingLot::Already_Parked_Aux(ParkingLotUtils::LicensePlate licensePlate, const MtmParkingLot::NodeP &_insert,
                                        ParkingLotUtils::VehicleType vehicleType) {

        unsigned int index;
        if (_metro.getIndex((_insert), index) == true) {

            ParkingLotPrinter::printVehicle(std::cout, _metro.Getbyid(index)->Getele()->GetVehicleType(), licensePlate,
                                            _metro.Getbyid(index)->Getele()->time);
            ParkingLotPrinter::printEntryFailureAlreadyParked(std::cout, ParkingSpot((MOTORBIKE), index));

            return true;
        } else if (_car.getIndex(_insert, index) == true) {
            ParkingLotPrinter::printVehicle(std::cout, _car.Getbyid(index)->Getele()->GetVehicleType(), licensePlate,
                                            _car.Getbyid(index)->Getele()->time);
            ParkingLotPrinter::printEntryFailureAlreadyParked(std::cout, ParkingSpot(CAR, index));
            return true;

        } else if ((_disable.getIndex(_insert, index))) {

            ParkingLotPrinter::printVehicle(std::cout, _disable.Getbyid(index)->Getele()->GetVehicleType(),
                                            licensePlate,
                                            _disable.Getbyid(index)->Getele()->time);
            ParkingLotPrinter::printEntryFailureAlreadyParked(std::cout,
                                                              ParkingSpot(HANDICAPPED, index));

            return true;
        }

        return false;
    }

    int ParkingLot::Exist_in(const ParkingLotUtils::LicensePlate &ele) const {
        unsigned int index;
        if (_metro.getIndex(NodeP(ele), index)) {
            return 1;
        } else if (_car.getIndex(NodeP(ele), index)) {
            return 2;
        } else if (_disable.getIndex(NodeP(ele), index)) {
            return 3;
        }
        return 0;
    }

    int ParkingLot::Calucator(int vech_type, ParkingLotUtils::Time _start, ParkingLotUtils::Time _end, int _extra) {
        if ((_start - _end).toHours() == 0) {
            return 0;
        }
        int _type = vech_type - 1;
        int _startprice[3] = {10, 20, 15};
        int _addtionalprice[3] = {5, 10, 0};
        int _price = 0;
        Time _wanted = _end - _start;
        int _topay = _wanted.toHours();

        _price = _startprice[_type];
        _topay--;
        int _hour;

        if (5 >= _topay)
            _hour = _topay;
        else
            _hour = 5;

        for (int i = 0; i < _hour; i++) {
            _price = _price + _addtionalprice[_type];
        }
        return (_price + _extra * 250);
    }

    ParkingLot::ParkingLot(unsigned int parkingBlockSizes[]) : _car((parkingBlockSizes[2])),
                                                               _metro(parkingBlockSizes[0]),
                                                               _disable(parkingBlockSizes[1]) {}

    ParkingLot::~ParkingLot() = default;

    ParkingResult ParkingLot::enterParking(ParkingLotUtils::VehicleType vehicleType,
                                           ParkingLotUtils::LicensePlate licensePlate,
                                           ParkingLotUtils::Time entranceTime) {
        unsigned int index;
        NodeP _insert(NodeP(licensePlate, vehicleType, entranceTime));
        if (Already_Parked_Aux(licensePlate, _insert, vehicleType)) {
            return VEHICLE_ALREADY_PARKED;
        } else {
            if (vehicleType == MOTORBIKE) {
                try {
                    index = _metro.insert((_insert));
                }
                catch (UniqueArray<MtmParkingLot::NodeP, MtmParkingLot::NodeP::Compare>::UniqueArrayIsFullException &e) {
                    ParkingLotPrinter::printVehicle(std::cout, vehicleType, licensePlate, entranceTime);
                    ParkingLotPrinter::printEntryFailureNoSpot(std::cout);
                    return NO_EMPTY_SPOT;
                }
                ParkingLotPrinter::printVehicle(std::cout, vehicleType, licensePlate, entranceTime);
                ParkingLotPrinter::printEntrySuccess(std::cout, ParkingSpot(MOTORBIKE, index));
                return SUCCESS;
            } else if (vehicleType == CAR) {
                try {
                    index = _car.insert(_insert);
                }
                catch (UniqueArray<MtmParkingLot::NodeP, MtmParkingLot::NodeP::Compare>::UniqueArrayIsFullException &e) {
                    ParkingLotPrinter::printVehicle(std::cout, vehicleType, licensePlate, entranceTime);
                    ParkingLotPrinter::printEntryFailureNoSpot(std::cout);
                    return NO_EMPTY_SPOT;
                }
                ParkingLotPrinter::printVehicle(std::cout, vehicleType, licensePlate, entranceTime);
                ParkingLotPrinter::printEntrySuccess(std::cout, ParkingSpot(CAR, index));
                return SUCCESS;
            } else {
                try {
                    index = _disable.insert(_insert);
                }
                catch (UniqueArray<MtmParkingLot::NodeP, MtmParkingLot::NodeP::Compare>::UniqueArrayIsFullException &e) {
                    try {
                        index = _car.insert(_insert);
                    }
                    catch (UniqueArray<MtmParkingLot::NodeP, MtmParkingLot::NodeP::Compare>::UniqueArrayIsFullException &e) {
                        ParkingLotPrinter::printVehicle(std::cout, vehicleType, licensePlate, entranceTime);
                        ParkingLotPrinter::printEntryFailureNoSpot(std::cout);
                        return NO_EMPTY_SPOT;
                    }

                    ParkingLotPrinter::printVehicle(std::cout, vehicleType,
                                                    licensePlate, entranceTime);
                    ParkingLotPrinter::printEntrySuccess(std::cout, ParkingSpot(CAR, index));
                    return SUCCESS;
                }
                ParkingLotPrinter::printVehicle(std::cout, vehicleType,
                                                licensePlate, entranceTime);
                ParkingLotPrinter::printEntrySuccess(std::cout, ParkingSpot(HANDICAPPED, index));
                return SUCCESS;
            }
        }
    }

    ParkingResult ParkingLot::exitParking(ParkingLotUtils::LicensePlate licensePlate, ParkingLotUtils::Time exitTime) {

        int result_in = Exist_in(licensePlate);
        unsigned int index;

        if (result_in == 0) {
            ParkingLotPrinter::printExitFailure(std::cout, licensePlate);
            return VEHICLE_NOT_FOUND;

        } else if (result_in == 1) {
            _metro.getIndex(NodeP(licensePlate), index);

            int _price = Calucator(result_in, (_metro[NodeP(licensePlate)])->time, exitTime,
                                   (_metro[NodeP(licensePlate)]->_extra));
            ParkingLotPrinter::printVehicle(std::cout, MOTORBIKE, licensePlate,
                                            (_metro[NodeP(licensePlate)]->time));
            ParkingLotPrinter::printExitSuccess(std::cout, ParkingSpot(MOTORBIKE, index),
                                                exitTime, _price);
            _metro.remove(*(_metro[NodeP(licensePlate)]));

        } else if (result_in == 2) {
            _car.getIndex(NodeP(licensePlate), index);
            int _price;
            if ((_car[NodeP(licensePlate)])->type == CAR) {
                _price = Calucator(2, (_car[NodeP(licensePlate)])->time, exitTime,
                                   (_car[NodeP(licensePlate)]->_extra));
            } else {
                _price = Calucator(3, (_car[NodeP(licensePlate)])->time, exitTime,
                                   (_car[NodeP(licensePlate)]->_extra));
            }
            ParkingLotPrinter::printVehicle(std::cout, _car[NodeP(licensePlate)]->type, licensePlate,
                                            (_car[NodeP(licensePlate)]->time));
            ParkingLotPrinter::printExitSuccess(std::cout, ParkingSpot(CAR, index),
                                                exitTime, _price);
            _car.remove(*(_car[NodeP(licensePlate)]));

        } else if (result_in == 3) {
            _disable.getIndex(NodeP(licensePlate), index);
            int _price = Calucator(result_in, (_disable[NodeP(licensePlate)])->time, exitTime,
                                   (_disable[NodeP(licensePlate)]->_extra));
            ParkingLotPrinter::printVehicle(std::cout, HANDICAPPED, licensePlate,
                                            (_disable[NodeP(licensePlate)]->time));
            ParkingLotPrinter::printExitSuccess(std::cout, ParkingSpot(HANDICAPPED, index),
                                                exitTime, _price);

            _disable.remove(*(_disable[NodeP(licensePlate)]));
        }

        return SUCCESS;
    }

    ParkingResult ParkingLot::getParkingSpot(ParkingLotUtils::LicensePlate licensePlate,
                                             ParkingLotUtils::ParkingSpot &parkingSpot) const {
        int spot = Exist_in(licensePlate);
        unsigned int index;
        if (spot == 0) {
            return VEHICLE_NOT_FOUND;
        } else if (spot == 1) {
            _metro.getIndex(NodeP(licensePlate), index);
            parkingSpot = (ParkingSpot(MOTORBIKE, index));
            return SUCCESS;
        } else if (spot == 2) {
            _car.getIndex(NodeP(licensePlate), index);
            parkingSpot = (ParkingSpot(CAR, index));
            return SUCCESS;
        } else {
            _disable.getIndex(NodeP(licensePlate), index);
            parkingSpot = (ParkingSpot(HANDICAPPED, index));
            return SUCCESS;
        }
    }

    ostream &
    ParkingLot::_PrintAux(ostream &os, const ParkingLot &parkingLot, const ParkingSpot &ele, VehicleType type) {
        int j;
        if (type == MOTORBIKE) {
            j = 0;
        } else if (type == CAR) {
            j = 1;
        } else {
            j = 2;
        }

        UniqueArray<NodeP, NodeP::Compare> aux[3] = {parkingLot._metro, parkingLot._car, parkingLot._disable};
        unsigned int index;

        for (unsigned int i = 0; i < aux[j].getSize(); i++) {
            if (aux[j].Getbyid(i)->GetFlag() == false) {
                aux[j].getIndex(NodeP((aux[j].Getbyid(i))->Getele()->licensePlate), index);
                if (ele.getParkingNumber() == index) {
                    ParkingLotPrinter::printVehicle(os, aux[j].Getbyid(i)->Getele()->type,
                                                    (aux[j].Getbyid(i))->Getele()->licensePlate,
                                                    (aux[j].Getbyid(i))->Getele()->time);
                    ParkingLotPrinter::printParkingSpot(os, ParkingSpot(type, index));
                }
            }
        }
        return os;
    }

    ostream &operator<<(ostream &os, const MtmParkingLot::ParkingLot &parkingLot) {

        unsigned int size[3] = {parkingLot._metro.getSize(), parkingLot._car.getSize(), parkingLot._disable.getSize()};
        std::vector<ParkingSpot> res;
        unsigned int index;
        os << ParkingLotPrinter::printParkingLotTitle;
        for (unsigned int i = 0; i < size[0]; i++) {
            if (parkingLot._metro.Getbyid(i)->GetFlag() == false) {
                parkingLot._metro.getIndex(NodeP(parkingLot._metro.Getbyid(i)->Getele()->GetLicensePlate()), index);
                res.push_back(ParkingSpot(MOTORBIKE, index));
            }
        }
        for (unsigned int i = 0; i < size[2]; i++) {
            if (parkingLot._disable.Getbyid(i)->GetFlag() == false) {
                parkingLot._disable.getIndex(NodeP(parkingLot._disable.Getbyid(i)->Getele()->GetLicensePlate()), index);
                res.push_back(ParkingSpot(HANDICAPPED, index));
            }
        }
        for (unsigned int i = 0; i < size[1]; i++) {
            if (parkingLot._car.Getbyid(i)->GetFlag() == false) {
                parkingLot._car.getIndex(NodeP(parkingLot._car.Getbyid(i)->Getele()->GetLicensePlate()), index);
                res.push_back(ParkingSpot(CAR, index));
            }
        }
        std::sort(res.begin(), res.end());

        for (unsigned int i = 0; i < res.size(); i++) {
            parkingLot._PrintAux(os, parkingLot, res[i], res[i].getParkingBlock());
        }
        return os;
    }

    int ParkingLot::Inspection_Aux(int type, unsigned _pointer, Time _inspec) {
        int counter = 0;
        int hour;
        Time _checking;
        unsigned size[3] = {_metro.getSize(), _car.getSize(), _disable.getSize()};
        UniqueArray<NodeP, NodeP::Compare> arr[3] = {_metro, _car, _disable};
        for (unsigned int i = 0; i < size[_pointer]; i++) {
            if (arr[type].Getbyid(i)->GetFlag() == false) {
                _checking = _inspec - arr[type].Getbyid(i)->Getele()->time;
                hour = _checking.toHours();
                if (hour > 24) {
                    if (type == 0 && this->_metro.Getbyid(i)->Getele()->_extra != 1) {
                        this->_metro.Getbyid(i)->Getele()->_extra = 1;
                        counter++;
                    } else if (type == 1 && this->_car.Getbyid(i)->Getele()->_extra != 1) {
                        this->_car.Getbyid(i)->Getele()->_extra = 1;
                        counter++;
                    } else if (type == 2 && this->_disable.Getbyid(i)->Getele()->_extra != 1) {
                        this->_disable.Getbyid(i)->Getele()->_extra = 1;
                        counter++;
                    }
                }
            }
        }
        return counter;
    }

    void ParkingLot::inspectParkingLot(ParkingLotUtils::Time inspectionTime) {
        int counter = 0;
        counter = Inspection_Aux(0, 0, inspectionTime);
        counter = counter + Inspection_Aux(1, 1, inspectionTime);
        counter = counter + Inspection_Aux(2, 2, inspectionTime);
        ParkingLotPrinter::printInspectionResult(std::cout, inspectionTime, counter);
    }
}