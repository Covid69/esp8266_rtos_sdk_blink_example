#include "esp_common.h"
#include "freertos/task.h"
#include "gpio.h"
#include "vrtc.h"
#include "ulsound.h"

//VARIABLE

// PROTOTYPE
// Function to initialize the startup configuration
uint8_t startup_cfg();
// Function to log messages to UART
void UartLog(char *str);