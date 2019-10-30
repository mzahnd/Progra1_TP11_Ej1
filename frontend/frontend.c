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

// Allegro
#include <allegro5/allegro5.h>

#include <allegro5/allegro_color.h>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <allegro5/allegro_primitives.h> 

// This file
#include "frontend.h"

// ====== Constants and Macros ======
#define D_WIDTH     640
#define D_HEIGHT    480

#define COLOR_MAIN_BKGND    "#FFFFFF"
#define COLOR_LED_BORDER    "#000000"
#define COLOR_LED_OFF       "#0A490A"
#define COLOR_LED_ON        "#00FF00"
#define COLOR_TXT_INST      "#000000"

// LEDs position and size in Main Window. Must be float
// Radius
#define SIZE_LED            20.0
#define BORDER_THIKNESS_LED (SIZE_LED / 5.0)
// 0.5 added to ensure LED looks nice
#define SIZE_INT_LED        SIZE_LED - (BORDER_THIKNESS_LED / 2) + 0.5

#define SHIFT_LED_BORDER    10.0
#define SPACE_BTWN_LEDS     2*SIZE_LED + BORDER_THIKNESS_LED + SHIFT_LED_BORDER

#define LED0_POS_X          SHIFT_LED_BORDER + SIZE_LED + BORDER_THIKNESS_LED
#define LED0_POS_Y          SHIFT_LED_BORDER + SIZE_LED + BORDER_THIKNESS_LED


#define LED1_POS_X          LED0_POS_X + SPACE_BTWN_LEDS
#define LED1_POS_Y          LED0_POS_Y

#define LED2_POS_X          LED1_POS_X + SPACE_BTWN_LEDS
#define LED2_POS_Y          LED0_POS_Y

#define LED3_POS_X          LED2_POS_X + SPACE_BTWN_LEDS
#define LED3_POS_Y          LED0_POS_Y

#define LED4_POS_X          LED3_POS_X + SPACE_BTWN_LEDS
#define LED4_POS_Y          LED0_POS_Y

#define LED5_POS_X          LED4_POS_X + SPACE_BTWN_LEDS
#define LED5_POS_Y          LED0_POS_Y

#define LED6_POS_X          LED5_POS_X + SPACE_BTWN_LEDS
#define LED6_POS_Y          LED0_POS_Y

#define LED7_POS_X          LED6_POS_X + SPACE_BTWN_LEDS
#define LED7_POS_Y          LED0_POS_Y

// Instructions
// Must be int
#define SIZE_INSTRUCTIONS       36
#define PATH_FONT_INSTRUCT  "/fonts/liberation_serif/LiberationSerif-Regular.ttf"

// ====== Prototypes ======
// Draw LEDs in Main Window
static void
draw_leds();

// Print instructions
static int
printInstructions(void);

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

    if(!al_init_font_addon())
    {
        fprintf(stderr, "Fonts Addon could not be initialized.\nExiting...\n");
        return AL_ERR_CODE;
    }

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
    ALLEGRO_TIMER *timer = NULL;

    // Start display
    display = al_create_display(D_WIDTH, D_HEIGHT);

    if(!display)
    {
        al_shutdown_primitives_addon();

        fprintf(stderr, "Display could not be initialized.\nExiting...\n");
        return AL_ERR_CODE;
    }

    // Draw display

    // Background
    al_clear_to_color(al_color_html(COLOR_MAIN_BKGND));

    // LEDs
    draw_leds();

    // Show
    al_flip_display();

    al_rest(2.0);
    al_shutdown_primitives_addon();
    al_destroy_display(display);

    return AL_OK_CODE;
}

// Draw LEDs in Main Window

static void
draw_leds()
{
    /*
     * 1.- LED border
     * 2.- Inside of the LED
     */

    // LED0
    al_draw_circle(LED0_POS_X, LED0_POS_Y, SIZE_LED,
                   al_color_html(COLOR_LED_BORDER), BORDER_THIKNESS_LED);
    al_draw_filled_circle(LED0_POS_X, LED0_POS_Y, SIZE_INT_LED,
                          al_color_html(COLOR_LED_OFF));

    // LED1
    al_draw_circle(LED1_POS_X, LED1_POS_Y, SIZE_LED,
                   al_color_html(COLOR_LED_BORDER), BORDER_THIKNESS_LED);
    al_draw_filled_circle(LED1_POS_X, LED1_POS_Y, SIZE_INT_LED,
                          al_color_html(COLOR_LED_OFF));

    // LED2
    al_draw_circle(LED2_POS_X, LED2_POS_Y, SIZE_LED,
                   al_color_html(COLOR_LED_BORDER), BORDER_THIKNESS_LED);
    al_draw_filled_circle(LED2_POS_X, LED2_POS_Y, SIZE_INT_LED,
                          al_color_html(COLOR_LED_OFF));

    // LED3
    al_draw_circle(LED3_POS_X, LED3_POS_Y, SIZE_LED,
                   al_color_html(COLOR_LED_BORDER), BORDER_THIKNESS_LED);
    al_draw_filled_circle(LED3_POS_X, LED3_POS_Y, SIZE_INT_LED,
                          al_color_html(COLOR_LED_OFF));

    // LED4
    al_draw_circle(LED4_POS_X, LED4_POS_Y, SIZE_LED,
                   al_color_html(COLOR_LED_BORDER), BORDER_THIKNESS_LED);
    al_draw_filled_circle(LED4_POS_X, LED4_POS_Y, SIZE_INT_LED,
                          al_color_html(COLOR_LED_OFF));

    // LED5
    al_draw_circle(LED5_POS_X, LED5_POS_Y, SIZE_LED,
                   al_color_html(COLOR_LED_BORDER), BORDER_THIKNESS_LED);
    al_draw_filled_circle(LED5_POS_X, LED5_POS_Y, SIZE_INT_LED,
                          al_color_html(COLOR_LED_OFF));

    // LED6
    al_draw_circle(LED6_POS_X, LED6_POS_Y, SIZE_LED,
                   al_color_html(COLOR_LED_BORDER), BORDER_THIKNESS_LED);
    al_draw_filled_circle(LED6_POS_X, LED6_POS_Y, SIZE_INT_LED,
                          al_color_html(COLOR_LED_OFF));

    // LED7
    al_draw_circle(LED7_POS_X, LED7_POS_Y, SIZE_LED,
                   al_color_html(COLOR_LED_BORDER), BORDER_THIKNESS_LED);
    al_draw_filled_circle(LED7_POS_X, LED7_POS_Y, SIZE_INT_LED,
                          al_color_html(COLOR_LED_OFF));

}

// Print instructions

static int
printInstructions(void)
{
    ALLEGRO_FONT *instruct_font = NULL;
    instruct_font = al_load_font(PATH_FONT_INSTRUCT, SIZE_INSTRUCTIONS, 0);

    if(!instruct_font)
    {
        fprintf(stderr, "Could not load font.\n");
        return AL_ERR_CODE;
    }

    //al_draw_text(intruct_font, COLOR_TXT_INST);

    /*
    puts(TEXT_COLOR "\nPress a LED number (0 - 7) to turn it on.");
    puts(TEXT_COLOR "Press \'t\' to toggle all LEDs status.");
    puts(TEXT_COLOR "Press \'s\' to turn ON all LEDs.");
    puts(TEXT_COLOR "Press \'c\' to turn OFF all LEDs.");
    puts(TEXT_COLOR "Press \'q\' to exit.");

     */

    return AL_OK_CODE;
}
