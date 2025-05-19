#define PNTR_APP_IMPLEMENTATION
#define PNTR_ENABLE_DEFAULT_FONT
#include "pntr_app.h"

#define PNTR_APP_SOUNDFONT_IMPLEMENTATION
#define PNTR_APP_ENABLE_DEFAULT_SOUNDFONT
#include "pntr_app_soundfont.h"

#define PNTR_APP_MIDI_IMPLEMENTATION
#include "pntr_app_midi.h"

static pntr_font *font;
static pntr_soundfont *soundfont;
static pntr_app_midi *midi;
static pntr_app_midi_player *midi_player;

bool Init(pntr_app *app) {
  font = pntr_load_font_default();
  soundfont = pntr_app_soundfont_load_default(app);

  // map bank 128:0 to channel 10 (drums)
  pntr_app_soundfont_channel_set_bank_preset(soundfont, 9, 128, 0);

  midi = pntr_app_midi_load("venture.mid");
  midi_player = pntr_app_midi_player_load(soundfont, midi);
  pntr_app_midi_player_play(midi_player);

  return true;
}

bool Update(pntr_app *app, pntr_image *screen) {
  pntr_clear_background(screen, PNTR_RAYWHITE);
  pntr_draw_text(screen, font, "You should hear music playing.", 80, 100, PNTR_BLACK);
  pntr_draw_text(screen, font, "If not, click on window.", 100, 120, PNTR_BLACK);

  return true;
}

void Close(pntr_app *app) {
  pntr_unload_font(font);
  pntr_app_midi_player_unload(midi_player);
  pntr_app_midi_unload(midi);
  pntr_app_soundfont_unload(soundfont);
}

void Event(pntr_app *app, pntr_app_event *event) {}

pntr_app Main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;
  return (pntr_app){.width = 400,
    .height = 225,
    .title = "pntr_app_soundfont: Example",
    .init = Init,
    .update = Update,
    .close = Close,
    .event = Event,
    .fps = 0
  };
}
