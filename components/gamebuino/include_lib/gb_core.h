/*
This file is part of the Gamebuino-AKA library,
Copyright (c) Gamebuino 2026

This is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License (LGPL)
as published by the Free Software Foundation, either version 3 of
the License, or (at your option) any later version.

This is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License (LGPL) for more details.

You should have received a copy of the GNU Lesser General Public
License (LGPL) along with the library.
If not, see <http://www.gnu.org/licenses/>.

Authors:
 - Jean-Marie Papillon
*/

#include <stdint.h>
#include <stddef.h>
#include "gb_common.h"

#pragma once


class gb_buttons {
    public:
            //! update status of buttons, joystick...
        void update();
            //! return buttons state, cf GB_KEY_xxx
        uint16_t state();
            //! return buttons press event, cf GB_KEY_xxx
        uint16_t pressed();
            //! return buttons release event, cf GB_KEY_xxx
        uint16_t released();

    private:
        uint16_t u16_buttons {0};
        uint16_t u16_buttons_last {0};

};


class gb_core {
    public:
        gb_core();
        ~gb_core();
            //! initialise gamebuino : screen, bus and peripherals
        void init();
            //! update status of buttons, joystick...
        void pool();
            //! buton management
        gb_buttons buttons;
            //! Joystick vertical position, from -1000 to 1000
        int16_t joy_y();
            //! Joystick horizontal position, from -1000 to 1000
        int16_t joy_x();
            //! delay in milliseconds
        void delay_ms(uint32_t u32_ms);
            //! return date in milliseconds
        uint32_t get_millis();
            //! return date in microseconds
        int64_t get_micros();
            //! return count of free PSRAM
        size_t free_psram();
            //! return count of free SRAM
        size_t free_sram();
            //! power down 
        void power_down();    
    private:
    int16_t i16_joy_x {0};
    int16_t i16_joy_y {0};
};




