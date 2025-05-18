#define PNTR_APP_IMPLEMENTATION
#define PNTR_ENABLE_DEFAULT_FONT
#include "pntr_app.h"

#define PNTR_APP_SOUNDFONT_IMPLEMENTATION
#include "pntr_app_soundfont.h"

typedef struct AppData {
  pntr_font *font;
} AppData;

bool Init(pntr_app *app) {
  AppData *appData = pntr_load_memory(sizeof(AppData));
  pntr_app_set_userdata(app, appData);

  appData->font = pntr_load_font_default();

  return true;
}

bool Update(pntr_app *app, pntr_image *screen) {
  AppData *appData = (AppData *)pntr_app_userdata(app);
  pntr_clear_background(screen, PNTR_RAYWHITE);

  pntr_draw_text(screen, appData->font, "Testing soundfont.", 100, 100,
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
