/*
 * matrix.h
 *
 *  Created on: Jun 3, 2026
 *      Author: sudee
 */

#ifndef INC_MATRIX_H_
#define INC_MATRIX_H_

#include "main.h"
#include "hid_keycodes.h"

#define ROWS 4
#define COLS 5

extern uint8_t fnPressed;

uint8_t Matrix_Scan(void);


#endif /* INC_MATRIX_H_ */
