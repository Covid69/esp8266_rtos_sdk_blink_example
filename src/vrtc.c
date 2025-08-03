#include "header.h"


void vRtcTask(void *pvParameters)
{
    while (1) {
        time.centisec += 1;
        if (time.centisec >= 100) {
            time.centisec = 0;
            time.epoch_sec += 1;
        }
        vTaskDelay(10 / portTICK_RATE_MS);
    }
    vTaskDelete(NULL);
}