#include "header.h"

/******************************************************************************
 * FunctionName : user_rf_cal_sector_set
 * Description  : SDK just reversed 4 sectors, used for rf init data and paramters.
 *                We add this function to force users to set rf cal sector, since
 *                we don't know which sector is free in user's application.
 *                sector map for last several sectors : ABCCC
 *                A : rf cal
 *                B : rf init data
 *                C : sdk parameters
 * Parameters   : none
 * Returns      : rf cal sector
*******************************************************************************/
uint32 user_rf_cal_sector_set(void){
    flash_size_map size_map = system_get_flash_size_map();
    uint32 rf_cal_sec = 0;
    switch (size_map) {
        case FLASH_SIZE_4M_MAP_256_256:
            rf_cal_sec = 128 - 5;
            break;

        case FLASH_SIZE_8M_MAP_512_512:
            rf_cal_sec = 256 - 5;
            break;

        case FLASH_SIZE_16M_MAP_512_512:
        case FLASH_SIZE_16M_MAP_1024_1024:
            rf_cal_sec = 512 - 5;
            break;

        case FLASH_SIZE_32M_MAP_512_512:
        case FLASH_SIZE_32M_MAP_1024_1024:
            rf_cal_sec = 1024 - 5;
            break;

        default:
            rf_cal_sec = 0;
            break;
    }

    return rf_cal_sec;
}

rtc_time_t time;

void task_blink(void* ignore){
    char msg[64];
    while(true) {
        float dis;
        dis = ultrasound_read_distance();
        sprintf(msg, "Distance: %.2f cm\n", dis);
        UartLog(msg);
        vTaskDelay(500/portTICK_RATE_MS);
    }

    vTaskDelete(NULL);
}

/******************************************************************************
 * FunctionName : user_init
 * Description  : entry of user application, init user function here
 * Parameters   : none
 * Returns      : none
*******************************************************************************/
void user_init(void){
    startup_cfg();

    static char logMsg[] = "Hello from UART!";
    xTaskHandle xUartHandle;
    xTaskCreate(&task_blink, "startup", 2048, NULL, 1, NULL);
    // xTaskCreate(&UartLog, "UartLog", 128, logMsg, tskIDLE_PRIORITY, &xUartHandle);
    xTaskCreate(&vRtcTask, "RTC", 128, &vTaskDelay, tskIDLE_PRIORITY + 1, NULL); // Higher priority
}

uint8_t startup_cfg(){
    // Initialize epoch_sec and centisec
    // Set initial time to a specific epoch (e.g., 1754236424 corresponds
    time.epoch_sec = 1754236424; // Set initial epoch seconds
    time.centisec = 0;

    UartLog("Starting ESP8266");
    // Set GPIO2 as output
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2);

    // Initialize ultrasound sensor
    if (ultrasound_init() != 0) {     
        UartLog("Ultrasound initialization failed!\n");
        return 1; // Return error code
    }
    else {
        UartLog("Ultrasound sensor initialized successfully!\n");
    }
}