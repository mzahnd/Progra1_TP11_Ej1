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
 * File:    arguments.c
 * 
 * Author:  Axel N. Cincunegui                        <acincunegui@itba.edu.ar>
 *          Gino Minnucci                               <gminnucci@itba.edu.ar>
 *          Martín E. Zahnd                                <mzahnd@itba.edu.ar>
 *
 * Team:    Grupo 3
 * 
 * Created: 01/11/2019, 09:48
 * 
 * General code description:
 *          Check if any argument was givven and, if so, acts in consequence.
 * ============================================================================
 */

// ====== Libreries ======
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// This file
#include "arguments.h"

// ====== Functions ======

// Verify CLI arguments

void
chkArgs(uint8_t *mode, int *argc, char *string)
{

    if(*argc == 1)
    {
        *mode = ALLEGRO;
    }

    else if(*argc == 2 &&
            (!strcmp(string, "--terminal") || !strcmp(string, "-t")))
    {
        *mode = TERMINAL;
    }

    else if(*argc == 2 &&
            (!strcmp(string, "--gui") || !strcmp(string, "-g")))
    {
        *mode = ALLEGRO;
    }

    else
    {
        *mode = ERROR;
    }
}
