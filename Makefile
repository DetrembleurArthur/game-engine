
LIBS=-L ./libs/glfw-3.4/lib-mingw-w64 -L ./libs/glew-2.1.0/lib/Release/x64 -L ./libs/glm/lib -lglfw3 -lglew32 -lopengl32 -lglm -lgdi32
HEADERS= -I include/ -I ./libs/glfw-3.4/include -I ./libs/glew-2.1.0/include -I ./libs/glm/include -I ./libs/stb

# Nom de l'exécutable
TARGET = ge.exe

# Compilateur et options de compilation
CXX = g++
CXXFLAGS = -std=c++17

# Répertoires des fichiers source
SRCDIR = src
BUILDDIR = build
SOURCES = $(shell powershell -Command "Get-ChildItem -Recurse -Filter '*.cpp' -Name -Path $(SRCDIR)")
$(info SOURCES = $(SOURCES))
OBJECTS = $(patsubst %.cpp, $(BUILDDIR)/%.o, $(SOURCES))
$(info OBJECTS = $(OBJECTS))



# Règle par défaut
all: $(TARGET)

# Règle pour créer l'exécutable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

# Règle pour compiler les fichiers source en fichiers objets
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@powershell -Command "if (!(Test-Path $(dir $@))) { New-Item -ItemType Directory -Path $(dir $@) }"
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(HEADERS)

# Règle pour nettoyer les fichiers générés
clean:
	powershell -Command "if (Test-Path '$(BUILDDIR)') { Remove-Item -Recurse -Force '$(BUILDDIR)' }"
	powershell -Command "if (Test-Path '$(TARGET)') { Remove-Item -Force '$(TARGET)' }"

.PHONY: all clean


