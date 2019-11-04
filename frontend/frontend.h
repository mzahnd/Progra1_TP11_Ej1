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
 * File:    frontend.h
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

#ifndef FRONTEND_H
#    define FRONTEND_H

// ====== Constants and Macros ======
#define AL_ERR_CODE 0
#define AL_OK_CODE 1

// ====== Prototypes ======
// Start Allegro modules needed for this program.
int
start_allegro();

// Create, draw and show main window
int
main_window();

// Change Blinking status or change LEDs satus (if status = active)
void
ledBlink(uint8_t change);

#endif /* FRONTEND_H */
