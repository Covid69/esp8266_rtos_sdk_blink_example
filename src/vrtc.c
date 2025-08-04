#include "vrtc.h"


void vRtcTask(void *pvParameters)
{
    void (*delayFunc)(portTickType) = (void (*)(portTickType))pvParameters;
    while (1) {
        time.centisec += 1;
        if (time.centisec >= 100) {
            time.centisec = 0;
            time.epoch_sec += 1;
        }
        
        delayFunc((portTickType)(10 / portTICK_RATE_MS));
    }
    vTaskDelete(NULL);
}