CPPFLAGS=`pkg-config gtkmm-2.4 --cflags`
OBJECTS=compose.o main.o message.o

all: compose

%.d: %.cpp 
	g++ -MM $< -MF $@

include $(OBJECTS:.o=.d)

clean:
	rm -f *.d
	rm -f *.o
	rm -f compose

compose: $(OBJECTS)
	g++ $(OBJECTS) -o compose `pkg-config gtkmm-2.4 --libs`


