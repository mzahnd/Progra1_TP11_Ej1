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
 * File:    PortEmul.c
 * 
 * Author:  Axel N. Cincunegui                        <acincunegui@itba.edu.ar>
 *          Gino Minnucci                               <gminnucci@itba.edu.ar>
 *          Martín E. Zahnd                                <mzahnd@itba.edu.ar>
 *
 * Team:    Grupo 3
 * 
 * Created: 23/10/2019, 20:48
 * 
 * General code description:
 *          In this file you will find a series of functions that will allow 
 *  the user to operate with two 8-bit ports. As much as bit by bit as with 
 * masks I allow to have precise control over it.
 * ============================================================================
 */

// ====== Libreries ======
#include <stdio.h>
#include <stdlib.h>

// This file
#include "PortEmul.h"

// ====== Structures and Unions ======

typedef union //Declaración de unión entre registro D y A junto con B.
{
    /**
     * @brief 
     * 
     * Para digirise al puerto D, se debe acceder mediante d.num
     * 
     * Para digirise al puerto A, se debe acceder mediante d.registros.a
     * 
     * Para digirise al puerto B, se debe acceder mediante d.registros.b
     */

    // @brief Puerto D

    unsigned short int num; //Declaración de puerto D en formato de dos bytes.

    struct //Declaración de estructura que contiene a registros A y B.
    {
        // @brief Puerto B

        unsigned char b;

        //Primero se coloca el puerto B pues es little endianne.

        // @brief Puerto A

        unsigned char a;
    } registros;

} port16_t; //Alias del tipo de dato creado.


// ====== Variables ======
/*Estructura del puerto D*/
port16_t d;


// ====== Prototypes ======
static void error(int);
/*Esta función recibe un tipo de error y lo analiza.
 *Dependiendo de cual sea, envía un mensaje al usuario*/

// ====== Public Functions ======

/*Función que permite encender un bit en especifico del puerto que se 
 *indique.*/
void
bitSet(char puerto, unsigned char bit)
{
    /*contador de ciclo For*/
    int i;
    /*incializa la mascara en 1*/
    unsigned int mask = ON;

    /*Condicional que verifica que el puerto ingresado sea valido(en especifico, 
     *el puerto D), asi como que el numero de bit que se quiere operar.*/
    if(((puerto == 'D') || (puerto == 'd'))&&(bit <= 15))
    {
        for(i = 0; i < bit; i++)
        {
            /*Se realiza un corrimiento del entre bit hacia la izquierda tantas
             veces hasta llegar al bit solicitado por parametro*/
            mask <<= 1;
        }
        /*Se realiza una operacion OR poniento en uno aquel bit seleccionado
         mediante la mascara*/
        d.num |= mask;
    }
        /*Condicional que verifica que el puerto ingresado sea valido(en especifico, 
         *el puerto A), asi como que el numero de bit que se quiere operar.*/
    else if(((puerto == 'a') || (puerto == 'A'))&&(bit <= 7))
    {
        for(i = 0; i < bit; i++)
        {
            /*Se realiza un corrimiento del entre bit hacia la izquierda tantas
             veces hasta llegar al bit solicitado por parametro*/
            mask <<= 1;
        }
        /*Se realiza una operacion OR poniento en uno aquel bit seleccionado
         mediante la mascara, se realiza un casteo defencivo*/
        d.registros.a |= (unsigned char) mask;
    }
        /*Condicional que verifica que el puerto ingresado sea valido(en especifico, 
         *el puerto B), asi como que el numero de bit que se quiere operar.*/
    else if(((puerto == 'b') || (puerto == 'B'))&&(bit <= 7))
    {
        for(i = 0; i < bit; i++)
        {
            /*Se realiza un corrimiento del entre bit hacia la izquierda tantas
             veces hasta llegar al bit solicitado por parametro*/
            mask <<= 1;
        }
        /*Se realiza una operacion OR poniento en uno aquel bit seleccionado
         mediante la mascara, se realiza un casteo defencivo*/
        d.registros.b |= (unsigned char) mask;
    }
        /*Condicional que dado que no se cumpla con los parametros soportados por 
         *la función, se porcedera a informa el error correspondiente*/
    else if(((bit > 7)&&((puerto != 'D') || (puerto != 'd'))) || (bit > 15))
    {
        /*Si el error es en el bit ingresado*/
        error(EBIT);
    }

    else
    {
        /*Si el error es en el puerto ingresado*/
        error(EPORT);
    }

    return;
}

