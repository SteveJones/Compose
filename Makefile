OBJECTS=compose.o main.o message.o

CPPFLAGS=`pkg-config gtkmm-2.4 --cflags` -DNDEBUG -O3 -Wall
LDFLAGS=`pkg-config gtkmm-2.4 --libs`
DEBUG_OBJECTS=$(OBJECTS:.o=.debug.o)
DEBUG_CPPFLAGS=`pkg-config gtkmm-2.4 --cflags` -ggdb -Wall

all: compose

%.d: %.cpp 
	g++ -MM $< -MF $@

include $(OBJECTS:.o=.d)

clean:
	rm -f *.d
	rm -f *.o
	rm -f compose

compose: $(OBJECTS)
	g++ $(OBJECTS) -o compose $(LDFLAGS)

%.debug.o: %.cpp %.o
	g++ $(DEBUG_CPPFLAGS) -c $< -o $@

compose.debug: $(DEBUG_OBJECTS)
	g++ -ggdb $(DEBUG_OBJECTS) -o compose.debug $(LDFLAGS)