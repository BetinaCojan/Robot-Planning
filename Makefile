# Numele executabilului
EXECUTABLE = tema1

# Directoarele sursă
SRC_DIR = src

# Extensia fișierelor sursă
SRC_EXT = cpp

# Listă cu toate fișierele sursă
SOURCES = $(wildcard $(SRC_DIR)/*.$(SRC_EXT))

# Compiler și opțiuni de compilare
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Regula de build pentru executabil
build: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Regula de curățare (șterge executabilul)
clean:
	rm -f $(EXECUTABLE)
