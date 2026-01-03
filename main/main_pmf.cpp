#include "gb_core.h"
#include "gb_audio_player.h"        // main player
#include "gb_audio_track_pmf.h"     // pmf player
#include "gb_audio_track_fx.h"      // fx tone player
#include "gb_audio_track_wav.h"     // wav player

#include "assets/fx_system.h"
#include "assets/WAV_SYSTEM.h"

const uint8_t u8_pmf_music_data[] = {
    #include "assets/pmf/pacman.mod.h"
};


gb_core core;                       // Gamebuino core lib
gb_audio_player     player;         // main audio player 
gb_audio_track_pmf  track_pmf;      // 1st track : a pmf player
gb_audio_track_fx   track_fx;       // 2st track : fx allow to can chain tone effects
gb_audio_track_wav  track_wav;      // 3th track : a simple WAV sound effect


extern "C" void app_main(void)
{
    core.init();                                            // initialize the Gamebuino
    player.set_master_volume(255);                          // set the volume to almost max ( up to 255 )
    player.add_track(&track_pmf);                           // add the pmf track player
    player.add_track(&track_fx);                            // add the fx track to player
    player.add_track(&track_wav);                           // add the WAV track to player

    track_pmf.load_pmf( u8_pmf_music_data );                // load the pmf to start playing later

    for ( ; ; )
    {
        uint16_t u16_buttons = core.buttons.pressed();

            // play the pmf
        if ( u16_buttons & GB_KEY_A )
            track_pmf.play_pmf();
            // stop the pmf
        if ( u16_buttons & GB_KEY_B )
            track_pmf.stop_playing();

        if ( u16_buttons & GB_KEY_C )
            track_fx.play_fx( gb_fx_system_explode, count_of(gb_fx_system_explode) );
            
        if ( u16_buttons & GB_KEY_D )
            track_wav.play_wav( gb_wav_system_laser );

        player.pool();                                      // generate samples for both tracks
        core.pool();                                        // update back system updates
        core.delay_ms(20);                                  // optional delay : no display in this example.
    }
}
