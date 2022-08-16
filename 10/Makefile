LDLIBS = -L/usr/X11R6/lib -lglut -lGLU -lGL -lXmu -lXi -lXext -lX11 -lpthread -lm
TARGETS = a.out
OBJECTS = main.o checkMatrix.o showGuide.o
CFLAGS = "-w"

$(TARGETS): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDLIBS)

main.o: checkMatrix.h showGuide.h
checkMatrix.o: checkMatrix.h
showGuide.o: showGuide.h

clean:
	-rm -f $(TARGETS) *.o *~
