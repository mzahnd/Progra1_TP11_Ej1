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
 * Created: 02/11/2019, 16:39
 * 
 * General code description:
 *          
 * ============================================================================
 */

// ====== Libreries ======
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Library used to manage the microcontroller ports
#include "../libs/PortEmul/PortEmul.h"

// Allegro
#include <allegro5/allegro.h>

// This File
#include "keyboard.h"

void
al_kbinput(ALLEGRO_EVENT *event, const uint8_t type,
           uint8_t *keyok, uint8_t *do_exit)
{
    static uint8_t b_pressed = false;

    const uint8_t port = 'A';

    if(type == ALLEGRO_EVENT_KEY_UP)
    {
        switch(event -> keyboard.keycode)
        {
            case ALLEGRO_KEY_B:
                // Not Working
                if(b_pressed)
                {
                    b_pressed = false;
                }

                else
                {
                    b_pressed = true;
                }

                *keyok = true;
                break;
            default:
                break;
        }
    }

    else if(type == ALLEGRO_EVENT_KEY_DOWN)
    {
        switch(event -> keyboard.keycode)
        {
            case ALLEGRO_KEY_Q:
                *do_exit = true;
                break;

            case ALLEGRO_KEY_T:
                maskToggle(port, 0xFF);
                *keyok = true;
                break;

            case ALLEGRO_KEY_C:
                maskOff(port, 0xFF);
                *keyok = true;
                break;

            case ALLEGRO_KEY_S:
                maskOn(port, 0xFF);
                *keyok = true;
                break;

            case ALLEGRO_KEY_0:
                bitToggle(port, 0);
                *keyok = true;
                break;

            case ALLEGRO_KEY_1:
                bitToggle(port, 1);
                *keyok = true;
                break;

            case ALLEGRO_KEY_2:
                bitToggle(port, 2);
                *keyok = true;
                break;

            case ALLEGRO_KEY_3:
                bitToggle(port, 3);
                *keyok = true;
                break;

            case ALLEGRO_KEY_4:
                bitToggle(port, 4);
                *keyok = true;
                break;

            case ALLEGRO_KEY_5:
                bitToggle(port, 5);
                *keyok = true;
                break;

            case ALLEGRO_KEY_6:
                bitToggle(port, 6);
                *keyok = true;
                break;

            case ALLEGRO_KEY_7:
                bitToggle(port, 7);
                *keyok = true;
                break;

            default:
                break;
        }
    }

    else
    {
        fprintf(stderr, "Bad call of al_kbinput.\n");
    }
}
