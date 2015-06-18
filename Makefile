all:
	gcc arrowkey.c -lSDL -lSDL_ttf -o arrowkey

install:
	cp arrowkey /usr/local/bin/arrowkey
