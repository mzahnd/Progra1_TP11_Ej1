/*
 * Copyright (C) 2019 Gino Minnucci
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
 * File:    PortEmul.h
 * 
 * Author:  Axel N. Cincunegui                        <acincunegui@itba.edu.ar>
 *          Gino Minnucci                               <gminnucci@itba.edu.ar>
 *          Martín E. Zahnd                                <mzahnd@itba.edu.ar>
 *
 * Team:    Grupo 3
 * 
 * Created: 21/10/2019, 14:00
 * 
 * General code description:
 *          In this file you will find a series of functions that will allow 
 *  the user to operate with two 8-bit ports. As much as bit by bit as with 
 * masks I allow to have precise control over it.
 * ============================================================================
 */

#ifndef PORTEMUL_H
#    define PORTEMUL_H

// ====== Macros ======

enum stats
{
    OFF, ON
}; //Asignación de valores a tipos de estados.

enum ers
{
    EBIT = 1, EPORT, EMASK
}; //Asignación de valores a tipos de errores.

#    define MASK8_OK 0xFF                //Mascara maxima de 8 bits.

#    define F 0xF                        //F de Fail.

// ====== Prototypes ======

void bitSet(char, unsigned char);
/*Esta función recibe un char indicando el puerto que se desea modificar 
 *y el bit para hacerlo.
 *Su función es encender bits en cada tipo de puerto. En caso de hacerlo en el D,
 *cambiará el A o el B dependiendo del bit indicado*/


void bitClr(char, unsigned char);
/*Esta funcion recibe un char indicando el puerto que se desea modificar 
 *y el bit para hacerlo.
 *Su función es apagar bits en cada tipo de puerto. En caso de hacerlo en el D,
 *cambiará el A o el B dependiendo del bit indicado*/


unsigned char bitGet(char, unsigned char);
/*Esta función recibe un char indicando el puerto y el bit que se desea conocer
 *y devuelve un unsigned char indicando el valor de un bit.
 *Su función es devolver el valor del bit elegido. En caso de buscarlo en el D,
 *utilizará al A o al B
 *dependiendo del n° de bit.
 *Si un bit no existente es pedido, devolverá una F en hexadecimal 
 *indicando FAIL*/


void bitToggle(char, unsigned char);
/*Esta función recibe un char indicando el puerto que se desea modificar
 *y el bit para hacerlo.
 *Su función es cambiar el valor del bit seleccionado a su opuesto. 
 *En caso de hacerlo en el D, cambiará el A o el B dependiendo del bit indicado*/


void maskOn(char, unsigned short int);
/*Esta función recibe un char indicando el puerto que se desea modificar 
 *y una máscara para hacerlo.
 *Su función es encender sólo los bits indicados por la máscara. 
 *En caso de hacerlo en el A o B,
 *no se podrá ingresar una máscara mayor a 0XFFFF. 
 *Si es D, opera normalmente cambiando a A y B.*/


void maskOff(char, unsigned short int);
/*Esta función recibe un char indicando el puerto que se desea modificar
 *y una máscara para hacerlo.
 *Su función es apagar sólo los bits indicados por la máscara.
 *En caso de hacerlo en el A o B,no se podrá ingresar una máscara mayor a 0XFFFF.
 *Si es D, opera normalmente cambiando a A y B.*/


void maskToggle(char, unsigned short int);
/*Esta función recibe un char indicando el puerto que se desea modificar
 *y una máscara para hacerlo.
 *Su función es cambiar sólo los bits indicados por la máscara.
 *En caso de hacerlo en el A o B,no se podrá ingresar una máscara mayor a 0XFFFF.
 *Si es D, opera normalmente cambiando a A y B.*/

#endif /* PORTEMUL_H */
