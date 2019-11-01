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
 * File:    printLEDs.c
 * 
 * Author:  Axel N. Cincunegui                        <acincunegui@itba.edu.ar>
 *          Gino Minnucci                               <gminnucci@itba.edu.ar>
 *          Martín E. Zahnd                                <mzahnd@itba.edu.ar>
 *
 * Team:    Grupo 3
 * 
 * Created: 21/10/2019, 20:19
 * 
 * General code description:
 *          Visual part of the simulator. Everything that the user can see is
 *  here.
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
#include "term.h"

// ====== Constants and Macros ======
#define PORT                'A'
#define LEDS                8

#define LDON_CHR            '*'
#define LDOFF_CHR           '-'

/*
 * Set simulator colors
 * Possible colors:
 * 
 * BLACK
 * RED
 * GREEN
 * YELLOW
 * BLUE
 * MAGENTA
 * CYAN
 * WHITE
 */
// BG_BLACK - BG_WHITE - BG_PERSONAL
#define BGCOLOR             BG_WHITE


// Color scheme
#define BG_BLACK            0
#define BG_PERSONAL         1
#define BG_WHITE            2

#if BGCOLOR == BG_BLACK
#    define BOARD_COLOR     BLUE
#    define LDON_COLOR      GREEN
#    define LDOFF_COLOR     BLACK
#    define TEXT_COLOR      WHITE

#elif BGCOLOR == BG_PERSONAL
#    define BOARD_COLOR     YELLOW
#    define LDON_COLOR      GREEN
#    define LDOFF_COLOR     RED
#    define TEXT_COLOR      MAGENTA

#elif BGCOLOR == BG_WHITE
#    define BOARD_COLOR     BLUE
#    define LDON_COLOR      GREEN
#    define LDOFF_COLOR     WHITE
#    define TEXT_COLOR      BLACK

#else
#    error "Please define a BGCOLOR"

#endif

enum position
{
    TOP,
    BOTTOM,
    LEFT,
    RIGHT
};
// ====== Prototypes ======
// Prints TOP and Bottom
static void
printTB(uint8_t pos);

// Prints Empty columns
static void
printMID(void);

// ====== Functions ======

// Print instructions

void
printInstructions(void)
{
    puts(TEXT_COLOR "\nPress a LED number (0 - 7) to turn it on.");
    puts(TEXT_COLOR "Press \'t\' to toggle all LEDs status.");
    puts(TEXT_COLOR "Press \'s\' to turn ON all LEDs.");
    puts(TEXT_COLOR "Press \'c\' to turn OFF all LEDs.");
    puts(TEXT_COLOR "Press \'q\' to exit.");
}

// Print all LEDs status

void
printLEDstatus(void)
{
    int16_t i;
    int8_t leds[LEDS];

    for(i = 0; i < LEDS; i++)
    {
        if(bitGet(PORT, i))
        {
            leds[i] = LDON_CHR;
        }

        else
        {
            leds[i] = LDOFF_CHR;
        }
    }

    /*
     *  /===============================\
     *  |   |   |   |   |   |   |   |   |
     *  | x | x | x | x | x | x | x | x |
     *  |   |   |   |   |   |   |   |   |
     *  \===============================/
     */

    // Set board's color
    printf(BOARD_COLOR "");

    // Print TOP
    printTB(TOP);

    // Print empty column
    printMID();

    // Print LEDs status
    for(i = 0; i < LEDS; i++)
    {
        putchar('|');
        putchar(' ');
        if(leds[i] == LDON_CHR)
        {

            printf(LDON_COLOR "%c", leds[i]);
        }

        else
        {
            printf(LDOFF_COLOR "%c", leds[i]);
        }

        // Set board's color
        printf(BOARD_COLOR "");
        putchar(' ');
    }
    putchar('|');
    putchar('\n');

    // Print empty column
    printMID();

    // Print BOTTOM
    printTB(BOTTOM);


}

// Prints TOP and Bottom

static void
printTB(uint8_t pos)
{
    uint16_t i;

    if(pos == TOP)
    {
        putchar('/');
    }

    else
    {
        putchar('\\');
    }

    for(i = 0; i < 4 * LEDS - 1; i++)
    {
        putchar('=');
    }

    if(pos == TOP)
    {
        putchar('\\');
    }

    else
    {
        putchar('/');
    }

    putchar('\n');

}

// Prints Empty columns

static void
printMID(void)
{
    uint16_t i;

    for(i = 0; i < LEDS; i++)
    {
        printf("|   ");
    }
    putchar('|');
    putchar('\n');
}
