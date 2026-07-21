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
    {0x1e, 0x1f, 0x20, 0x21, 0x22},

    {0x23, 0x24, 0x25, 0x26, 0x27},

    {0xF0, 0xF1, 0x69, 0x6a, 0x6b},

    {0xFE, 0x28, 0xFD, 0x68, 0x6c}
};

const uint8_t fnKeymap[ROWS][COLS] =
{
    {0x3a, 0x3b, 0x3c, 0x3d, 0x3e},

    {0x3f, 0x40, 0x41, 0x42, 0x43},

    {0x44, 0x45, 0x69, 0x6a, 0x6b},

    {0xFE, 0x28, 0xFD, 0x68, 0x6c}
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
            HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, GPIO_PIN_RESET);
            break;

        case 1:
            HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, GPIO_PIN_RESET);
            break;

        case 2:
            HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, GPIO_PIN_RESET);
            break;

        case 3:
            HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, GPIO_PIN_RESET);
            break;
    }
}

static uint8_t ReadColumn(void)
{
    if(HAL_GPIO_ReadPin(COL1_GPIO_Port, COL1_Pin) == GPIO_PIN_RESET)
    {
        return 0;
    }

    if(HAL_GPIO_ReadPin(COL2_GPIO_Port, COL2_Pin) == GPIO_PIN_RESET)
    {
        return 1;
    }

    if(HAL_GPIO_ReadPin(COL3_GPIO_Port, COL3_Pin) == GPIO_PIN_RESET)
    {
        return 2;
    }

    if(HAL_GPIO_ReadPin(COL4_GPIO_Port, COL4_Pin) == GPIO_PIN_RESET)
    {
        return 3;
    }

    if(HAL_GPIO_ReadPin(COL5_GPIO_Port, COL5_Pin) == GPIO_PIN_RESET)
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
        return 0x00;
    }

    if(fnPressed)
    {
        return fnKeymap[keyRow][keyCol];
    }

    return keymap[keyRow][keyCol];
}

