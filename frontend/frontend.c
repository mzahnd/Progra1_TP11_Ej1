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
 * File:    frontend.c
 * 
 * Author:  Axel N. Cincunegui                        <acincunegui@itba.edu.ar>
 *          Gino Minnucci                               <gminnucci@itba.edu.ar>
 *          Martín E. Zahnd                                <mzahnd@itba.edu.ar>
 *
 * Team:    Grupo 3
 * 
 * Created: 29/10/2019, 18:01
 * 
 * General code description:
 *          
 * ============================================================================
 */

// ====== Libreries ======
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Allegro
#include <allegro5/allegro5.h>

#include <allegro5/allegro_color.h>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <allegro5/allegro_primitives.h> 

// Library used to manage the microcontroller ports
#include "../libs/PortEmul/PortEmul.h"

#include "../keyboard/keyboard.h"

// This file
#include "frontend.h"

// ====== Constants and Macros ======
#define LEDS        8
#define TXT_INST    6

#define D_WIDTH     ( (2 * LEDS * LED_SIZE) + (2 * LEDS * LED_BORDER ) + \
                    LED_SHIFT + LED_SPC_BTWN )
#define D_HEIGHT    ( (2 * LED_SIZE) + (2 * LED_BORDER) + (2 * LED_SHIFT) + \
                    ((TXT_INST_POS_Y) + (TXT_INST * TXT_INST_SIZE)) )

#define MAIN_BKGND_COLOR    "#000000"
#define LED_COLOR_BORDER    "#626567"
#define LED_COLOR_OFF       "#0A490A"
#define LED_COLOR_ON        "#00FF00"
#define TXT_INST_COLOR      "#D7DBDD"

// LEDs position and size in Main Window. Must be float
// Radius
#define LED_SIZE            20.0
#define LED_BORDER          (LED_SIZE / 5.0)

// 0.5 added to ensure LED looks nice
#define LED_SIZE_INT        (LED_SIZE - (LED_BORDER / 2.0) + 0.5)

// First LED Shift respect to top left corner (in both, x and y axis)
#define LED_SHIFT           10.0
// Space between LEDs
#define LED_SPC_BTWN        ((2 * LED_SIZE) + (LED_BORDER) + LED_SHIFT)

#define LED_POS_X          (LED_SHIFT + LED_SIZE + LED_BORDER)
#define LED_POS_Y          (LED_SHIFT + LED_SIZE + LED_BORDER)

/*
 * @brief Look Up Table for LEDs position and colors
 * 
 * leds_lku[i][0] = LED i position in X axis
 * 
 * leds_lku[i][1] = LED i position in Y axis
 * 
 * leds_lku[i][2] = LED border size
 * 
 * leds_lku[i][3] = LED size
 * 
 * leds_lku[i][4] = LED border thikness
 */
static const float leds_lku[LEDS][5] = {
    {LED_POS_X + (0 * LED_SPC_BTWN), LED_POS_Y,
     LED_SIZE, LED_SIZE_INT, LED_BORDER},
    {LED_POS_X + (1 * LED_SPC_BTWN), LED_POS_Y,
     LED_SIZE, LED_SIZE_INT, LED_BORDER},
    {LED_POS_X + (2 * LED_SPC_BTWN), LED_POS_Y,
     LED_SIZE, LED_SIZE_INT, LED_BORDER},
    {LED_POS_X + (3 * LED_SPC_BTWN), LED_POS_Y,
     LED_SIZE, LED_SIZE_INT, LED_BORDER},
    {LED_POS_X + (4 * LED_SPC_BTWN), LED_POS_Y,
     LED_SIZE, LED_SIZE_INT, LED_BORDER},
    {LED_POS_X + (5 * LED_SPC_BTWN), LED_POS_Y,
     LED_SIZE, LED_SIZE_INT, LED_BORDER},
    {LED_POS_X + (6 * LED_SPC_BTWN), LED_POS_Y,
     LED_SIZE, LED_SIZE_INT, LED_BORDER},
    {LED_POS_X + (7 * LED_SPC_BTWN), LED_POS_Y,
     LED_SIZE, LED_SIZE_INT, LED_BORDER},
};

