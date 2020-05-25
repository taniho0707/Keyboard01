/*
 * keyscan.h
 *
 *  Created on: 2020/05/24
 *      Author: taniho0707
 */

#pragma once

#include <stdint.h>

enum KEY_IN {
    KEY_IN_00, KEY_IN_01, KEY_IN_02, KEY_IN_03, KEY_IN_04, KEY_IN_05, KEY_IN_06, KEY_IN_07
};

enum KEY_OUT {
    KEY_OUT_00, KEY_OUT_01, KEY_OUT_02, KEY_OUT_03, KEY_OUT_04, KEY_OUT_05, KEY_OUT_06, KEY_OUT_07, KEY_OUT_08, KEY_OUT_09, KEY_OUT_10, KEY_OUT_11, KEY_OUT_12, KEY_OUT_13, KEY_OUT_14, KEY_OUT_15,
};

enum KEY_STATUS {
    KEY_STATUS_OFF, KEY_STATUS_PUSHED, KEY_STATUS_RELEASED, KEY_STATUS_ON
};

struct keyboardHID_t {
    uint8_t modifiers;
    uint8_t reserved;
    uint8_t key[6];
};

void flushKeyUpdateList();

uint8_t getLengthReport();

struct keyboardHID_t getReport();

void keyUpdate(enum KEY_IN in);

void reportUpdate();
