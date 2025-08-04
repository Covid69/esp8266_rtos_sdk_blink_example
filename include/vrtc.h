#include "esp_common.h"

typedef struct {
    uint32_t epoch_sec;    // seconds since Jan 1, 1970
    uint16_t centisec;     // hundredths of a second (0-99)
} rtc_time_t;


//VARIABLE
extern rtc_time_t time;

// PROTOTYPE
void vRtcTask(void *pvParameters);