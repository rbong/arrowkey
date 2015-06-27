# arrowkey

![screen](https://raw.github.com/rbong/arrowkey/master/images/screen.png)

arrowkey is a quick SDL/C program written as a virtual keyboard for remotes.
An example of piping its output using xdotool can be found in example.sh
arrowkey is for Linux, but could be easily ported.

The default font according to fontconfig is used. This can be changed within
the Makefile.

The colours can also be changed within the Makefile.

# dependencies

- SDL
- SDL\_ttf
- fontconfig

# installation

```
$ make
$ make install
```

# running

```
$ arrowkey
```

# controls

- up,down,left,right: control the position of the cursor
- space: enter keys
- backspace: output the backspace key
- esc/return: exit arrowkey