// Instructions
// Must be int
#define TXT_INST_SIZE   18
#define TXT_INST_PATH_FONT \
                    "frontend/fonts/liberation_serif/LiberationSerif-Bold.ttf"

#define TXT_INST_POS_X      (LED_POS_X - LED_SIZE - LED_BORDER)
// Separation from LEDs + LED_POS_Y + LED Diameter + LED_BORDER (twice)
#define TXT_INST_POS_Y      (TXT_INST_SPC_BTWN + LED_SHIFT + (2 * LED_SIZE) + \
                            (2 * LED_BORDER))

#define TXT_INST_SPC_BTWN   (10.0 + TXT_INST_SIZE)

static const float txt_inst_lku[TXT_INST][2] = {
    {TXT_INST_POS_X, TXT_INST_POS_Y + 0 * TXT_INST_SPC_BTWN},
    {TXT_INST_POS_X, TXT_INST_POS_Y + 1 * TXT_INST_SPC_BTWN},
    {TXT_INST_POS_X, TXT_INST_POS_Y + 2 * TXT_INST_SPC_BTWN},
    {TXT_INST_POS_X, TXT_INST_POS_Y + 3 * TXT_INST_SPC_BTWN},
    {TXT_INST_POS_X, TXT_INST_POS_Y + 4 * TXT_INST_SPC_BTWN},
    {TXT_INST_POS_X, TXT_INST_POS_Y + 5 * TXT_INST_SPC_BTWN},
};

// ====== Prototypes ======
// Draw Main display
static void
draw_Main();

// Draw LEDs in Main Window.
static void
draw_leds();

// Print instructions
static int
printInstructions(void);

// Manage Event Queue
static void
manageEvq(uint8_t *do_exit, ALLEGRO_EVENT_QUEUE *evq);

// ====== Functions ======

// Start Allegro modules needed for this program.

int
start_allegro()
{
    if(!al_init())
    {
        fprintf(stderr, "Allegro could not be initialized.\nExiting...\n");
        return AL_ERR_CODE;
    }

    if(!al_install_keyboard())
    {
        fprintf(stderr, "Keyboard could not be initialized.\nExiting...\n");
        return AL_ERR_CODE;
    }

    if(!al_init_primitives_addon())
    {
        fprintf(stderr, "Primitives Addon could not be initialized.\n");
        fprintf(stderr, "Exiting...\n");
        return AL_ERR_CODE;
    }

    /*if(!al_init_font_addon())
    {
        fprintf(stderr, "Fonts Addon could not be initialized.\nExiting...\n");
        return AL_ERR_CODE;
    }*/

    if(!al_init_ttf_addon())
    {
        fprintf(stderr, "TTF Fonts could not be initialized.\nExiting...\n");
        return AL_ERR_CODE;
    }

    return AL_OK_CODE;
}


// Create, draw and show main window

int
main_window()
{
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *evq = NULL;
    //ALLEGRO_TIMER *timer = NULL;

    uint8_t do_exit = false;

    // Start display
    display = al_create_display(D_WIDTH, D_HEIGHT);

    if(!display)
    {
        al_shutdown_primitives_addon();

        fprintf(stderr, "Display could not be initialized.\nExiting...\n");
        return AL_ERR_CODE;
    }

    // Create event queue
    evq = al_create_event_queue();
    if(!evq)
    {
        fprintf(stderr, "Event queue could not be initialized.\nExiting...\n");
        return AL_ERR_CODE;
    }

    // Draw display
    draw_Main();


    // Events sources
    // Display
    al_register_event_source(evq, al_get_display_event_source(display));
    // Keyboard
    al_register_event_source(evq, al_get_keyboard_event_source());

    // Show
    al_flip_display();

    while(!do_exit)
    {
        manageEvq(&do_exit, evq);
    }

    al_rest(2.0);
    al_shutdown_primitives_addon();
    al_destroy_display(display);

    return AL_OK_CODE;
}

// Draw Main display

