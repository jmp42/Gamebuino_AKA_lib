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

##gb_audio_track_wav
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
