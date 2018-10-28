#include "mbed.h"
#include "src/Functions/ImuMei/ImuMei.h"

int main() {
    ImuMei imuMei;
    imuMei.handleEvent(imuMei.noEvent);
    imuMei.handleEvent(imuMei.onEvent);
    imuMei.handleEvent(imuMei.offEvent);
}

