This is a simple example.

Build with:

```
cmake -G Ninja -B build
cmake --build build
```

You can build for the web, too:

```
emcmake cmake -G Ninja -B build
cmake --build build
```

### sfotool

In the build, I included [sfotool](https://github.com/schellingb/TinySoundFont/tree/main/sfotool) so you can convert a soundfont:

```bash
# extract samples from sf2
./build/sfotool casio_ctx230.sf2 casio_ctx230.wav

# recompress samples
ffmpeg -i casio_ctx230.wav -c:a libvorbis casio_ctx230.ogg

# rebuild sfo
./build/sfotool casio_ctx230.sf2 casio_ctx230.ogg casio_ctx230.sfo

# generate C code
xxd -i casio_ctx230.sfo > casio_ctx230_sfo.h

# clean up
rm casio_ctx230.sf2 casio_ctx230.ogg casio_ctx230.wav casio_ctx230.sfo
```

This compressed the original soundfont about 10X. I used this to create the [embedded default soundfont](../casio_ctx230_sfo.h).
