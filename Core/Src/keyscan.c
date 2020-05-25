/*
 * keyscan.c
 *
 *  Created on: 2020/05/24
 *      Author: taniho0707
 */

#include "keyscan.h"
#include "keymap.h"

#include "stm32f0xx_hal.h"
#include "main.h"

// Bit 0(LSB): Current Key Status(1=Push, 0=Release)
// Bit 1     : Last Key Status(1=Push, 0=Release)
// Bit 2-7   : Do not care
static uint8_t key_data[8][16] = { 0 };

static struct keyboardHID_t keyboard_report_last;
static struct keyboardHID_t keyboard_report_current;

static uint8_t keyboard_update_list[256] = { 0 };

struct keyboardHID_t keyboard_report[10];
uint8_t length_report = 0;

void flushKeyUpdateList() {
    for (int i = 0; i < 256; ++i) {
        keyboard_update_list[i] = 0;
    }
}

uint8_t getLengthReport() {
    return length_report;
}

struct keyboardHID_t getReport() {
    if (length_report == 0) {
        struct keyboardHID_t ret = { 0, 0, { 0 } };
        return ret;
    } else {
        --length_report;
        return keyboard_report[length_report];
    }
}

void keyUpdate(enum KEY_IN in) {
    for (int i = 0; i < 16; ++i) {
        key_data[in][i] <<= 1;
        key_data[in][i] &= 0x03;
    }

    static GPIO_InitTypeDef GPIO_InitStruct = { 0 };
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

    switch (in) {
    case KEY_OUT_00:
        GPIO_InitStruct.Pin = OUT_00_Pin;
        break;
    case KEY_OUT_01:
        GPIO_InitStruct.Pin = OUT_01_Pin;
        break;
    case KEY_OUT_02:
        GPIO_InitStruct.Pin = OUT_02_Pin;
        break;
    case KEY_OUT_03:
        GPIO_InitStruct.Pin = OUT_03_Pin;
        break;
    case KEY_OUT_04:
        GPIO_InitStruct.Pin = OUT_04_Pin;
        break;
    case KEY_OUT_05:
        GPIO_InitStruct.Pin = OUT_05_Pin;
        break;
    case KEY_OUT_06:
        GPIO_InitStruct.Pin = OUT_06_Pin;
        break;
    case KEY_OUT_07:
        GPIO_InitStruct.Pin = OUT_07_Pin;
        break;
    default:
        return;
    }

    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    HAL_GPIO_WritePin(GPIOC, GPIO_InitStruct.Pin, GPIO_PIN_SET);

    key_data[in][0] |= HAL_GPIO_ReadPin(GPIOB, IN_00_Pin);
    key_data[in][1] |= HAL_GPIO_ReadPin(GPIOB, IN_01_Pin);
    key_data[in][2] |= HAL_GPIO_ReadPin(GPIOB, IN_02_Pin);
    key_data[in][3] |= HAL_GPIO_ReadPin(GPIOB, IN_03_Pin);
    key_data[in][4] |= HAL_GPIO_ReadPin(GPIOB, IN_04_Pin);
    key_data[in][5] |= HAL_GPIO_ReadPin(GPIOB, IN_05_Pin);
    key_data[in][6] |= HAL_GPIO_ReadPin(GPIOB, IN_06_Pin);
    key_data[in][7] |= HAL_GPIO_ReadPin(GPIOB, IN_07_Pin);
    key_data[in][8] |= HAL_GPIO_ReadPin(GPIOB, IN_08_Pin);
    key_data[in][9] |= HAL_GPIO_ReadPin(GPIOB, IN_09_Pin);
    key_data[in][10] |= HAL_GPIO_ReadPin(GPIOB, IN_10_Pin);
    key_data[in][11] |= HAL_GPIO_ReadPin(GPIOB, IN_11_Pin);
    key_data[in][12] |= HAL_GPIO_ReadPin(GPIOB, IN_12_Pin);
    key_data[in][13] |= HAL_GPIO_ReadPin(GPIOB, IN_13_Pin);
    key_data[in][14] |= HAL_GPIO_ReadPin(GPIOB, IN_14_Pin);
    key_data[in][15] |= HAL_GPIO_ReadPin(GPIOB, IN_15_Pin);

    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    for (int i = 0; i < 16; ++i) {
        if (key_data[in][i] == KEY_STATUS_PUSHED || key_data[in][i] == KEY_STATUS_RELEASED) {
            keyboard_update_list[keycode_table[0][in][i]] = key_data[in][i];
        }
    }
}

void reportUpdate() {
    uint8_t change_flag = 0;
    keyboard_report_last = keyboard_report_current;

    for (int i = 0; i < 256; ++i) {
        if (keyboard_update_list[i] == KEY_STATUS_RELEASED) {
            if (i == KEY_LEFTCTRL) {
                keyboard_report_current.modifiers &= (~KEY_MOD_LCTRL);
            } else if (i == KEY_RIGHTCTRL) {
                keyboard_report_current.modifiers &= (~KEY_MOD_RCTRL);
            } else if (i == KEY_LEFTALT) {
                keyboard_report_current.modifiers &= (~KEY_MOD_LALT);
            } else if (i == KEY_RIGHTALT) {
                keyboard_report_current.modifiers &= (~KEY_MOD_RALT);
            } else if (i == KEY_LEFTSHIFT) {
                keyboard_report_current.modifiers &= (~KEY_MOD_LSHIFT);
            } else if (i == KEY_RIGHTSHIFT) {
                keyboard_report_current.modifiers &= (~KEY_MOD_RSHIFT);
            } else if (i == KEY_LEFTMETA) {
                keyboard_report_current.modifiers &= (~KEY_MOD_LMETA);
            } else if (i == KEY_RIGHTMETA) {
                keyboard_report_current.modifiers &= (~KEY_MOD_RMETA);
            }
            for (int j = 0; j < 6; ++j) {
                if (keyboard_report_current.key[j] == i) {
                    keyboard_report_current.key[j] = KEY_NONE;
                    change_flag = 1;
                }
            }
        }
    }
    for (int i = 0; i < 256; ++i) {
        if (keyboard_update_list[i] == KEY_STATUS_PUSHED) {
            if (i == KEY_LEFTCTRL) {
                keyboard_report_current.modifiers |= KEY_MOD_LCTRL;
            } else if (i == KEY_RIGHTCTRL) {
                keyboard_report_current.modifiers |= KEY_MOD_RCTRL;
            } else if (i == KEY_LEFTALT) {
                keyboard_report_current.modifiers |= KEY_MOD_LALT;
            } else if (i == KEY_RIGHTALT) {
                keyboard_report_current.modifiers |= KEY_MOD_RALT;
            } else if (i == KEY_LEFTSHIFT) {
                keyboard_report_current.modifiers |= KEY_MOD_LSHIFT;
            } else if (i == KEY_RIGHTSHIFT) {
                keyboard_report_current.modifiers |= KEY_MOD_RSHIFT;
            } else if (i == KEY_LEFTMETA) {
                keyboard_report_current.modifiers |= KEY_MOD_LMETA;
            } else if (i == KEY_RIGHTMETA) {
                keyboard_report_current.modifiers |= KEY_MOD_RMETA;
            }
            for (int j = 0; j < 6; ++j) {
                if (keyboard_report_current.key[j] == KEY_NONE) {
                    keyboard_report_current.key[j] = i;
                    change_flag = 1;
                    break;
                }
            }
        }
    }

    if (change_flag) {
        keyboard_report[length_report] = keyboard_report_current;
        ++length_report;
    }
}
