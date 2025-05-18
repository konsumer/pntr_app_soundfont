This will let you load soundfonts in [pntr_app](https://github.com/robloach/pntr_app), using [TinySoundFont](https://github.com/schellingb/TinySoundFont).

it supports sf2, sf3, and sfo files.

Basic usage looks like this:

```c
#define PNTR_APP_SOUNDFONT_IMPLEMENTATION
#define PNTR_APP_ENABLE_DEFAULT_SOUNDFONT
#include "pntr_app_soundfont.h"

// TODO
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
