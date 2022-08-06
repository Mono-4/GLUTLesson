LDLIBS = -L/usr/X11R6/lib -lglut -lGLU -lGL -lXmu -lXi -lXext -lX11 -lpthread -lm
TARGETS = a.out
OBJECTS = main.o
CFLAGS = "-w"

$(TARGETS): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDLIBS)

clean:
	-rm -f $(TARGETS) *.o *~
