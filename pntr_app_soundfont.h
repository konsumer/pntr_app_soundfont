#ifndef PNTR_APP_SOUNDFONT_H__
#define PNTR_APP_SOUNDFONT_H__

#ifdef PNTR_APP_SOUNDFONT_IMPLEMENTATION
#define TSF_IMPLEMENTATION
#endif // PNTR_APP_SOUNDFONT_IMPLEMENTATION

#include "pntr.h"
#include "tsf.h"

typedef tsf pntr_soundfont;

// Loading/initialization functions
pntr_soundfont *pntr_load_soundfont_default(void);
pntr_soundfont *pntr_app_soundfont_load(const char *filename);
pntr_soundfont *pntr_app_soundfont_load_memory(const void *buffer, int size);
pntr_soundfont *pntr_app_soundfont_copy(pntr_soundfont *f);
void pntr_app_soundfont_close(pntr_soundfont *f);
void pntr_app_soundfont_reset(pntr_soundfont *f);

// Preset management
int pntr_app_soundfont_get_presetindex(const pntr_soundfont *f, int bank,
                                       int preset_number);
int pntr_app_soundfont_get_presetcount(const pntr_soundfont *f);
const char *pntr_app_soundfont_get_presetname(const pntr_soundfont *f,
                                              int preset_index);
const char *pntr_app_soundfont_bank_get_presetname(const pntr_soundfont *f,
                                                   int bank, int preset_number);

// Output settings
void pntr_app_soundfont_set_output(pntr_soundfont *f,
                                   enum TSFOutputMode outputmode,
                                   int samplerate, float global_gain_db);
void pntr_app_soundfont_set_volume(pntr_soundfont *f, float global_gain);
int pntr_app_soundfont_set_max_voices(pntr_soundfont *f, int max_voices);

// Direct note control
int pntr_app_soundfont_note_on(pntr_soundfont *f, int preset_index, int key,
                               float vel);
int pntr_app_soundfont_bank_note_on(pntr_soundfont *f, int bank,
                                    int preset_number, int key, float vel);
void pntr_app_soundfont_note_off(pntr_soundfont *f, int preset_index, int key);
int pntr_app_soundfont_bank_note_off(pntr_soundfont *f, int bank,
                                     int preset_number, int key);
void pntr_app_soundfont_note_off_all(pntr_soundfont *f);
int pntr_app_soundfont_active_voice_count(pntr_soundfont *f);

// Audio rendering
void pntr_app_soundfont_render_short(pntr_soundfont *f, short *buffer,
                                     int samples, int flag_mixing);
void pntr_app_soundfont_render_float(pntr_soundfont *f, float *buffer,
                                     int samples, int flag_mixing);

// Channel settings
int pntr_app_soundfont_channel_set_presetindex(pntr_soundfont *f, int channel,
                                               int preset_index);
int pntr_app_soundfont_channel_set_presetnumber(pntr_soundfont *f, int channel,
                                                int preset_number,
                                                int flag_mididrums);
int pntr_app_soundfont_channel_set_bank(pntr_soundfont *f, int channel,
                                        int bank);
int pntr_app_soundfont_channel_set_bank_preset(pntr_soundfont *f, int channel,
                                               int bank, int preset_number);
int pntr_app_soundfont_channel_set_pan(pntr_soundfont *f, int channel,
                                       float pan);
int pntr_app_soundfont_channel_set_volume(pntr_soundfont *f, int channel,
                                          float volume);
int pntr_app_soundfont_channel_set_pitchwheel(pntr_soundfont *f, int channel,
                                              int pitch_wheel);
int pntr_app_soundfont_channel_set_pitchrange(pntr_soundfont *f, int channel,
                                              float pitch_range);
int pntr_app_soundfont_channel_set_tuning(pntr_soundfont *f, int channel,
                                          float tuning);
int pntr_app_soundfont_channel_set_sustain(pntr_soundfont *f, int channel,
                                           int flag_sustain);

// Channel note control
int pntr_app_soundfont_channel_note_on(pntr_soundfont *f, int channel, int key,
                                       float vel);
void pntr_app_soundfont_channel_note_off(pntr_soundfont *f, int channel,
                                         int key);
void pntr_app_soundfont_channel_note_off_all(pntr_soundfont *f, int channel);
void pntr_app_soundfont_channel_sounds_off_all(pntr_soundfont *f, int channel);

// MIDI control
int pntr_app_soundfont_channel_midi_control(pntr_soundfont *f, int channel,
                                            int controller, int control_value);

// Channel getters
int pntr_app_soundfont_channel_get_preset_index(pntr_soundfont *f, int channel);
int pntr_app_soundfont_channel_get_preset_bank(pntr_soundfont *f, int channel);
int pntr_app_soundfont_channel_get_preset_number(pntr_soundfont *f,
                                                 int channel);
