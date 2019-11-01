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
 * File:    keyboard_input.c
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

// ====== Libreries ======
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* 
 * Linux support for keyboard functions for getch and getche and kbhit ansy.sys 
 * Like functions added
 */
#include "../libs/termlib.h"

// Library used to manage the microcontroller ports
#include "../libs/PortEmul/PortEmul.h"

// Fake Library (For test only)
//#include "fake_library.h"

// This file
#include "term_keyboard_input.h"

// ====== Constants and Macros ======
#define PORT        'A'
#define LEDS        8

// UPPER To lower
#define TOLOWER(c) (((c) >= 'A' && (c) <= 'Z') ? (c)-'A'+'a':(c))

// Input status

enum status
{
    BAD,
    OK,
    FALSE = 0,
    TRUE
};

// ====== Prototypes ======
// Verify if user input is valid and, if so, write it to the struct

static int
verifyInput(answer_t *answer, uint8_t *inptChar);

// Given a correct keyboard input, do something

static void
runKBInput(answer_t *usrinput);

// ====== Functions ======

// Asks the user for a keyboard input

/*
 * Input: Pointer to struct with the type of answer and the letter/number 
 * Output: void
 */
uint8_t
kbinput(answer_t* answer)
{
    /*
     * 
     */

    // Array with characters entered by user; status of the user input
    uint8_t key, inputstatus = BAD;
    static uint8_t errMsg = FALSE;

    key = getch();

    // User entered something
    if(key != '\n')
    {
        // Verify if user input is valid
        inputstatus = verifyInput(answer, &key);
    }

    else
    {
        inputstatus = BAD;
    }

    // User entered nothing
    if((key == '\n' || inputstatus == BAD) && !errMsg)
    {
#ifndef TEST
        puts("\nError. Please check your input.\n");
        errMsg = TRUE;
#endif

    }

#ifdef DEBUG
    printf("input: %d \n", inputstatus);

    printf("answer -> anstype: %d \n", answer-> anstype);

    if(answer->anstype == 1)
    {
        printf("answer -> number: %d\n", answer -> number);
    }

    else
    {
        printf("answer -> letter: %d\n", answer -> letter);
    }
#endif

    if(inputstatus == OK)
    {
        runKBInput(answer);
        errMsg = FALSE;
    }

    return inputstatus;
}

// Verify if user input is valid and, if so, write it to the struct

static int
verifyInput(answer_t *answer, uint8_t *inptChar)
{
    int inputstatus = BAD;

    // A number was entered
    if(*inptChar >= '0' && *inptChar <= '7')
    {
        inputstatus = OK;
        answer -> anstype = 1;
        answer -> number = *inptChar - 48;
    }

        // A letter
    else
    {
        switch(*inptChar)
        {
            case 'C':
            case 'c':
            case 'Q':
            case 'q':
            case 'S':
            case 's':
            case 'T':
            case 't':
                inputstatus = OK;
                answer -> anstype = 0;
                answer -> letter = TOLOWER(*inptChar);
                break;

            default:
                inputstatus = BAD;
                break;
        }
    }

    return inputstatus;
}

// Given a correct keyboard input, do something

static void
runKBInput(answer_t *usrinput)
{
    // Numbers
    if(usrinput -> anstype == 1)
    {
        bitSet(PORT, usrinput -> number);
    }

        // Letters
    else if(usrinput -> anstype == 0)
    {
        switch(TOLOWER(usrinput -> letter))
        {
                // Clear all LEDs
            case 'c':
                maskOff(PORT, 0xFF);
                break;

                // Set all LEDs
            case 's':
                maskOn(PORT, 0xFF);
                break;

                // Togle LEDs
            case 't':
                maskToggle(PORT, 0xFF);
                break;

                // Quit
            case 'q':
                break;

            default:
                break;
        }
    }
}
