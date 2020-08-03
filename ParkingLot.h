#ifndef MTMPARKINGLOT_PARKINGLOT_H
#define MTMPARKINGLOT_PARKINGLOT_H


#include "ParkingLotTypes.h"
#include "Time.h"
#include "ParkingSpot.h"
#include "UniqueArray.h"
#include "ParkingLotPrinter.h"
#include <vector>


namespace MtmParkingLot {

    using namespace ParkingLotUtils;
    using std::ostream;

    /*                          *  ~~ ParkingLot.H Declaration &     initialization  Class ~~                        */


    /*
     * NodeP Class implement & initialization.
     * NodeP Class  was utilized to implement ParkingLot Class.
     * NodeP Class was decleared as a friend with ParkingLot Class.
     */
    class NodeP {
        /*
        * licensePlate - licensePlate id.
        * time - entrance time.
        * _extra - 1 if the care parked more than 24 hours else default = 0.
        * type - VehicleType type.
        */
    private:
        LicensePlate licensePlate;
        VehicleType type;
        Time time;
        int _extra;

    public:
        /* NodeP Class include two types of Constructors & an copy Constructor
        * 1- a defaulted constructor which implemented as ()
        * 2- Constructor which absorb an licensePlate as input.
        * 3- Copy Constructor.
        */
        NodeP() = default;

        NodeP(LicensePlate len, VehicleType type, Time time) : licensePlate(len), type(type), time(time), _extra(0) {};

        NodeP(const NodeP &ele) : licensePlate(ele.licensePlate), type(ele.type), time(ele.time), _extra(ele._extra) {};

        NodeP(const LicensePlate &ele) : licensePlate(ele), _extra(0) {};

        /* Distractor - calling the  default Distractor */
        ~NodeP() = default;

        /* Compare - a required class to compare between two NodeP elements
         * two NodeP are the same if they have the same licensePlate
         */
        class Compare {
        public:
            bool operator()(NodeP a, NodeP b) {
                return a.licensePlate == b.licensePlate;
            }
        };

        LicensePlate GetLicensePlate() const {
            return this->licensePlate;
        }

        VehicleType GetVehicleType() const {
            return this->type;
        }


        friend class ParkingLot;
    };


    class ParkingLot {
        /* _car - an UniqueArray array that include all cars at our Parkinglot.
         * _metro - an UniqueArray array that include all metros at our Parkinglot.
         * _disabled - an UniqueArray array that include all diabled_cars at our Parkinglot.
         */
    private:
        UniqueArray<NodeP, NodeP::Compare> _car;
        UniqueArray<NodeP, NodeP::Compare> _metro;
        UniqueArray<NodeP, NodeP::Compare> _disable;


    public:
        ParkingLot() = default;

        ParkingLot(unsigned int parkingBlockSizes[]);

        ~ParkingLot();

        ParkingResult enterParking(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime);

        ParkingResult exitParking(LicensePlate licensePlate, Time exitTime);

        ParkingResult getParkingSpot(LicensePlate licensePlate, ParkingSpot &parkingSpot) const;

        void inspectParkingLot(Time inspectionTime);

        friend ostream &operator<<(ostream &os, const ParkingLot &parkingLot);

        /* helping function session*/

        /* The function check if the car/metro Exist at our park
         * return : 0- Not found, 1- Found at metro , 2- Found at Cars , 3- disabled.
         */
        int Exist_in(const LicensePlate &ele) const;

        /* The function return the value which the customer have to pay .
        * The main reason of wrting the following function is to take off code duplication
        */
        int Calucator(int vech_type, Time _start, Time _end, int _extra);

        /*
         * The Function was build as a helper to operator << function
         * The function take off all the duplication code and make the code more clearly
         * input : all requested argmunents to make a print
         */
        static ostream &_PrintAux(ostream &os, const ParkingLot &parkingLot, const ParkingSpot &ele, VehicleType type);

        /*
         * The Function was build as a helper to inspection function
         * The function take off all the duplication code and make the code more clearly
         * The function raise a flag in cars who parked over 24Hour
         */
        int Inspection_Aux(int type, unsigned _pointer, Time _inspec);

        /*
         * The function check if the care already parked and print fit msg
         * return values
         * true - if the care already parked
         * false - other ;
         */

        bool Already_Parked_Aux(LicensePlate licensePlate, const NodeP &_insert, VehicleType vehicleType);
    };
}

#endif //MTMPARKINGLOT_PARKINGLOT_H
