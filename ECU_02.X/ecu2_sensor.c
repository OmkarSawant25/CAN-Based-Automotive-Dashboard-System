/*
 * File:   ecu1_sensor.c
 * Author: HP
 *
 * Created on 1 April, 2026, 1:08 PM
 */

#include "ecu2_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"
#include "ssd_display.h"
#include "digital_keypad.h"

uint16_t adc_val;
uint16_t rpm;

char rpm_arr[5];
char digit[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
char ssd[4];
char key;

uint16_t get_rpm() {
    //Implement the rpm function

    adc_val = read_adc(CHANNEL4);
    rpm = (adc_val / 10.23) * 60;

    rpm_arr[0] = (rpm / 1000) + '0';
    rpm_arr[1] = ((rpm / 100) % 10) + '0';
    rpm_arr[2] = ((rpm / 10) % 10) + '0';
    rpm_arr[3] = (rpm % 10) + '0';
    rpm_arr[4] = '\0';

    ssd[0] = digit[rpm / 1000];
    ssd[1] = digit[(rpm / 100) % 10];
    ssd[2] = digit[(rpm / 10) % 10];
    ssd[3] = digit[(rpm % 10)];

    display(ssd);
    return 0;
}

uint16_t get_engine_temp() {
    //Implement the engine temperature function
}

IndicatorStatus process_indicator() {
    //Implement the indicator function

    key = read_digital_keypad(STATE_CHANGE);

    if (key == SWITCH1) {
        PORTBbits.RB0 = 1;
        PORTBbits.RB1 = 1;
        PORTBbits.RB6 = 0;
        PORTBbits.RB7 = 0;
    } else if (key == SWITCH2) {
        PORTBbits.RB0 = 0;
        PORTBbits.RB1 = 0;
        PORTBbits.RB6 = 0;
        PORTBbits.RB7 = 0;
    }
    else if (key == SWITCH3) {
        PORTBbits.RB0 = 0;
        PORTBbits.RB1 = 0;
        PORTBbits.RB6 = 1;
        PORTBbits.RB7 = 1;
    }
}