float pntr_app_soundfont_channel_get_pan(pntr_soundfont *f, int channel);
float pntr_app_soundfont_channel_get_volume(pntr_soundfont *f, int channel);
int pntr_app_soundfont_channel_get_pitchwheel(pntr_soundfont *f, int channel);
float pntr_app_soundfont_channel_get_pitchrange(pntr_soundfont *f, int channel);
float pntr_app_soundfont_channel_get_tuning(pntr_soundfont *f, int channel);

#endif // PNTR_APP_SOUNDFONT_H__

#ifdef PNTR_APP_SOUNDFONT_IMPLEMENTATION
#ifndef PNTR_APP_SOUNDFONT_IMPLEMENTATION_ONCE
#define PNTR_APP_SOUNDFONT_IMPLEMENTATION_ONCE

pntr_soundfont *pntr_load_soundfont_default(void) {
#ifdef PNTR_APP_DEFAULT_SOUNDFONT
  return PNTR_APP_DEFAULT_SOUNDFONT();
#elif defined(PNTR_APP_ENABLE_DEFAULT_SOUNDFONT)
#include "casio_ctx230_sfo.h"
  return pntr_app_soundfont_load_memory(casio_ctx230_sfo,
                                        sizeof(casio_ctx230_sfo));
#endif
}
// Loading/initialization implementations
pntr_soundfont *pntr_app_soundfont_load(const char *filename) {
  unsigned int bytesRead;
  unsigned char *data = pntr_load_file(filename, &bytesRead);
  if (!data)
    return NULL;
  pntr_soundfont *result = tsf_load_memory(data, bytesRead);
  free(data);
  return result;
}

pntr_soundfont *pntr_app_soundfont_load_memory(const void *buffer, int size) {
  return tsf_load_memory(buffer, size);
}

pntr_soundfont *pntr_app_soundfont_copy(pntr_soundfont *f) {
  return tsf_copy(f);
}

void pntr_app_soundfont_close(pntr_soundfont *f) { tsf_close(f); }

void pntr_app_soundfont_reset(pntr_soundfont *f) { tsf_reset(f); }

// Preset management implementations
int pntr_app_soundfont_get_presetindex(const pntr_soundfont *f, int bank,
                                       int preset_number) {
  return tsf_get_presetindex(f, bank, preset_number);
}

int pntr_app_soundfont_get_presetcount(const pntr_soundfont *f) {
  return tsf_get_presetcount(f);
}

const char *pntr_app_soundfont_get_presetname(const pntr_soundfont *f,
                                              int preset_index) {
  return tsf_get_presetname(f, preset_index);
}

const char *pntr_app_soundfont_bank_get_presetname(const pntr_soundfont *f,
                                                   int bank,
                                                   int preset_number) {
  return tsf_bank_get_presetname(f, bank, preset_number);
}

// Output settings implementations
void pntr_app_soundfont_set_output(pntr_soundfont *f,
                                   enum TSFOutputMode outputmode,
                                   int samplerate, float global_gain_db) {
  tsf_set_output(f, outputmode, samplerate, global_gain_db);
}

void pntr_app_soundfont_set_volume(pntr_soundfont *f, float global_gain) {
  tsf_set_volume(f, global_gain);
}

int pntr_app_soundfont_set_max_voices(pntr_soundfont *f, int max_voices) {
  return tsf_set_max_voices(f, max_voices);
}

// Direct note control implementations
int pntr_app_soundfont_note_on(pntr_soundfont *f, int preset_index, int key,
                               float vel) {
  return tsf_note_on(f, preset_index, key, vel);
}

int pntr_app_soundfont_bank_note_on(pntr_soundfont *f, int bank,
                                    int preset_number, int key, float vel) {
  return tsf_bank_note_on(f, bank, preset_number, key, vel);
}

void pntr_app_soundfont_note_off(pntr_soundfont *f, int preset_index, int key) {
  tsf_note_off(f, preset_index, key);
}

int pntr_app_soundfont_bank_note_off(pntr_soundfont *f, int bank,
                                     int preset_number, int key) {
  return tsf_bank_note_off(f, bank, preset_number, key);
}

void pntr_app_soundfont_note_off_all(pntr_soundfont *f) { tsf_note_off_all(f); }

int pntr_app_soundfont_active_voice_count(pntr_soundfont *f) {
  return tsf_active_voice_count(f);
}

// Audio rendering implementations
void pntr_app_soundfont_render_short(pntr_soundfont *f, short *buffer,
                                     int samples, int flag_mixing) {
  tsf_render_short(f, buffer, samples, flag_mixing);
}

