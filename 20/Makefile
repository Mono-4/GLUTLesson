LDLIBS = -L/usr/X11R6/lib -lglut -lGLU -lGL -lXmu -lXi -lXext -lX11 -lpthread -lm
TARGETS = a.out
OBJECTS = main.o checkmatrix.o showguide.o trackball.o
CXXFLAGS = "-w"

$(TARGETS): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS) $(LDLIBS)

main.o: checkmatrix.h showguide.h
checkmatrix.o: checkmatrix.h
showguide.o: showguide.h
trackball.o: trackball.h

clean:
	-rm -f $(TARGETS) *.o *~
