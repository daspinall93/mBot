#include <src/Functions/ImuMei/ImuMei.h>

ImuMei::ImuMei() :
	onEvent(SWITCH_ON), offEvent(SWITCH_OFF), noEvent(NONE), currentState(offState)
    {
    currentState = offState;

    // Set values of events

    // Initialise the vectors to 0
    acceleration_g_mb.fill(0);
    acceleration_scaledInt_as.fill(0);
    rate_degs_mb.fill(0);
    rate_scaledInt_gs.fill(0);

    }

/* Eexternal command to transition to on state. Will switch on IMU
 * (exit sleep mode) and   */
void ImuMei::switchOn()
    {

    switchImuOn(); // apply initial settings and turn on

    wait_ms(1); // wait for IMU to turn on

    }

/* external command to transition to off state */
void ImuMei::switchOff()
    {
    switchImuOff();
    }

//std::array<float, 3> ImuMei::getAcceleration_g_mb()
//    {
//    return acceleration_g_mb;
//    }
//
//std::array<float, 3> ImuMei::getRate_degs_mb()
//    {
//    return rate_degs_mb;
//    }

//ImuMei::StateId ImuMei::getStateId()
//    {
//    return p_currentState->getStateId();
//    }

void ImuMei::offState(ImuMei &imuMei, Event &event)
    {
    switch (event)
	{
    case NONE:
	break;

    case SWITCH_ON:
	imuMei.switchOn();
	imuMei.changeState(onState);
	break;

    case ENTRY:
	/* Upon exit reset outputs */
	imuMei.acceleration_g_mb.fill(0.0);
	imuMei.rate_degs_mb.fill(0.0);
	break;

    case EXIT:
	break;

    default:
	break;

	}

    }

/* cyclic activities in on state */
void ImuMei::onState(ImuMei & imuMei, Event &event)
    {

    switch (event)
	{
    case NONE:
	imuMei.updateAcceleration_scaledInt_as();
	imuMei.updateRate_scaledInt_gs();
	imuMei.updateAcceleration_g_mb();
	imuMei.updateRate_degs_mb();
	break;

    case SWITCH_OFF:
	imuMei.switchOff();
	imuMei.changeState(offState);
	break;

    case ENTRY:
	/* Upon entry reset outputs */
	imuMei.acceleration_g_mb.fill(0.0);
	imuMei.rate_degs_mb.fill(0.0);
	break;

    case EXIT:
	break;

    default:
	break;

	}

    }

void ImuMei::handleEvent(Event event)
    {
    currentState(*this,event);
    }

//void ImuMei::callback(ImuMei* instance)
//    {
//    instance->update();
//    }

void ImuMei::changeState(State state)
    {
    /* Call the exit action of the current state */
    handleEvent(EXIT);

    /* Change the State */
    currentState = state;

    /* Update the stateId variable */

    /* Call the entry action of the new state */
    handleEvent(ENTRY);
    }

/* Apply initial settings to IMU and then turn on (sleep mode disabled)
 *
 */
void ImuMei::switchImuOn()
    {
// TODO: Check if any other settings are required
    mpu.setClockSource(MPU6050_CLOCK_PLL_XGYRO);
    mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_250);
    mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);
    mpu.setSleepEnabled(false);
    }

void ImuMei::switchImuOff()
    {
    mpu.setSleepEnabled(true);
    }

/* Get latest acceleration measurement from IMU to be converted
 * into g and correct frame later
 */
void ImuMei::updateAcceleration_scaledInt_as()
    {

// update accelerometer sensor measurments
    acceleration_scaledInt_as[0] = mpu.getAccelerationX();
    acceleration_scaledInt_as[1] = mpu.getAccelerationY();
    acceleration_scaledInt_as[2] = mpu.getAccelerationZ();

    }

/* Get latest rate measurement from IMU to be converted
 * into deg/s and correct frame later
 */
void ImuMei::updateRate_scaledInt_gs()
    {

// update rate sensor measurments
    rate_scaledInt_gs[0] = mpu.getRotationX();
    rate_scaledInt_gs[1] = mpu.getRotationY();
    rate_scaledInt_gs[2] = mpu.getRotationZ();

    }

/* Convert scaled int in as frame into g in mb frame for use by
 * localisation functionality
 */
void ImuMei::updateAcceleration_g_mb()
    {

    /* Convert scaledInt values into g values using scaling factor */
    for (size_t i = 0; i < acceleration_scaledInt_as.size(); i++)
	{
	acceleration_g_mb[i] = (float) acceleration_scaledInt_as[i] / LSBPERG;
	}

// TODO: put into correct frame

    }

/* Convert scaled int in gs frame into deg/s in mb frame for use by
 * localisation functionality
 */
void ImuMei::updateRate_degs_mb()
    {

    /* Convert scaledInt values into g values using scaling factor */
    for (size_t i = 0; i < rate_scaledInt_gs.size(); i++)
	{
	rate_degs_mb[i] = (float) rate_scaledInt_gs[i] / LSBPERDEGS;
	}

// TODO: put into correct frame

    }
