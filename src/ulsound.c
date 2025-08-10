#include "ulsound.h"

const int trigPin = 12;
const int echoPin = 14;

uint8_t ultrasound_init() {
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, FUNC_GPIO12);  // trigPin as output
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U, FUNC_GPIO14);  // echoPin as input
    GPIO_DIS_OUTPUT(echoPin); // Set echoPin as input
    GPIO_OUTPUT_SET(trigPin, 0); // Set trigPin low
    return 0;
}

// Returns distance in centimeters
float ultrasound_read_distance() {
    uint32_t start, end, duration;
    // Send 10us pulse to trigger
    GPIO_OUTPUT_SET(trigPin, 0);
    vTaskDelay(2 / portTICK_RATE_MS);
    GPIO_OUTPUT_SET(trigPin, 1);
    os_delay_us(10);
    GPIO_OUTPUT_SET(trigPin, 0);

    // Wait for echoPin to go high
    while (GPIO_INPUT_GET(echoPin) == 0);
    start = system_get_time();

    // Wait for echoPin to go low
    while (GPIO_INPUT_GET(echoPin) == 1);
    end = system_get_time();

    duration = end - start; // microseconds

    // HC-SR04: distance (cm) = duration / 58.0
    return (float)duration / 58.0f;
}