/*
 * matrix.c
 *
 *  Created on: Jun 3, 2026
 *      Author: sudeep
 */
#include "matrix.h"

uint8_t fnPressed = 0;

const uint8_t keymap[ROWS][COLS] =
{
    {KEY_1, KEY_2, KEY_3, KEY_4, KEY_5},

    {KEY_6, KEY_7, KEY_8, KEY_9, KEY_0},

    {KEY_HASH_INTERNAL,KEY_STAR_INTERNAL, KEY_F14, KEY_F15, KEY_F16},

    {KEY_FN, KEY_ENTER, KEY_AUDIO_MUTE,
     KEY_MIC_MUTE, KEY_F17}
};

const uint8_t fnKeymap[ROWS][COLS] =
{
    {KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5},

    {KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10},

    {KEY_F11, KEY_F12, KEY_F14, KEY_F15, KEY_F16},

    {KEY_FN, KEY_ENTER, KEY_AUDIO_MUTE,
     KEY_MIC_MUTE, KEY_F17}
};

static void SelectRow(uint8_t row)
{
    HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, GPIO_PIN_SET);

    switch(row)
    {
        case 0:
            HAL_GPIO_WritePin(
                ROW1_GPIO_Port,
                ROW1_Pin,
                GPIO_PIN_RESET);
            break;

        case 1:
            HAL_GPIO_WritePin(
                ROW2_GPIO_Port,
                ROW2_Pin,
                GPIO_PIN_RESET);
            break;

        case 2:
            HAL_GPIO_WritePin(
                ROW3_GPIO_Port,
                ROW3_Pin,
                GPIO_PIN_RESET);
            break;

        case 3:
            HAL_GPIO_WritePin(
                ROW4_GPIO_Port,
                ROW4_Pin,
                GPIO_PIN_RESET);
            break;
    }
}

static uint8_t ReadColumn(void)
{
    if(HAL_GPIO_ReadPin(
        COL1_GPIO_Port,
        COL1_Pin) == GPIO_PIN_RESET)
    {
        return 0;
    }

    if(HAL_GPIO_ReadPin(
        COL2_GPIO_Port,
        COL2_Pin) == GPIO_PIN_RESET)
    {
        return 1;
    }

    if(HAL_GPIO_ReadPin(
        COL3_GPIO_Port,
        COL3_Pin) == GPIO_PIN_RESET)
    {
        return 2;
    }

    if(HAL_GPIO_ReadPin(
        COL4_GPIO_Port,
        COL4_Pin) == GPIO_PIN_RESET)
    {
        return 3;
    }

    if(HAL_GPIO_ReadPin(
        COL5_GPIO_Port,
        COL5_Pin) == GPIO_PIN_RESET)
    {
        return 4;
    }

    return 255;
}

uint8_t Matrix_Scan(void)
{
    uint8_t keyRow = 255;
    uint8_t keyCol = 255;

    fnPressed = 0;

    for(uint8_t row = 0; row < ROWS; row++)
    {
        SelectRow(row);

        for(volatile int i = 0; i < 200; i++);

        uint8_t col = ReadColumn();

        if(col != 255)
        {
            /*
             * FN key position
             * R4C1
             */
            if(row == 3 && col == 0)
            {
                fnPressed = 1;
            }
            else
            {
                keyRow = row;
                keyCol = col;
            }
        }
    }

    if(keyRow == 255)
    {
        return KEY_NONE;
    }

    if(fnPressed)
    {
        return fnKeymap[keyRow][keyCol];
    }

    return keymap[keyRow][keyCol];
}

