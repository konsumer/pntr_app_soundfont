#define PNTR_APP_IMPLEMENTATION
#define PNTR_ENABLE_DEFAULT_FONT
#include "pntr_app.h"

#define PNTR_APP_SOUNDFONT_IMPLEMENTATION
#define PNTR_APP_ENABLE_DEFAULT_SOUNDFONT
#include "pntr_app_soundfont.h"

// this is a very simple midi-file loader
#define TML_IMPLEMENTATION
#include "tml.h"

typedef struct AppData {
  pntr_font *font;
  pntr_soundfont *soundfont;

  double g_Msec;              // current playback time
  tml_message *g_MidiMessage; // next message to be played
} AppData;

bool Init(pntr_app *app) {
  AppData *appData = pntr_load_memory(sizeof(AppData));
  pntr_app_set_userdata(app, appData);

  appData->font = pntr_load_font_default();
  appData->soundfont = pntr_load_soundfont_default();

  // Initialize preset on special 10th MIDI channel to use percussion sound bank
  // (128) if available
  pntr_app_soundfont_channel_set_bank_preset(appData->soundfont, 9, 128, 0);

  tml_message *TinyMidiLoader = NULL;
  TinyMidiLoader = tml_load_filename("venture.mid");
  if (!TinyMidiLoader) {
    fprintf(stderr, "Could not load MIDI file\n");
    return false;
  }

  appData->g_MidiMessage = TinyMidiLoader;

  return true;
}

bool Update(pntr_app *app, pntr_image *screen) {
  AppData *appData = (AppData *)pntr_app_userdata(app);
  pntr_clear_background(screen, PNTR_RAYWHITE);

  pntr_draw_text(screen, appData->font, "You should hear music playing.", 80,
                 100, PNTR_BLACK);
  pntr_draw_text(screen, appData->font, "If not, click on window.", 100, 120,
                 PNTR_BLACK);

  return true;
}

void Close(pntr_app *app) {
  AppData *appData = (AppData *)pntr_app_userdata(app);
  pntr_unload_font(appData->font);
  pntr_unload_memory(appData);
}

void Event(pntr_app *app, pntr_app_event *event) {
  AppData *appData = (AppData *)pntr_app_userdata(app);
}

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
                    .fps = 0};
}
