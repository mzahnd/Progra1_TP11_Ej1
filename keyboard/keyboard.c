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
#include <allegro5/allegro_audio.h> 
#include <allegro5/allegro_acodec.h> 

// This File
#include "keyboard.h"

void
al_kbinput(ALLEGRO_EVENT *event, const uint8_t type,
           uint8_t *keyok, uint8_t *do_exit)
{
    /*Declaro variables
     */
    static uint8_t b_pressed = false;
    static ALLEGRO_SAMPLE *sample = NULL;
    const uint8_t port = 'A';

    /*Instalo e inicio funciones de Allegro
     */
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(1);
    al_install_keyboard();


    if(type == ALLEGRO_EVENT_KEY_UP)
    {
        switch(event -> keyboard.keycode)
        {
            case ALLEGRO_KEY_B:
                /*si presiona la tecla B, se inicia o se termina el parpadeo
                 * del led
                 */
                // Not Working
                if(b_pressed)
                {
                    sample = al_load_sample("blinkoon.ogg");
                    al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    b_pressed = false;
                }

                else
                {
                    //sample = al_load_sample("blinkoff.ogg");
                    //al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
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
                /*si se presiona la m se reproduce un audio en honor a martin */
            case ALLEGRO_KEY_M:
                sample = al_load_sample("martin.ogg");
                al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                break;
                /*Si se preciona la k se reproduce un audio en honor a la señora 
                 * de los chanchos.
                 */
            case ALLEGRO_KEY_K:
                sample = al_load_sample("chancha.ogg");
                al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                break;
                /*presione Q para salir*/
            case ALLEGRO_KEY_Q:
                sample = al_load_sample("out.ogg");
                al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                *do_exit = true;
                break;

                /*presione T para invertir los estados de los leds*/
            case ALLEGRO_KEY_T:
                sample = al_load_sample("ledinvert.ogg");
                al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                maskToggle(port, 0xFF);
                *keyok = true;
                break;
                /*presione c para apagar los leds seleccionados*/
            case ALLEGRO_KEY_C:
                sample = al_load_sample("ledoff.ogg");
                al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                maskOff(port, 0xFF);
                *keyok = true;
                break;
                /*presione S para encender los leds seleccionados*/
            case ALLEGRO_KEY_S:
                sample = al_load_sample("ledon.ogg");
                al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                maskOn(port, 0xFF);
                *keyok = true;
                break;
                /*precione cero para invertir el estado actual del bit 0*/
            case ALLEGRO_KEY_0:
                bitToggle(port, 0);
                *keyok = true;
                break;
                /*precione cero para invertir el estado actual del bit 1*/
            case ALLEGRO_KEY_1:
                bitToggle(port, 1);
                *keyok = true;
                break;
                /*precione cero para invertir el estado actual del bit 2*/
            case ALLEGRO_KEY_2:
                bitToggle(port, 2);
                *keyok = true;
                break;
                /*precione cero para invertir el estado actual del bit 3*/
            case ALLEGRO_KEY_3:
                bitToggle(port, 3);
                *keyok = true;
                break;
                /*precione cero para invertir el estado actual del bit 4*/
            case ALLEGRO_KEY_4:
                bitToggle(port, 4);
                *keyok = true;
                break;
                /*precione cero para invertir el estado actual del bit 5*/
            case ALLEGRO_KEY_5:
                bitToggle(port, 5);
                *keyok = true;
                break;
                /*precione cero para invertir el estado actual del bit 6*/
            case ALLEGRO_KEY_6:
                bitToggle(port, 6);
                *keyok = true;
                break;
                /*precione cero para invertir el estado actual del bit 7*/
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
