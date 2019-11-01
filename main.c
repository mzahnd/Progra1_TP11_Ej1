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
 * File:    main.c
 * 
 * Author:  Axel N. Cincunegui                        <acincunegui@itba.edu.ar>
 *          Gino Minnucci                               <gminnucci@itba.edu.ar>
 *          Martín E. Zahnd                                <mzahnd@itba.edu.ar>
 *
 * Team:    Grupo 3
 * 
 * Created: 29/10/2019, 17:56
 * 
 * General code description:
 *          
 * ============================================================================
 */

// ====== Libreries ======
#include <stdio.h>
#include <stdint.h>
// Allegro
#include <allegro5/allegro5.h>

// Verify CLI arguments
#include "args/arguments.h"

/* 
 * Linux support for keyboard functions for getch and getche and kbhit ansy.sys 
 * Like functions added
 */
#include "libs/termlib.h"

// Ask the user for a keyboard input in terminal mode
#include "keyboard/term_keyboard_input.h"

// Print LEDs status
#include "frontend/frontend.h"

// Terminal mode
#include "frontend/term.h"

// ====== Constants and Macros ======
// OS to compile for
#define OS LINUX

// Operative System
#define LINUX 0
#define WIN32 1

// Clear terminal
#if OS == LINUX
#    define CLRSCREEN (system("clear"))

#elif OS == WIN32
#    define CLRSCREEN (system("cls"))

#else
#    error "Bad definition of Operative System"
#endif

#ifndef OS
#    error "Operative System not defined"
#endif

// ====== Functions ======

// Main

int
main(int argc, char **argv)
{
    uint8_t mode = ERROR;
    answer_t usrinput;

    chkArgs(&mode, &argc, argv[1]);

    switch(mode)
    {
        case ALLEGRO:
            if(!start_allegro())
            {
                return (EXIT_FAILURE);
            }

            if(!main_window())
            {
                return (EXIT_FAILURE);
            }

            break;

        case TERMINAL:
            /* TERMINAL MODE*/
            // Turn off terminal line buffering
            changemode(BUFFERED_OFF);

            do
            {
                CLRSCREEN;

#ifndef TEST
                // Print LEDs status
                printLEDstatus();

                // Print instructions
                printInstructions();
#endif

                // Wait for a (correct) keyboard input
                while(!kbhit() && !kbinput(&usrinput));


            } while(usrinput.letter != 'q');

            // Turn on terminal line buffering
            changemode(BUFFERED_ON);

            break;

        default:
            puts("Bad argument input.");
            puts("[--terminal] or [-t] arguments to execute in terminal mode.");
            puts("[--gui] , [-g] or nothing to execute in gui mode. ");
            break;
    }

    return (EXIT_SUCCESS);
}