void pntr_app_soundfont_render_float(pntr_soundfont *f, float *buffer,
                                     int samples, int flag_mixing) {
  tsf_render_float(f, buffer, samples, flag_mixing);
}

// Channel settings implementations
int pntr_app_soundfont_channel_set_presetindex(pntr_soundfont *f, int channel,
                                               int preset_index) {
  return tsf_channel_set_presetindex(f, channel, preset_index);
}

int pntr_app_soundfont_channel_set_presetnumber(pntr_soundfont *f, int channel,
                                                int preset_number,
                                                int flag_mididrums) {
  return tsf_channel_set_presetnumber(f, channel, preset_number,
                                      flag_mididrums);
}

int pntr_app_soundfont_channel_set_bank(pntr_soundfont *f, int channel,
                                        int bank) {
  return tsf_channel_set_bank(f, channel, bank);
}

int pntr_app_soundfont_channel_set_bank_preset(pntr_soundfont *f, int channel,
                                               int bank, int preset_number) {
  return tsf_channel_set_bank_preset(f, channel, bank, preset_number);
}

int pntr_app_soundfont_channel_set_pan(pntr_soundfont *f, int channel,
                                       float pan) {
  return tsf_channel_set_pan(f, channel, pan);
}

int pntr_app_soundfont_channel_set_volume(pntr_soundfont *f, int channel,
                                          float volume) {
  return tsf_channel_set_volume(f, channel, volume);
}

int pntr_app_soundfont_channel_set_pitchwheel(pntr_soundfont *f, int channel,
                                              int pitch_wheel) {
  return tsf_channel_set_pitchwheel(f, channel, pitch_wheel);
}

int pntr_app_soundfont_channel_set_pitchrange(pntr_soundfont *f, int channel,
                                              float pitch_range) {
  return tsf_channel_set_pitchrange(f, channel, pitch_range);
}

int pntr_app_soundfont_channel_set_tuning(pntr_soundfont *f, int channel,
                                          float tuning) {
  return tsf_channel_set_tuning(f, channel, tuning);
}

int pntr_app_soundfont_channel_set_sustain(pntr_soundfont *f, int channel,
                                           int flag_sustain) {
  return tsf_channel_set_sustain(f, channel, flag_sustain);
}

// Channel note control implementations
int pntr_app_soundfont_channel_note_on(pntr_soundfont *f, int channel, int key,
                                       float vel) {
  return tsf_channel_note_on(f, channel, key, vel);
}

void pntr_app_soundfont_channel_note_off(pntr_soundfont *f, int channel,
                                         int key) {
  tsf_channel_note_off(f, channel, key);
}

void pntr_app_soundfont_channel_note_off_all(pntr_soundfont *f, int channel) {
  tsf_channel_note_off_all(f, channel);
}

void pntr_app_soundfont_channel_sounds_off_all(pntr_soundfont *f, int channel) {
  tsf_channel_sounds_off_all(f, channel);
}

// MIDI control implementation
int pntr_app_soundfont_channel_midi_control(pntr_soundfont *f, int channel,
                                            int controller, int control_value) {
  return tsf_channel_midi_control(f, channel, controller, control_value);
}

// Channel getters implementations
int pntr_app_soundfont_channel_get_preset_index(pntr_soundfont *f,
                                                int channel) {
  return tsf_channel_get_preset_index(f, channel);
}

int pntr_app_soundfont_channel_get_preset_bank(pntr_soundfont *f, int channel) {
  return tsf_channel_get_preset_bank(f, channel);
}

int pntr_app_soundfont_channel_get_preset_number(pntr_soundfont *f,
                                                 int channel) {
  return tsf_channel_get_preset_number(f, channel);
}

float pntr_app_soundfont_channel_get_pan(pntr_soundfont *f, int channel) {
  return tsf_channel_get_pan(f, channel);
}

float pntr_app_soundfont_channel_get_volume(pntr_soundfont *f, int channel) {
  return tsf_channel_get_volume(f, channel);
}

int pntr_app_soundfont_channel_get_pitchwheel(pntr_soundfont *f, int channel) {
  return tsf_channel_get_pitchwheel(f, channel);
}

float pntr_app_soundfont_channel_get_pitchrange(pntr_soundfont *f,
                                                int channel) {
  return tsf_channel_get_pitchrange(f, channel);
}

float pntr_app_soundfont_channel_get_tuning(pntr_soundfont *f, int channel) {
  return tsf_channel_get_tuning(f, channel);
}

#endif // PNTR_APP_SOUNDFONT_IMPLEMENTATION_ONCE
#endif // PNTR_APP_SOUNDFONT_IMPLEMENTATION