/*Función que permite apagar un bit en especifico del puerto que se 
 *indique.*/
void
bitClr(char puerto, unsigned char bit)
{
    /*contador de ciclo For*/
    int i;
    /*incializa la mascara en 1*/
    unsigned int mask = ON;

    /*Condicional que verifica que el puerto ingresado sea valido(en especifico, 
     *el puerto D), asi como que el numero de bit que se quiere operar.*/
    if(((puerto == 'D') || (puerto == 'd'))&&(bit <= 15))
    {
        for(i = 0; i < bit; i++)
        {
            /*Se realiza un corrimiento del entre bit hacia la izquierda tantas
             veces hasta llegar al bit solicitado por parametro*/
            mask <<= 1;
        }
        /*Se invierte la mascara*/
        mask = ~mask;
        /*Se realiza una operacion AND poniento en cero aquel bit seleccionado
         mediante la mascara*/
        d.num &= mask;
    }
        /*Condicional que verifica que el puerto ingresado sea valido(en especifico, 
         *el puerto D), asi como que el numero de bit que se quiere operar.*/
    else if(((puerto == 'a') || (puerto == 'A'))&&(bit <= 7))
    {
        for(i = 0; i < bit; i++)
        {
            /*Se realiza un corrimiento del entre bit hacia la izquierda tantas
             veces hasta llegar al bit solicitado por parametro*/
            mask <<= 1;
        }
        /*Se invierte la mascara*/
        mask = ~mask;
        /*Se realiza una operacion AND poniento en cero aquel bit seleccionado
         mediante la mascara, se realiza un casteo defencivo*/
        d.registros.a &= (unsigned char) mask;
    }
        /*Condicional que verifica que el puerto ingresado sea valido(en especifico, 
         *el puerto D), asi como que el numero de bit que se quiere operar.*/
    else if(((puerto == 'b') || (puerto == 'B'))&&(bit <= 7))
    {
        for(i = 0; i < bit; i++)
        {
            /*Se realiza un corrimiento del entre bit hacia la izquierda tantas
             veces hasta llegar al bit solicitado por parametro*/
            mask <<= 1;
        }
        /*Se invierte la mascara*/
        mask = ~mask;
        /*Se realiza una operacion AND poniento en cero aquel bit seleccionado
         mediante la mascara, se realiza un casteo defencivo*/
        d.registros.b &= (unsigned char) mask;
    }

        /*Condicional que dado que no se cumpla con los parametros soportados por 
         *la función, se porcedera a informa el error correspondiente*/
    else if(((bit > 7)&&((puerto != 'D') || (puerto != 'd'))) || (bit > 15))
    {
        /*Si el error es en el bit ingresado*/
        error(EBIT);
    }

    else
    {
        /*Si el error es en el puerto ingresado*/
        error(EPORT);
    }

    return;

}

/*Función que permite obtener el estado actual de un bit de un puerto espefici-
 fico dado por parametro*/
unsigned char
bitGet(char puerto, unsigned char bit)
{
    /*Contador de ciclo FOR*/
    int i;
    /*Variable con el estado actual del bit*/
    unsigned char result;
    /*Incializa la mascara en 1*/
    unsigned int mask = ON;

    /*Condicional que verifica que el puerto ingresado sea valido(en especifico, 
     *el puerto D), asi como que el numero de bit que se quiere operar.*/
    if(((puerto == 'D') || (puerto == 'd'))&&(bit <= 15))
    {
        for(i = 0; i < bit; i++)
        {
            /*Se realiza un corrimiento del entre bit hacia la izquierda tantas
             veces hasta llegar al bit solicitado por parametro*/
            mask <<= 1;
        }
        result = ((d.num & mask) != OFF);
    }

        /*Condicional que verifica que el puerto ingresado sea valido(en especifico, 
         *el puerto D), asi como que el numero de bit que se quiere operar.*/
    else if(((puerto == 'a') || (puerto == 'A'))&&(bit <= 7))
    {
        for(i = 0; i < bit; i++)
        {
            /*Se realiza un corrimiento del entre bit hacia la izquierda tantas
             veces hasta llegar al bit solicitado por parametro*/
            mask <<= 1;
        }
        result = ((d.registros.a & (unsigned char) mask) != OFF);
    }

        /*Condicional que verifica que el puerto ingresado sea valido(en especifico, 
         *el puerto D), asi como que el numero de bit que se quiere operar.*/
    else if(((puerto == 'b') || puerto == 'B')&&(bit <= 7))
    {
        for(i = 0; i < bit; i++)
        {
            /*Se realiza un corrimiento del entre bit hacia la izquierda tantas
             veces hasta llegar al bit solicitado por parametro*/
            mask <<= 1;
        }
        result = ((d.registros.b & (unsigned char) mask) != OFF);
    }

        /*Condicional que dado que no se cumpla con los parametros soportados por 
         *la función, se porcedera a informa el error correspondiente*/
    else if(((bit > 7)&&((puerto != 'D') || (puerto != 'd'))) || (bit > 15))
    {
        /*Devuelvo error */
        result = F;
        /*Si el error es en el bit ingresado*/
        error(EBIT);
    }

    else
    {
        /*Si el error es en el puerto ingresado*/
        error(EPORT);
        result = F;
    }

    return result;
}

