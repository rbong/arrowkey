FONT    = $$(fc-match -f "%{file[0]}")
FONT_CL = "{ 0xFF, 0xFF, 0xFF }" 
BCKGRND = 0xEEEEEE
KEYS_NH = 0xCCCCD0
SHIF_NH = 0xB8B8C0
CAPS_NH = 0xA8A8B0
KEYS_HI = 0xB0B0B8
SHIF_HI = 0xA8A8B0
CAPS_HI = 0x9898A0
DEF     = -D FONT="\"$(FONT)\"" -D FONT_CL=$(FONT_CL) -D BCKGRND=$(BCKGRND) -D KEYS_NH=$(KEYS_NH) -D SHIF_NH=$(SHIF_NH) -D CAPS_NH=$(CAPS_NH) -D KEYS_HI=$(KEYS_HI) -D SHIF_HI=$(SHIF_HI) -D CAPS_HI=$(CAPS_HI)

all:
	gcc $(DEF) arrowkey.c -lSDL -lSDL_ttf -o arrowkey

install:
	cp arrowkey /usr/local/bin/arrowkey
