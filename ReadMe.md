# Gamebuino AKA library


## Gamebuino AKA sound library
The Gamebuino AKA sound library allow to play various type of sounds : WAV, PMF, FMSynth
Audio is composed of 2 layers : the gb_audio_player, and various gb_audio_track_xxx for different types of sound.


### gb_audio_player
gb_audio_player is the low level sound library.

void set_master_volume( uint8_t u8_volume ) : set volume to 0 (mute) to 255 (max)
uint8_t get_master_volume() : return current volume
void vibrator( uint32_t u32_delay_ms ) : start vibrator for requested delay in milliseconds. call with 0 to stop 
int add_track( gb_audio_track_base* track, float f32_volume = 1.0f ) : add a track type to player
int del_track( gb_audio_track_base* track ) : remove a track from player
void pool() : update track objects ( generate sound samples )

### gb_audio_track_wav
Allow to play WAV file from SDCard or ESP memory
WAV files must be signed 16 bits, mono channel, and 44100 Hz frequency.

```cpp
#include "gb_core.h"
#include "gb_audio_player.h"        // main player
#include "gb_audio_track_wav.h"     // wav player
#include "assets/WAV_SYSTEM.h"      //!< embedded Gamebuino system sound : gb_wav_system_xxx

gb_core core;                       // Gamebuino core lib
gb_audio_player player;             // main audio player 
gb_audio_track_wav  track_wav1;     // 1st WAV track : play a system sound
gb_audio_track_wav  track_wav2;     // 2nd WAV track : play for SDcard
gb_audio_track_wav  track_wav3;     // 3th WAV track : play my custom wav fx

const uint8_t u8_my_custom_wav[] = {
    #include "assets/wav/kick.wav.h"
};

extern "C" void app_main(void)
{
    core.init();                                            // initialize the Gamebuino
    player.set_master_volume(255);                          // set the volume to almost max ( up to 255 )
    player.add_track(&track_wav1);                          // add a 1st WAV track to player
    player.add_track(&track_wav2);                          // add a 2nd WAV track to player
    player.add_track(&track_wav3);                          // add the last track : my wav
    track_wav1.set_track_volume(0.5);                       // fix volume for this track to 50%
    track_wav2.set_track_volume(1.0);                       // fix volume for this track to 100%
    track_wav3.set_track_volume(0.75);                      // fix volume for this track to 75%

    track_wav2.play_wav( MOUNT_POINT"/pacman.wav" );        // Start playing the WAV from SDCard : need to place au wav file "example.wav"

    for ( int iLoop = 0 ; ; iLoop++ )
    {
        if  ( ( iLoop % 100 ) == 0 )                        // 2 sec modulo time
            track_wav1.play_wav( gb_wav_system_explode );   // play my custom wav at t0+0s
        if  ( ( iLoop % 100 ) == 50 )                       // 2 sec modulo time
            track_wav3.play_wav( u8_my_custom_wav );        // play my custom wav at t0+1s
        player.pool();                                      // generate samples for both tracks
        core.pool();                                        // update back system updates
        core.delay_ms(20);                                  // optional delay : no display in this example.
    }
}
```

### gb_audio_track_tone 
gb_audio_track_tone allow to play simple waveform.

void play_tone( float f32_frequency, float f32_volume, uint16_t u16_duration_ms, tone_type type = SINE )
start playing sound for frequency(Hz), volume (0.0 to 1.0), and duration(ms). waveform can be  SINE, SQUARE, TRIANGLE or NOISE.
      
void play_tone( float f32_start_frequency, float f32_end_frequency, float f32_start_volume,  float f32_end_volume, uint16_t u16_duration_ms, tone_type fx_type = SINE )
start playing sound for duration(ms) and frequency(Hz) with effect on freq and volume. Note : volume range 0.0 to 1.0

### gb_audio_track_fx
gb_audio_track_fx allow to play waveform array.

void play_fx( const gb_audio_track_fx_t* fx_array, size_t fx_count ) : Start playing sound for duration(ms) and frequency(Hz)

```cpp
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
        if ( u16_buttons & GB_KEY_A )
            track_fx.play_fx( gb_fx_system_ok, count_of(gb_fx_system_ok) );
        if ( u16_buttons & GB_KEY_B )
            track_fx.play_fx( gb_fx_system_ko, count_of(gb_fx_system_ko) );
        if ( u16_buttons & GB_KEY_C )
            track_fx.play_fx( gb_fx_system_tick, count_of(gb_fx_system_tick) );
        if ( u16_buttons & GB_KEY_D )
            track_fx.play_fx( gb_fx_system_explode, count_of(gb_fx_system_explode) );

            // simple tone
        if (u16_buttons&GB_KEY_UP)   
            track_tone.play_tone( 600, 800, 0.0, 1.0, 250, gb_audio_track_tone::SINE );
        if (u16_buttons&GB_KEY_DOWN) 
            track_tone.play_tone( 440, 220, 1.0, 0.0, 100, gb_audio_track_tone::SQUARE );
        if (u16_buttons&GB_KEY_LEFT) 
            track_tone.play_tone( 220, 220, 1.0, 0.0, 500, gb_audio_track_tone::NOISE );
        if (u16_buttons&GB_KEY_RIGHT) 
            track_fx.play_fx( track_my_music, count_of(track_my_music) );

        player.pool();                                      // generate samples for both tracks
        core.pool();                                        // update back system updates
        core.delay_ms(20);                                  // optional delay : no display in this example.
    }
}

```

### gb_audio_track_pmf
gb_audio_track_pmf allow to play a pmf data from MCU memory.
pmf file can be generated with the pmf_converter.exe
eg : pmf_converter.exe -i <input_file.mod> -o <output_file.h> -c -ch 4 -hex
the binary stream datra can be simply embeeded into the binaty app with sequence like this :
```cpp
const uint8_t my_pmf_data[] = {
    #include output_file.h
};

```


```cpp
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
```


