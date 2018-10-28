#ifndef INTERFACING_IMUMEI_H_

#define INTERFACING_IMUMEI_H_

#include "mbed.h"
#include <src/Functions/ImuMei/MPU6050/MPU6050.h>
#include <src/Functions/ImuMei/ImuMei_constantDefs.h>
#include <vector>
#include <array>



class ImuMei
    {
public:

    typedef int Event;
    typedef void (*State)(ImuMei&, Event&);

    /* STATE ID */
    enum
	{
	INIT = 0,
	OFF,
	ON
	} StateId;

    /* EVENT ID */
    enum
	{
	ENTRY = -2,
	EXIT = -1,
	NONE = 0,
	SWITCH_ON,
	SWITCH_OFF
	} EventId;

    /* CONSTRUCTOR */
    ImuMei();

    /* CALLBACK */
//    static void callback(ImuMei*);

    /* PUBLIC UPDATE*/
    void handleEvent(Event event);

    /* Event Objects */
    Event noEvent;
    Event onEvent;
    Event offEvent;

    /* PUBLIC OUTPUT */
    array<int,3> acceleration_scaledInt_as;
    array<int, 3> rate_scaledInt_gs;

//    StateId getStateId();

private:

    /* STATE FUNCTIONS */
    static void offState(ImuMei &imu, Event &event);
    static void onState(ImuMei &imu, Event &event);

    /* POINTER TO CURRENT STATE FUNCTION */
    State currentState;

    /* STATE MANAGEMENT */
    void changeState(State newState);

    /* STATE TRANSITION FUNCTIONS */
    void switchOn();
    void switchOff();

    /* DEPENDENCIES */
    MPU6050 mpu;

    /* IMU MANAGEMENT */
    void switchImuOn();
    void switchImuOff();

    /* DATA MANAGEMENT */
    array<float, 3> acceleration_g_mb;
    array<float, 3> rate_degs_mb;

    /* ALGORITHMS */
    void updateAcceleration_scaledInt_as();
    void updateRate_scaledInt_gs();

    void updateAcceleration_g_mb();
    void updateRate_degs_mb();


    };

#endif /* INTERFACING_ACCELMEI_H_ */
