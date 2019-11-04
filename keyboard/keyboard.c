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
 * File:    keyboard.c
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
 *          Manages actions when an Allegro Keyboard Event is detected.
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

// Audio managment
#include "../audio/auidomgmt.h"

// Frontend
#include "../frontend/frontend.h"

// This File
#include "keyboard.h"

// ====== Constants and Macros ======
#define PORT    'A'

// ====== Functions ======

// Manage keyboard input when using GUI mode

void
al_kbinput(ALLEGRO_EVENT *event, const uint8_t type, uint8_t *do_exit)
{
    /*
     * Declaro variables
     */
    // B key status
    static uint8_t b_pressed = false;

    if(type == ALLEGRO_EVENT_KEY_UP)
    {
        switch(event -> keyboard.keycode)
        {
            case ALLEGRO_KEY_B:
                /* Si presiona la tecla B, se inicia o se termina el parpadeo
                 * de los LED
                 */
                if(b_pressed)
                {
                    playAudio("audio/blinkoff.ogg");

                    b_pressed = false;
                    // Change Blinking status
                    ledBlink(true);
                }

                else
                {
                    playAudio("audio/blinkon.ogg");
                    b_pressed = true;
                    // Change Blinking status
                    ledBlink(true);

                }
                break;
            default:
                break;
        }
    }

    else if(type == ALLEGRO_EVENT_KEY_DOWN)
    {
        switch(event -> keyboard.keycode)
        {
                // Si se presiona la m se reproduce un audio en honor a Martín
            case ALLEGRO_KEY_M:
                playAudio("audio/martin.ogg");
                break;

                /* Si se presiona la K se reproduce un audio en honor a la 
                 * señora de los chanchos.
                 */
            case ALLEGRO_KEY_K:
                playAudio("audio/chancha.ogg");
                break;

                /*Presione Q para salir*/
            case ALLEGRO_KEY_Q:
                playAudio("audio/out.ogg");
                // Time gap to play audio
                al_rest(1.0);
                *do_exit = true;
                break;

                /*Presione T para invertir los estados de los leds*/
            case ALLEGRO_KEY_T:
                playAudio("audio/ledinvert.ogg");
                maskToggle(PORT, 0xFF);
                break;

                /*Presione C para apagar todos los leds*/
            case ALLEGRO_KEY_C:
                playAudio("audio/ledoff.ogg");
                maskOff(PORT, 0xFF);
                break;

                /*Presione S para encender todos los leds*/
            case ALLEGRO_KEY_S:
                playAudio("audio/ledon.ogg");
                maskOn(PORT, 0xFF);
                break;

                /*Presione un numero para invertir el estado de dicho bit*/
            case ALLEGRO_KEY_0:
                bitToggle(PORT, 0);
                break;

            case ALLEGRO_KEY_1:
                bitToggle(PORT, 1);
                break;

            case ALLEGRO_KEY_2:
                bitToggle(PORT, 2);
                break;

            case ALLEGRO_KEY_3:
                bitToggle(PORT, 3);
                break;

            case ALLEGRO_KEY_4:
                bitToggle(PORT, 4);
                break;

            case ALLEGRO_KEY_5:
                bitToggle(PORT, 5);
                break;

            case ALLEGRO_KEY_6:
                bitToggle(PORT, 6);
                break;

            case ALLEGRO_KEY_7:
                bitToggle(PORT, 7);
                break;

                // Invalid key pressed
            default:
                // Do nothing
                break;
        }
    }

        // Just in case
    else
    {
        fprintf(stderr, "Bad call of al_kbinput.\n");
    }
}
