#include "ecu1_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"
#include "matrix_keypad.h"
#include "clcd.h"

uint16_t adc_val;
uint16_t speed;

char speed_arr[3];
char gear_arr[3];
char key;
char value;

static char index = 0;

char gear[9][3] = {"ON", "GN", "G1", "G2", "G3", "G4", "G5", "GR", "C "};

uint16_t get_speed() {
    // Implement the speed function
    adc_val = read_adc(CHANNEL4);
    speed = adc_val / 10.23;

    speed_arr[0] = (speed / 10) + '0';
    speed_arr[1] = (speed % 10) + '0';
    speed_arr[2] = '\0';

    clcd_putch((speed / 10) + '0', LINE2(0));
    clcd_putch((speed % 10) + '0', LINE2(1));

    return speed;
}

unsigned char get_gear_pos() {
    // Implement the gear function

    key = scan_switch(); // Scan keypad
    value = triggering_type(EDGE, key); // Apply edge detection

    if (value == KEY_1) {
        if (index < 7) {
            index++;
        }
    } else if (value == KEY_4) {
        if (index > 0) {
            index--;
        }
    } else if (value == KEY_7) {
        index = 8;
    }

    gear_arr[0] = gear[index][0];
    gear_arr[1] = gear[index][1];
    gear_arr[2] = '\0';

    clcd_print(gear[index], LINE2(8));
    return 0;
}