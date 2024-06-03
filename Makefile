CPP = g++
SRC = ./src/
SOURCES = main.cpp application.cpp window.cpp log.cpp global_events.cpp monitor.cpp window_events.cpp image.cpp stb_image.cpp key_events.cpp key_input.cpp key_combo.cpp mouse_events.cpp mouse_input.cpp controller_input.cpp controller_events.cpp timing.cpp clipboard.cpp
OBJECTS = $(SOURCES:.cpp=.o)
CFLAGS=
LIBS=-L ./libs/glfw-3.4/lib-mingw-w64 -L ./libs/glew-2.1.0/lib/Release/x64 -L ./libs/glm/lib -lglfw3 -lglew32 -lopengl32 -lglm -lgdi32
HEADERS= -I src/ -I ./libs/glfw-3.4/include -I ./libs/glew-2.1.0/include -I ./libs/glm/include -I ./libs/stb

%.o: $(SRC)%.cpp
	$(CPP) -o $@ -c $< $(HEADERS)

exe: $(OBJECTS)
	$(CPP) $(CFLAGS) -o $@ $(OBJECTS) $(LIBS)

clean:
	@rm -f exe.exe *.o
	@echo "cleaning done"
