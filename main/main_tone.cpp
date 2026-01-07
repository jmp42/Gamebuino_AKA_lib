#include "gb_core.h"
#include "gb_audio_player.h"        // main player
#include "gb_audio_track_tone.h"    // tone player
#include "gb_audio_track_fx.h"      // fx tone player

#include "assets/fx_system.h"

gb_core core;                       // Gamebuino core lib
gb_audio_player     player;         // main audio player 
gb_audio_track_tone track_tone;     // 1st track : simple tone sin/square/noise
gb_audio_track_fx   track_fx;       // 2st track : fx allow to can chain tone effects

gb_audio_track_fx_t track_my_music[] = 
{
    { 220, 440, 0.0, 1.0, 250, gb_audio_track_tone::SINE },
    { 440, 330, 1.0, 0.5, 500, gb_audio_track_tone::SINE },
    { 330, 220, 0.5, 0.0, 250, gb_audio_track_tone::SINE },

    { 220, 440, 0.0, 1.0, 250, gb_audio_track_tone::SQUARE },
    { 440, 330, 1.0, 0.5, 500, gb_audio_track_tone::SQUARE },
    { 330, 220, 0.5, 0.0, 250, gb_audio_track_tone::SQUARE },

    { 220, 440, 0.0, 1.0, 250, gb_audio_track_tone::TRIANGLE },
    { 440, 330, 1.0, 0.5, 500, gb_audio_track_tone::TRIANGLE },
    { 330, 220, 0.5, 0.0, 250, gb_audio_track_tone::TRIANGLE },
};



extern "C" void app_main(void)
{
    core.init();                                            // initialize the Gamebuino
    player.set_master_volume(255);                          // set the volume to almost max ( up to 255 )
    player.add_track(&track_tone);                          // add a tone track to player
    player.add_track(&track_fx);                            // add a fx track to player
    track_tone.set_track_volume(1.0);                       // fix volume for this track to 100%
    track_fx.set_track_volume(1.0);                         // fix volume for this track to 100%

    for ( int iLoop = 0 ; ; iLoop++ )
    {
        uint16_t u16_buttons = core.buttons.pressed();

            // embeeded fx example sound
        if ( u16_buttons & gb_buttons::KEY_A )
            track_fx.play_fx( gb_fx_system_ok, count_of(gb_fx_system_ok) );
        if ( u16_buttons & gb_buttons::KEY_B )
            track_fx.play_fx( gb_fx_system_ko, count_of(gb_fx_system_ko) );
        if ( u16_buttons & gb_buttons::KEY_C )
            track_fx.play_fx( gb_fx_system_tick, count_of(gb_fx_system_tick) );
        if ( u16_buttons & gb_buttons::KEY_D )
            track_fx.play_fx( gb_fx_system_explode, count_of(gb_fx_system_explode) );

            // simple tone
        if ( u16_buttons & gb_buttons::KEY_UP )   
            track_tone.play_tone( 600, 800, 0.0, 1.0, 250, gb_audio_track_tone::SINE );
        if ( u16_buttons & gb_buttons::KEY_DOWN ) 
            track_tone.play_tone( 440, 220, 1.0, 0.0, 100, gb_audio_track_tone::SQUARE );
        if ( u16_buttons & gb_buttons::KEY_LEFT ) 
            track_tone.play_tone( 220, 220, 1.0, 0.0, 500, gb_audio_track_tone::NOISE );
        if ( u16_buttons & gb_buttons::KEY_RIGHT ) 
            track_fx.play_fx( track_my_music, count_of(track_my_music) );

        player.pool();                                      // generate samples for both tracks
        core.pool();                                        // update back system updates
        core.delay_ms(20);                                  // optional delay : no display in this example.
    }
}