/*Función que pone en el estado opuesto al bit y puerto seleccionado.*/
void
bitToggle(char puerto, unsigned char bit)
{
    /*Contador de ciclo FOR*/
    int i;
    /*Inicializa la mascara en 1*/
    unsigned int mask = ON;

    /*Condicional que verifica que el puerto ingresado sea valido(en especifico, 
     *el puerto D), asi como que el numero de bit que se quiere operar.*/
    if(((puerto == 'D') || (puerto == 'd'))&&(bit <= 15))
    {
        for(i = 0; i < bit; i++)
        {
            /*Se realiza un corrimiento del entre bit hacia la izquierda tantas
             veces hasta llegar al bit solicitado por parametro*/
            mask <<= 1;
        }
        /*Se realiza una operacion XOR invirtiendo aquel bit seleccionado
         mediante la mascara*/
        d.num ^= mask;
    }
        /*Condicional que verifica que el puerto ingresado sea valido(en especifico, 
         *el puerto A), asi como que el numero de bit que se quiere operar.*/
    else if(((puerto == 'a') || (puerto == 'A'))&&(bit <= 7))
    {
        for(i = 0; i < bit; i++)
        {
            /*Se realiza un corrimiento del entre bit hacia la izquierda tantas
             veces hasta llegar al bit solicitado por parametro*/
            mask <<= 1;
        }
        /*Se realiza una operacion XOR invirtiendo aquel bit seleccionado
         mediante la mascara, se realiza un casteo defencivo*/
        d.registros.a ^= (unsigned char) mask;
    }

        /*Condicional que verifica que el puerto ingresado sea valido(en especifico, 
         *el puerto B), asi como que el numero de bit que se quiere operar.*/
    else if(((puerto == 'b') || (puerto == 'B'))&&(bit <= 7))
    {
        for(i = 0; i < bit; i++)
        {
            /*Se realiza un corrimiento del entre bit hacia la izquierda tantas
             veces hasta llegar al bit solicitado por parametro*/
            mask <<= 1;
        }
        /*Se realiza una operacion XOR invirtiendo aquel bit seleccionado
         mediante la mascara, se realiza un casteo defencivo*/
        d.registros.b ^= (unsigned char) mask;
    }

        /*Condicional que dado que no se cumpla con los parametros soportados por 
         *la función, se porcedera a informa el error correspondiente*/
    else if(((bit > 7)&&((puerto != 'D') || (puerto != 'd'))) || (bit > 15))
    {
        /*Si el error es en el bit ingresado*/
        error(EBIT);
    }

    else
    {
        /*Si el error es en el puerto ingresado*/
        error(EPORT);
    }

    return;

}

/*Funcion que enciende los bits que se indican mediante la mascara*/
void
maskOn(char puerto, unsigned short int mask)
{
    /*Condicional que verifica que el puerto ingresado sea valido(en especifico, 
     *el puerto D), asi como la mascara sea valida.*/
    if((puerto == 'd') || (puerto == 'D'))
    {
        /*Realiza una operación OR entre el puerto y la mascara*/
        d.num |= mask;
    }
        /*Condicional que verifica que el puerto ingresado sea valido(en especifico, 
         *el puerto A),  asi como la mascara sea valida.*/
    else if(((puerto == 'a') || (puerto == 'A')) && (mask <= MASK8_OK))
    {
        /*Realiza una operación OR entre el puerto y la mascara,se realiza un 
         casteo defencivo*/
        d.registros.a |= (unsigned char) mask;
    }

        /*Condicional que verifica que el puerto ingresado sea valido(en especifico, 
         *el puerto B),  asi como la mascara sea valida.*/
    else if(((puerto == 'b') || (puerto == 'B')) && (mask <= MASK8_OK))
    {
        /*Realiza una operación OR entre el puerto y la mascara,se realiza un 
         casteo defencivo*/
        d.registros.b |= (unsigned char) mask;
    }

    else if((puerto != 'a')&&(puerto != 'b')&&(puerto != 'd'))
    {
        /*Si el error es en el puerto ingresado*/
        error(EPORT);
    }

    else
    {
        /*Si el error es en la mascara ingresada*/
        error(EMASK);
    }
    return;
}