static void
draw_Main()
{
    // Background
    al_clear_to_color(al_color_html(MAIN_BKGND_COLOR));

    // LEDs
    draw_leds();

    // Instructions
    printInstructions();
}

// Draw LEDs in Main Window

static void
draw_leds()
{
    /*
     * 1.- Draw LED border
     * 2.- Draw inside of the LED
     */

    /*
     * @brief Look Up Table for LEDs position and colors
     * 
     * leds_lku[i][0] = LED i position in X axis
     * 
     * leds_lku[i][1] = LED i position in Y axis
     * 
     * leds_lku[i][2] = LED border size
     * 
     * leds_lku[i][3] = LED size
     * 
     * leds_lku[i][4] = LED border thikness
     * 
     * leds_lku[i][5] = LED i border color
     */

    uint16_t i;
    const int8_t port = 'A';
    uint8_t bit = 0;
    char * ld_color[] = {LED_COLOR_OFF};

    for(i = 0, bit = 0; i < LEDS; i++, bit++)
    {
        // Border

        al_draw_circle(leds_lku[i][0], leds_lku[i][1], leds_lku[i][2],
                       al_color_html(LED_COLOR_BORDER), leds_lku[i][4]);

        if(bitGet(port, bit))
        {
            *ld_color = LED_COLOR_ON;
        }

        else
        {
            *ld_color = LED_COLOR_OFF;
        }


        // LED

        al_draw_filled_circle(leds_lku[i][0], leds_lku[i][1], leds_lku[i][3],
                              al_color_html(*ld_color));

    }
}

// Print instructions

static int
printInstructions(void)
{
    ALLEGRO_FONT *instruct_font = NULL;
    instruct_font = al_load_font(TXT_INST_PATH_FONT, TXT_INST_SIZE, 0);

    if(!instruct_font)
    {
        fprintf(stderr, "Could not load font.\n");
        return AL_ERR_CODE;
    }

    al_draw_text(instruct_font, al_color_html(TXT_INST_COLOR),
                 txt_inst_lku[0][0], txt_inst_lku[0][1], 0,
                 "Press a LED number (0 - 7) to turn it on.");

    al_draw_text(instruct_font, al_color_html(TXT_INST_COLOR),
                 txt_inst_lku[1][0], txt_inst_lku[1][1], 0,
                 "Press \'b\' to blink the LEDs.");

    al_draw_text(instruct_font, al_color_html(TXT_INST_COLOR),
                 txt_inst_lku[2][0], txt_inst_lku[2][1], 0,
                 "Press \'c\' to turn OFF all LEDs.");

    al_draw_text(instruct_font, al_color_html(TXT_INST_COLOR),
                 txt_inst_lku[3][0], txt_inst_lku[3][1], 0,
                 "Press \'s\' to turn ON all LEDs.");

    al_draw_text(instruct_font, al_color_html(TXT_INST_COLOR),
                 txt_inst_lku[4][0], txt_inst_lku[4][1], 0,
                 "Press \'t\' to toggle all LEDs status.");

    al_draw_text(instruct_font, al_color_html(TXT_INST_COLOR),
                 txt_inst_lku[5][0], txt_inst_lku[5][1], 0,
                 "Press \'q\' to exit.");

    return AL_OK_CODE;
}

// Manage Event Queue

static void
manageEvq(uint8_t *do_exit, ALLEGRO_EVENT_QUEUE *evq)
{
    ALLEGRO_EVENT event;
    uint8_t redraw = false;

    if(al_get_next_event(evq, &event))
    {
        switch(event.type)
        {
                // Close Window
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                *do_exit = true;
                break;

                // Keyboard Events
            case ALLEGRO_EVENT_KEY_DOWN:
                al_kbinput(&event, ALLEGRO_EVENT_KEY_DOWN, &redraw, do_exit);
                break;

            case ALLEGRO_EVENT_KEY_UP:
                al_kbinput(&event, ALLEGRO_EVENT_KEY_UP, &redraw, do_exit);
                break;

            default:
                break;
        }
    }

    // Redraw display
    if(redraw)
    {
        redraw = false;

        // Draw Main display
        draw_Main();

        // Show
        al_flip_display();
    }
}
