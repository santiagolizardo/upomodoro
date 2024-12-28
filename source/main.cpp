#include "MicroBit.h"

#include "TickImageData.h"
#include "PomodoroApp.h"

MicroBitImage tickImage((ImageData *)TICK_IMAGE_DATA);
/*
MicroBitImage tickImage(
        "0,0,0,0,0\n"
        "0,0,0,0,1\n"
        "0,0,0,1,0\n"
        "1,0,1,0,0\n"
        "0,1,0,0,0\n"
);
*/

MicroBit uBit;

PomodoroApp app;

int main()
{
    uBit.init();
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_AB, MICROBIT_BUTTON_EVT_CLICK, onQuit);
    uBit.messageBus.listen(MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_TILT_UP, onTiltUp);
    uBit.messageBus.listen(MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_SHAKE, onShake);

    pomodoroMainLoop();

    uBit.display.print(tickImage);
    uBit.sleep(ONE_SECOND * 3);
    uBit.display.clear();

    release_fiber();
    return EXIT_SUCCESS;
}
