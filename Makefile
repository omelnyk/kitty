CXX=g++
CC=g++
CXXFLAGS=-Wall
LDFLAGS=
BINDIR=/usr/local/bin
MANDIR=/usr/share/man/man1
OWNER=bin
GROUP=bin

all: src/kitty src/meow

src/kitty: src/kitty.o src/kitty_types.o

src/meow: src/meow.o src/kitty_types.o

src/kitty.o: src/kitty.cpp src/kitty_types.h

src/meow.o: src/meow.cpp src/kitty_types.h

src/kitty_types.o: src/kitty_types.cpp

clean:
	rm -f src/kitty.o src/meow.o src/kitty_types.o src/kitty src/meow

install: src/kitty src/meow
	install -c -o ${OWNER} -g ${GROUP} -m 755 src/kitty ${BINDIR}
	install -c -o ${OWNER} -g ${GROUP} -m 755 src/meow ${BINDIR}
	install -c -o ${OWNER} -g ${GROUP} -m 644 man/kitty.man ${MANDIR}/kitty.1
	install -c -o ${OWNER} -g ${GROUP} -m 644 man/meow.man ${MANDIR}/meow.1

