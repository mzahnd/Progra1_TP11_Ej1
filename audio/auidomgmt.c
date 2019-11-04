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
 * File:    audio.c
 * 
 * Author:  Axel N. Cincunegui                        <acincunegui@itba.edu.ar>
 *          Gino Minnucci                               <gminnucci@itba.edu.ar>
 *          Martín E. Zahnd                                <mzahnd@itba.edu.ar>
 *
 * Team:    Grupo 3
 * 
 * Created: 03/11/2019, 22:30
 * 
 * General code description:
 *          
 * ============================================================================
 */

// ====== Libreries ======
#include <stdio.h>
#include <stdlib.h>

// Allegro
#include <allegro5/allegro5.h>

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "../frontend/frontend.h"

// This file
#include "auidomgmt.h"

// ====== Constants and Macros ======
static ALLEGRO_SAMPLE *audiosmpl = NULL;

// ====== Prototypes ======

// ====== Functions ======

// Play given audio

void
playAudio(const char *audio)
{
    // Set audio
    audiosmpl = al_load_sample(audio);
    if(!audiosmpl)
    {
        fprintf(stderr, "Failed to open audio %s.\n", audio);
    }

    else
    {
        // Play audio    
        if(!al_play_sample(audiosmpl,
                           1.0, 0.0, 1.0,
                           ALLEGRO_PLAYMODE_ONCE, NULL))
        {
            fprintf(stderr, "Failed to play audio %s\n", audio);
        }
    }
}

// Start audio system

void
startAudio(uint8_t *status)
{
    if(*status != AL_ERR_CODE && !al_install_audio())
    {
        fprintf(stderr, "Audio could not be installed.\nExiting...\n");
        *status = AL_ERR_CODE;
    }

    if(*status != AL_ERR_CODE && !al_init_acodec_addon())
    {
        fprintf(stderr, "Audio codec could not be initialized.\nExiting...\n");
        *status = AL_ERR_CODE;
    }

    if(*status != AL_ERR_CODE && !al_reserve_samples(1))
    {
        fprintf(stderr, "Audio sample could not be reserved.\nExiting...\n");
        *status = AL_ERR_CODE;
    }

}

// Destroy audio sample

void
destroySample()
{
    al_destroy_sample(audiosmpl);
    al_uninstall_audio();
}
