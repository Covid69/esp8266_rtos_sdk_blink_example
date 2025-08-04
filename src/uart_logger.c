#include "header.h"

void UartLog(char *str){
    // This function logs messages to UART
    if (str != NULL) {
        os_printf("[%d.%02d] LOGGER: %s\n", time.epoch_sec, time.centisec, str);
    } else {
        os_printf("[%d.%02d] LOGGER: (null)\n", time.epoch_sec, time.centisec);
    }
    // vTaskDelete(NULL);
}