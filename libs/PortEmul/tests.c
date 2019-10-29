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
 * Created: 23/10/2019, 20:48
 * 
 * General code description:
 *          
 * ============================================================================
 */

/*
 * NOTE: For this tests to work, the typedef port16_t in PortEmul.c must be 
 * moved to PortEmul.h. This is for testing the correct working of the ports
 * structure.
 */

#include <stdio.h>
#include <stdlib.h>
#include "PortEmul.h"

int
main(void)
{
    extern port16_t d;

    d.num = 0xAA55;

    // ====== BitSet ======
    printf("BITSET\n\n");

    printf("D=%X\n", d.num);
    printf("A=%X\n", d.registros.a);
    printf("B=%X\n", d.registros.b);

    printf("\nUso bitSet en bits 6,4 en A\n");
    bitSet('A', 6);
    bitSet('a', 4);

    printf("D=%X\n", d.num);
    printf("A=%X\n", d.registros.a);
    printf("B=%X\n", d.registros.b);

    printf("\nUso bitSet en bits 7,5 en B\n");
    bitSet('b', 7);
    bitSet('B', 5);

    printf("D=%X\n", d.num);
    printf("A=%X\n", d.registros.a);
    printf("B=%X\n", d.registros.b);

    printf("\nUso bitSet en bits 10,8,3,1 en D\n");
    bitSet('D', 10);
    bitSet('d', 8);
    bitSet('D', 3);
    bitSet('d', 1);

    printf("D=%X\n", d.num);
    printf("A=%X\n", d.registros.a);
    printf("B=%X\n", d.registros.b);


    // ====== BitClear ======
    printf("\nBITCLEAR\n\n");

    printf("D=%X\n", d.num);
    printf("A=%X\n", d.registros.a);
    printf("B=%X\n", d.registros.b);

    printf("\nUso bitClear en bits 6,4 en A\n");
    bitClr('A', 6);
    bitClr('a', 4);

    printf("D=%X\n", d.num);
    printf("A=%X\n", d.registros.a);
    printf("B=%X\n", d.registros.b);

    printf("\nUso bitClear en bits 7,5 en B\n");
    bitClr('b', 7);
    bitClr('B', 5);

    printf("D=%X\n", d.num);
    printf("A=%X\n", d.registros.a);
    printf("B=%X\n", d.registros.b);

    printf("\nUso bitClear en bits 10,8,3,1 en D\n");
    bitClr('D', 10);
    bitClr('d', 8);
    bitClr('D', 3);
    bitClr('d', 1);

    printf("D=%X\n", d.num);
    printf("A=%X\n", d.registros.a);
    printf("B=%X\n", d.registros.b);


    // ====== BitGet ======
    printf("\nBITGET\n\n");

    printf("D=%X\n", d.num);
    printf("A=%X\n", d.registros.a);
    printf("B=%X\n", d.registros.b);

    printf("\nAnalizo bit 7,6 en A\n");

    printf("BIT7:%d\n", bitGet('A', 7));
    printf("BIT6:%d\n", bitGet('a', 6));

    printf("\nAnalizo bit 7,6 en B\n");

    printf("BIT7:%d\n", bitGet('B', 7));
    printf("BIT6:%d\n", bitGet('b', 6));

    printf("\nAnalizo bit 15,7 en D\n");

    printf("BIT15:%d\n", bitGet('D', 15));
    printf("BIT7:%d\n", bitGet('d', 7));


    // ====== BitToggle ======
    printf("\nBITTOGGLE\n\n");

    printf("D=%X\n", d.num);
    printf("A=%X\n", d.registros.a);
    printf("B=%X\n", d.registros.b);

    printf("\nUso bitToggle en bits 0,1 en A\n");
    bitToggle('A', 0);
    bitToggle('a', 1);

    printf("D=%X\n", d.num);
    printf("A=%X\n", d.registros.a);
    printf("B=%X\n", d.registros.b);

    printf("\nUso bitToggle en bits 0,1 en B\n");
    bitToggle('b', 0);
    bitToggle('B', 1);

    printf("D=%X\n", d.num);
    printf("A=%X\n", d.registros.a);
    printf("B=%X\n", d.registros.b);

    printf("\nUso bitToggle en bits 10,8,3,1 en D\n");
    bitToggle('D', 10);
    bitToggle('d', 8);
    bitToggle('D', 3);
    bitToggle('d', 1);

    printf("D=%X\n", d.num);
    printf("A=%X\n", d.registros.a);
    printf("B=%X\n", d.registros.b);

    // ====== MaskOn ======
    printf("\nMASKON\n");

    d.num = 0;

    printf("D=%X\n", d.num);
    printf("A=%X\n", d.registros.a);
    printf("B=%X\n", d.registros.b);

    printf("\nUso mascara F0 en A\n");
    maskOn('A', 0xF0);

    printf("D=%X\n", d.num);
    printf("A=%X\n", d.registros.a);
    printf("B=%X\n", d.registros.b);

    printf("\nUso mascara F en B\n");
    maskOn('b', 0xF);

    printf("D=%X\n", d.num);
    printf("A=%X\n", d.registros.a);
    printf("B=%X\n", d.registros.b);

    printf("\nUso mascara FFFF en D\n");
    maskOn('D', 0xFFFF);

    printf("D=%X\n", d.num);
    printf("A=%X\n", d.registros.a);
    printf("B=%X\n", d.registros.b);



    // ====== MaskOff ======
    printf("\nMASKOFF\n");

    printf("D=%X\n", d.num);
    printf("A=%X\n", d.registros.a);
    printf("B=%X\n", d.registros.b);

    printf("\nUso mascara F0 en A\n");
    maskOff('A', 0xF0);

    printf("D=%X\n", d.num);
    printf("A=%X\n", d.registros.a);
    printf("B=%X\n", d.registros.b);

    printf("\nUso mascara F en B\n");
    maskOff('b', 0xF);

    printf("D=%X\n", d.num);
    printf("A=%X\n", d.registros.a);
    printf("B=%X\n", d.registros.b);

    printf("\nUso mascara FFFF en D\n");
    maskOff('D', 0xFFFF);

    printf("D=%X\n", d.num);
    printf("A=%X\n", d.registros.a);
    printf("B=%X\n", d.registros.b);


    // ====== MaskToggle ======

    printf("\nMASKTOGGLE\n");

    d.num = 0xAA55;

    printf("D=%X\n", d.num);
    printf("A=%X\n", d.registros.a);
    printf("B=%X\n", d.registros.b);

    printf("\nUso mascara FF en A\n");
    maskToggle('A', 0xFF);

    printf("D=%X\n", d.num);
    printf("A=%X\n", d.registros.a);
    printf("B=%X\n", d.registros.b);

    printf("\nUso mascara FF en B\n");
    maskToggle('b', 0xFF);

    printf("D=%X\n", d.num);
    printf("A=%X\n", d.registros.a);
    printf("B=%X\n", d.registros.b);

    printf("\nUso mascara FFFF en D\n");
    maskToggle('D', 0xFFFF);

    printf("D=%X\n", d.num);
    printf("A=%X\n", d.registros.a);
    printf("B=%X\n", d.registros.b);


    // ====== BitError ======

    printf("\nBIT FUNCTIONS");
    printf("\nPuertos y bits incorrectos en todas las funciones de bits\n");

    printf("\nbitSet\n");
    bitSet('k', 6);
    bitSet('a', 8);

    printf("\nbitClr\n");
    bitClr('Q', 6);
    bitClr('a', -5);

    printf("\nbitGet\n");
    printf("Devuelve:%X", bitGet('*', 6));
    printf("Devuelve:%X", bitGet('a', 100));

    printf("\n\nbitToggle\n");
    bitToggle('0', 6);
    bitToggle('a', 58);

    /*********MASK ERRORS*****************************/
    printf("\nMASK FUNCTIONS");
    printf("\nPondré puertos y máscaras incorrectos en todas las funciones de masks\n");

    printf("\nmaskOn\n");
    maskOn('k', 0xFF);
    maskOn('a', 0xFFF);

    printf("\nmaskOff\n");
    maskOff('Q', 0xFF);
    maskOff('b', 0xFFF);

    printf("\nmaskToggle\n");
    maskToggle('&', 0xFF);
    maskToggle('A', 0xFFF);

    return (EXIT_SUCCESS);
}

