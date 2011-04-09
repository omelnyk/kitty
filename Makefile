CXX=c++
CXXFLAGS=

kitty: kitty.o kitty_types.o
	${CXX} kitty.o kitty_types.o -o kitty

kittychk: kittychk.o kity_types.o
	${CXX} kittychk.o kitty_types.o -o kittychk

kitty.o: kitty.cpp kitty_types.h
	${CXX} ${CXXFLAGS} -c kitty.cpp -o kitty.o

kittychk.o: kittychk.cpp kitty_types.h
	${CXX} ${CXXFLAGS} -c kittychk.cpp -o kittychk.o

kitty_types.o: kitty_types.cpp
	${CXX} ${CXXFLAGS} -c kitty_types.cpp -o kitty_types.o
