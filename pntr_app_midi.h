#ifndef PNTR_APP_MIDI_H__
#define PNTR_APP_MIDI_H__

#ifdef PNTR_APP_MIDI_IMPLEMENTATION
#define TML_IMPLEMENTATION
#endif // PNTR_APP_MIDI_IMPLEMENTATION

#include "pntr.h"
#include "tml.h"

typedef tml_message pntr_midi_message;

// Loading/initialization functions
pntr_midi_message *pntr_app_midi_load_memory(const void *buffer, int size);
pntr_midi_message *pntr_app_midi_load(const char *filename);
void pntr_app_midi_unload(pntr_midi_message *midi);

// MIDI message information
int pntr_app_midi_get_info(pntr_midi_message *first_message, int *used_channels,
                           int *used_programs, int *total_notes,
                           unsigned int *time_first_note,
                           unsigned int *time_length);

// Tempo functions
int pntr_app_midi_get_tempo_value(pntr_midi_message *set_tempo_message);

#endif // PNTR_APP_MIDI_H__

#ifdef PNTR_APP_MIDI_IMPLEMENTATION
#ifndef PNTR_APP_MIDI_IMPLEMENTATION_ONCE
#define PNTR_APP_MIDI_IMPLEMENTATION_ONCE

// Loading/initialization implementations
pntr_midi_message *pntr_app_midi_load(const char *filename) {
  unsigned int bytesRead;
  unsigned char *data = pntr_load_file(filename, &bytesRead);
  if (!data)
    return NULL;
  pntr_midi_message *result = pntr_app_midi_load_memory(data, (int)bytesRead);
  free(data);
  return result;
}

pntr_midi_message *pntr_app_midi_load_memory(const void *buffer, int size) {
  return tml_load_memory(buffer, size);
}

void pntr_app_midi_unload(pntr_midi_message *midi) { tml_free(midi); }

// MIDI message information implementation
int pntr_app_midi_get_info(pntr_midi_message *first_message, int *used_channels,
                           int *used_programs, int *total_notes,
                           unsigned int *time_first_note,
                           unsigned int *time_length) {
  return tml_get_info(first_message, used_channels, used_programs, total_notes,
                      time_first_note, time_length);
}

// Tempo functions implementation
int pntr_app_midi_get_tempo_value(pntr_midi_message *set_tempo_message) {
  return tml_get_tempo_value(set_tempo_message);
}

#endif // PNTR_APP_MIDI_IMPLEMENTATION_ONCE
#endif // PNTR_APP_MIDI_IMPLEMENTATION
