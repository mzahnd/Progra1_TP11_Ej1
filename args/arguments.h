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
 * File:    arguments.h
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
 *          
 * ============================================================================
 */

#ifndef ARGUMENTS_H
#    define ARGUMENTS_H

// ====== Constants and Macros ======
enum mode
{
    ERROR = -1,
    TERMINAL,
    ALLEGRO
};

// ====== Prototypes ======
// Verify CLI arguments
 void
chkArgs(uint8_t *mode, int *argc, char *string);
 
#endif /* ARGUMENTS_H */
