OBJECTS=compose.o main.o message.o message_printer.o header_view.o header_view_impl.o compose_impl.o
CPP=ccache g++
CPPFLAGS=`pkg-config gtkmm-2.4 --cflags` -DNDEBUG -O3 -Wall
LDFLAGS=`pkg-config gtkmm-2.4 --libs`
DEBUG_OBJECTS=$(OBJECTS:.o=.debug.o)
DEBUG_CPPFLAGS=`pkg-config gtkmm-2.4 --cflags` -ggdb -Wall

compose: $(OBJECTS)
	$(CPP) $(OBJECTS) -o compose $(LDFLAGS)

%.d: %.cpp 
	$(CPP) -MM $< -MF $@ -MT $(@:.d=.o)\ $@\ $(@:.d=.debug.o)

include $(OBJECTS:.o=.d)

clean:
	rm -f *.d
	rm -f *.o
	rm -f compose

%.o:
	$(CPP) $(CPPFLAGS) -c $< -o $@

%.debug.o:
	$(CPP) $(DEBUG_CPPFLAGS) -c $< -o $@

compose.debug: $(DEBUG_OBJECTS)
	$(CPP) -ggdb $(DEBUG_OBJECTS) -o compose.debug $(LDFLAGS)