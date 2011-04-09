CXX=g++
CC=g++
CXXFLAGS=
LDFLAGS=
BINDIR=/usr/local/bin
MANDIR=/usr/local/man/man1

all: kitty kittychk

kitty: kitty.o kitty_types.o

meow: meow.o kitty_types.o

kitty.o: kitty.cpp kitty_types.h

meow.o: meow.cpp kitty_types.h

kitty_types.o: kitty_types.cpp

clean:
	rm -f kitty.o meow.o kitty_types.o kitty meow

install: kitty meow
	install -c -o ${OWNER} -g ${GROUP} -m 755 kitty ${BINDIR}
	install -c -o ${OWNER} -g ${GROUP} -m 755 meow ${BINDIR}
	install -c -o ${OWNER} -g ${GROUP} -m 644 kitty.man ${MANDIR}/kitty.1
	install -c -o ${OWNER} -g ${GROUP} -m 644 meow.man ${MANDIR}/meow.1

