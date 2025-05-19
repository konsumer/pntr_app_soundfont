This will let you load soundfonts & midi files in [pntr_app](https://github.com/robloach/pntr_app), using [TinySoundFont](https://github.com/schellingb/TinySoundFont).

it supports sf2, sf3, and sfo files for soundfont, and midi files for score.

I have included [an example](example). You can build it with this:

```
cd example
cmake -DCMAKE_BUILD_TYPE=Release -B build
cmake --build build
```

## API

```c
// SOUNDFONT

// Loading/initialization functions
pntr_soundfont *pntr_app_soundfont_load_default(pntr_app *app);
pntr_soundfont *pntr_app_soundfont_load(pntr_app *app, const char *filename);
pntr_soundfont *pntr_app_soundfont_load_memory(pntr_app *app, const void *buffer, int size);
pntr_soundfont *pntr_app_soundfont_copy(pntr_soundfont *f);
void pntr_app_soundfont_unload(pntr_soundfont *f);
void pntr_app_soundfont_reset(pntr_soundfont *f);

// Preset management
int pntr_app_soundfont_get_presetindex(const pntr_soundfont *f, int bank, int preset_number);
int pntr_app_soundfont_get_presetcount(const pntr_soundfont *f);
const char *pntr_app_soundfont_get_presetname(const pntr_soundfont *f, int preset_index);
const char *pntr_app_soundfont_bank_get_presetname(const pntr_soundfont *f, int bank, int preset_number);

// Direct note control
int pntr_app_soundfont_note_on(pntr_soundfont *f, int preset_index, int key, float vel);
int pntr_app_soundfont_bank_note_on(pntr_soundfont *f, int bank, int preset_number, int key, float vel);
void pntr_app_soundfont_note_off(pntr_soundfont *f, int preset_index, int key);
int pntr_app_soundfont_bank_note_off(pntr_soundfont *f, int bank, int preset_number, int key);
void pntr_app_soundfont_note_off_all(pntr_soundfont *f);
int pntr_app_soundfont_active_voice_count(pntr_soundfont *f);

// Channel settings
int pntr_app_soundfont_channel_set_presetindex(pntr_soundfont *f, int channel, int preset_index);
int pntr_app_soundfont_channel_set_presetnumber(pntr_soundfont *f, int channel, int preset_number, int flag_mididrums);
int pntr_app_soundfont_channel_set_bank(pntr_soundfont *f, int channel, int bank);
int pntr_app_soundfont_channel_set_bank_preset(pntr_soundfont *f, int channel, int bank, int preset_number);
int pntr_app_soundfont_channel_set_pan(pntr_soundfont *f, int channel, float pan);
int pntr_app_soundfont_channel_set_volume(pntr_soundfont *f, int channel, float volume);
int pntr_app_soundfont_channel_set_pitchwheel(pntr_soundfont *f, int channel, int pitch_wheel);
int pntr_app_soundfont_channel_set_pitchrange(pntr_soundfont *f, int channel, float pitch_range);
int pntr_app_soundfont_channel_set_tuning(pntr_soundfont *f, int channel, float tuning);
int pntr_app_soundfont_channel_set_sustain(pntr_soundfont *f, int channel, int flag_sustain);

// Channel note control
int pntr_app_soundfont_channel_note_on(pntr_soundfont *f, int channel, int key, float vel);
void pntr_app_soundfont_channel_note_off(pntr_soundfont *f, int channel, int key);
void pntr_app_soundfont_channel_note_off_all(pntr_soundfont *f, int channel);
void pntr_app_soundfont_channel_sounds_off_all(pntr_soundfont *f, int channel);

// MIDI control
int pntr_app_soundfont_channel_midi_control(pntr_soundfont *f, int channel, int controller, int control_value);

// Channel getters
int pntr_app_soundfont_channel_get_preset_index(pntr_soundfont *f, int channel);
int pntr_app_soundfont_channel_get_preset_bank(pntr_soundfont *f, int channel);
int pntr_app_soundfont_channel_get_preset_number(pntr_soundfont *f, int channel);
float pntr_app_soundfont_channel_get_pan(pntr_soundfont *f, int channel);
float pntr_app_soundfont_channel_get_volume(pntr_soundfont *f, int channel);
int pntr_app_soundfont_channel_get_pitchwheel(pntr_soundfont *f, int channel);
float pntr_app_soundfont_channel_get_pitchrange(pntr_soundfont *f, int channel);
float pntr_app_soundfont_channel_get_tuning(pntr_soundfont *f, int channel);

// MIDI FILE

// Loading/initialization functions
pntr_app_midi *pntr_app_midi_load_memory(const void *buffer, int size);
pntr_app_midi *pntr_app_midi_load(const char *filename);
void pntr_app_midi_unload(pntr_app_midi *midi);

// MIDI message information
int pntr_app_midi_get_info(pntr_app_midi *first_message, int *used_channels, int *used_programs, int *total_notes, unsigned int *time_first_note, unsigned int *time_length);
int pntr_app_midi_get_tempo_value(pntr_app_midi *set_tempo_message);

// Player functions
pntr_app_midi_player *pntr_app_midi_player_load(pntr_soundfont *soundfont, pntr_app_midi* midi);
pntr_app_midi_player *pntr_app_midi_play(pntr_app_midi_player* player);
void pntr_app_midi_stop(pntr_app_midi_player *player);
void pntr_app_midi_player_unload(pntr_app_midi_player *player);
```
