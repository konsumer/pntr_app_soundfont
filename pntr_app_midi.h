#ifndef PNTR_APP_MIDI_H__
#define PNTR_APP_MIDI_H__

#ifdef PNTR_APP_MIDI_IMPLEMENTATION
#define TML_IMPLEMENTATION
#endif // PNTR_APP_MIDI_IMPLEMENTATION

#include "pntr.h"
#include "pntr_app_soundfont.h"
#include "tml.h"

typedef tml_message pntr_app_midi;

typedef struct {
  pntr_app *app;
  pntr_soundfont *soundfont;
  pntr_app_midi *midi;
  bool playing;
  // TODO: need other stuff to track offset/etc
} pntr_app_midi_player;

// Loading/initialization functions
pntr_app_midi *pntr_app_midi_load_memory(const void *buffer, int size);
pntr_app_midi *pntr_app_midi_load(const char *filename);
void pntr_app_midi_unload(pntr_app_midi *midi);

// MIDI message information
int pntr_app_midi_get_info(pntr_app_midi *first_message, int *used_channels, int *used_programs, int *total_notes, unsigned int *time_first_note, unsigned int *time_length);
int pntr_app_midi_get_tempo_value(pntr_app_midi *set_tempo_message);

// Player functions
pntr_app_midi_player *pntr_app_midi_player_load(pntr_soundfont *soundfont, pntr_app_midi* midi);
void pntr_app_midi_player_play(pntr_app_midi_player* player);
void pntr_app_midi_player_stop(pntr_app_midi_player *player);
void pntr_app_midi_player_unload(pntr_app_midi_player *player);

// TODO: seek functions?


#endif // PNTR_APP_MIDI_H__

#ifdef PNTR_APP_MIDI_IMPLEMENTATION
#ifndef PNTR_APP_MIDI_IMPLEMENTATION_ONCE
#define PNTR_APP_MIDI_IMPLEMENTATION_ONCE

// Loading/initialization implementations
pntr_app_midi *pntr_app_midi_load(const char *filename) {
  unsigned int bytesRead;
  unsigned char *data = pntr_load_file(filename, &bytesRead);
  if (!data){
    return NULL;
  }
  pntr_app_midi *result = pntr_app_midi_load_memory(data, (int)bytesRead);
  PNTR_FREE(data);
  return result;
}

pntr_app_midi *pntr_app_midi_load_memory(const void *buffer, int size) {
  return tml_load_memory(buffer, size);
}

void pntr_app_midi_unload(pntr_app_midi *midi) {
  tml_free(midi);
}

int pntr_app_midi_get_info(pntr_app_midi *first_message, int *used_channels, int *used_programs, int *total_notes, unsigned int *time_first_note, unsigned int *time_length) {
  return tml_get_info(first_message, used_channels, used_programs, total_notes, time_first_note, time_length);
}

pntr_app_midi_player *pntr_app_midi_player_load(pntr_soundfont *soundfont, pntr_app_midi* midi) {
  pntr_app_midi_player *ret = PNTR_MALLOC(sizeof(pntr_app_midi_player));
  ret->soundfont = soundfont;
  ret->midi = midi;
  return ret;
}

void pntr_app_midi_player_unload(pntr_app_midi_player *player) {
  pntr_app_midi_player_stop(player);
  PNTR_FREE(player);
}

void pntr_app_midi_player_play(pntr_app_midi_player* player) {
  // TODO: need more here?
  player->playing = true;
}

void pntr_app_midi_player_stop(pntr_app_midi_player *player) {
  // TODO: need more here?
  player->playing = false;
}


// Tempo functions implementation
int pntr_app_midi_get_tempo_value(pntr_app_midi *set_tempo_message) {
  return tml_get_tempo_value(set_tempo_message);
}

#endif // PNTR_APP_MIDI_IMPLEMENTATION_ONCE
#endif // PNTR_APP_MIDI_IMPLEMENTATION
