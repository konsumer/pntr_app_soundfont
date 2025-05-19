This will let you load soundfonts & midi files in [pntr_app](https://github.com/robloach/pntr_app), using [TinySoundFont](https://github.com/schellingb/TinySoundFont).

it supports sf2, sf3, and sfo files for soundfont, and midi files for score.

Basic usage looks like this:

```c
#define PNTR_APP_SOUNDFONT_IMPLEMENTATION
#define PNTR_APP_ENABLE_DEFAULT_SOUNDFONT
#include "pntr_app_soundfont.h"

#define PNTR_APP_MIDI_IMPLEMENTATION
#include "pntr_app_midi.h"

static pntr_app_soundfont* soundfont;
static pntr_app_midi* midi;

// INIT
soundfont = pntr_app_soundfont_load_default();
// or
soundfont = pntr_app_soundfont_load("cool.sf2");

midi = pntr_app_midi_load("cool.mid");
pntr_app_midi_play(app, soundfont, midi);


// CLOSE
pntr_app_midi_stop(midi);
pntr_app_midi_unload(midi);
pntr_app_soundfont_unload(soundfont);
```

I have included [an example](example), too. You can build it with this:

```
cd example
cmake -B build
cmake --build build
```

## API

```c
// TODO
```