/*Funcion que apaga los bits que se indican mediante la mascara*/
void
maskOff(char puerto, unsigned short int mask)
{
    /*Condicional que verifica que el puerto ingresado sea valido(en especifico, 
     *el puerto D), asi como la mascara sea valida.*/
    if((puerto == 'd') || (puerto == 'D'))
    {
        mask = ~mask;
        /*Realiza una operación AND entre el puerto y la mascara*/
        d.num &= mask;
    }
        /*Condicional que verifica que el puerto ingresado sea valido(en especifico, 
         *el puerto A), asi como la mascara sea valida.*/
    else if(((puerto == 'a') || (puerto == 'A')) && (mask <= MASK8_OK))
    {
        mask = ~mask;
        /*Realiza una operación AND entre el puerto y la mascara,se realiza un 
         casteo defencivo*/
        d.registros.a &= (unsigned char) mask;
    }
        /*Condicional que verifica que el puerto ingresado sea valido(en especifico, 
         *el puerto B), asi como la mascara sea valida.*/
    else if(((puerto == 'b') || (puerto == 'B')) && (mask <= MASK8_OK))
    {
        mask = ~mask;
        /*Realiza una operación AND entre el puerto y la mascara,se realiza un 
         casteo defencivo*/
        d.registros.b &= (unsigned char) mask;
    }

    else if(((mask > MASK8_OK)&&((puerto != 'd') || (puerto != 'D'))))
    {
        /*Si el error es en la mascara ingresada*/
        error(EMASK);
    }

    else
    {
        /*Si el error es en el puerto ingresado*/
        error(EPORT);
    }
    return;
}

/*Funcion que invierte los bits que se indican mediante la mascara*/
void
maskToggle(char puerto, unsigned short int mask)
{
    /*Condicional que verifica que el puerto ingresado sea valido(en especifico, 
     *el puerto D), asi como la mascara sea valida.*/
    if((puerto == 'd') || (puerto == 'D'))
    {
        /*Realiza una operación XOR entre el puerto y la mascara*/
        d.num ^= mask;
    }

        /*Condicional que verifica que el puerto ingresado sea valido(en especifico, 
         *el puerto A), asi como la mascara sea valida.*/
    else if(((puerto == 'a') || (puerto == 'A')) && (mask <= MASK8_OK))
    {
        /*Realiza una operación XOR entre el puerto y la mascara,se realiza un 
         casteo defencivo*/
        d.registros.a ^= (unsigned char) mask;
    }

        /*Condicional que verifica que el puerto ingresado sea valido(en especifico, 
         *el puerto B), asi como la mascara sea valida.*/
    else if(((puerto == 'b') || (puerto == 'B')) && (mask <= MASK8_OK))
    {
        /*Realiza una operación XOR entre el puerto y la mascara,se realiza un 
         casteo defencivo*/
        d.registros.b ^= (unsigned char) mask;
    }

    else if(((mask > MASK8_OK)&&((puerto != 'd') || (puerto != 'D'))))
    {
        /*Si el error es en la mascara ingresada*/
        error(EMASK);
    }

    else
    {
        /*Si el error es en el puerto ingresado*/
        error(EPORT);
    }
}

// ====== Local Functions ======

static void
error(int e)
{
    switch(e) //Analiza el tipo de error.
    {
        case EBIT: //Si es un error de bit incorrecto, imprime en pantalla:
            printf("\nError en n°de bit ingresado\n");
            break;

        case EPORT: //Si es un error de puerto incorrecto, imprime en pantalla:
            printf("\nError en puerto ingresado\n");
            break;

        case EMASK: //Si es un error de máscara incorrecta, imprime en pantalla:
            printf("\nError en mascara ingresada\n");
            break;
    }
    return;
}
// 
