/*
 * Copyright (C) 2019 Martín E. Zahnd
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * ============================================================================
 * File:    keyboard_input.h
 * 
 * Author:  Axel N. Cincunegui                        <acincunegui@itba.edu.ar>
 *          Gino Minnucci                               <gminnucci@itba.edu.ar>
 *          Martín E. Zahnd                                <mzahnd@itba.edu.ar>
 *
 * Team:    Grupo 3
 * 
 * Created: 21/10/2019, 17:05
 * 
 * General code description:
 *          Asks the user for an input (from the keyboard) and then verifies if
 *  it's valid or not.
 *   In case the input valid, an answer_t variable is modified with the input,
 *  otherwise, the user is asked again for an input.
 * ============================================================================
 */

#ifndef KEYBOARD_INPUT_H
#    define KEYBOARD_INPUT_H
// ====== Constants and Macros ======
// User input by keyboard

typedef struct
{
    /**
     * @brief Answer type
     * 
     * 1: Number
     * 
     * 0: Letter
     */
    uint8_t anstype;

    union
    {
        // @brief Answer is a number
        uint8_t number;

        // @brief Answer is a letter
        uint8_t letter;
    };

} answer_t;

// ====== Prototypes ======
// Asks the user for a keyboard input

/*
 * Input: Pointer to struct with the type of answer and the letter/number 
 * Output: void
 */
uint8_t
kbinput(answer_t* answer);

#endif /* KEYBOARD_INPUT_H */
