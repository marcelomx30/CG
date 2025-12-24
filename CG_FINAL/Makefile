# Makefile para projeto de Ray Casting em C++

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I./include
LDFLAGS =

# Diretórios
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = .

# Arquivos fonte
SOURCES = $(filter-out $(SRC_DIR)/main.cpp $(SRC_DIR)/interactive.cpp $(SRC_DIR)/capela.cpp $(SRC_DIR)/viewer_raycasting.cpp, $(wildcard $(SRC_DIR)/*.cpp))
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
EXECUTABLE = $(BIN_DIR)/raycaster
INTERACTIVE = $(BIN_DIR)/interactive
CAPELA = $(BIN_DIR)/capela
VIEWER = $(BIN_DIR)/viewer

# Flags SDL2
SDL_FLAGS = $(shell sdl2-config --cflags --libs)

# Regra principal
all: $(EXECUTABLE) $(INTERACTIVE) $(CAPELA) $(VIEWER)

# Criar executável principal
$(EXECUTABLE): $(OBJECTS) $(OBJ_DIR)/main.o | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(OBJ_DIR)/main.o -o $@ $(LDFLAGS)
	@echo "Build completo! Executável: $(EXECUTABLE)"

# Criar executável interativo
$(INTERACTIVE): $(OBJECTS) $(OBJ_DIR)/interactive.o | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(OBJ_DIR)/interactive.o -o $@ $(LDFLAGS)
	@echo "Build completo! Executável interativo: $(INTERACTIVE)"

# Criar executável da capela
$(CAPELA): $(OBJECTS) $(OBJ_DIR)/capela.o | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(OBJ_DIR)/capela.o -o $@ $(LDFLAGS)
	@echo "Build completo! Executável da capela: $(CAPELA)"

# Criar visualizador interativo com RAY CASTING
$(VIEWER): $(OBJECTS) $(OBJ_DIR)/viewer_raycasting.o | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(OBJ_DIR)/viewer_raycasting.o -o $@ $(LDFLAGS) $(SDL_FLAGS)
	@echo "Build completo! Visualizador interativo: $(VIEWER)"

# Compilar objetos
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Criar diretórios se não existirem
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Limpar arquivos gerados
clean:
	rm -rf $(OBJ_DIR) $(EXECUTABLE) $(INTERACTIVE) $(CAPELA) $(VIEWER)
	@echo "Arquivos limpos!"

# Executar versão normal
run: $(EXECUTABLE)
	./$(EXECUTABLE)

# Executar versão interativa
run-interactive: $(INTERACTIVE)
	./$(INTERACTIVE)

# Executar cena da capela
run-capela: $(CAPELA)
	./$(CAPELA)

# Executar visualizador 3D (RAY CASTING em tempo real!)
run-viewer: $(VIEWER)
	@echo "Iniciando visualizador interativo com RAY CASTING..."
	@echo "Controles: WASD (mover), Space (subir), Shift (descer), Setas (olhar), ESC (sair)"
	./$(VIEWER)

# Atalho para compilar só o viewer
viewer: $(VIEWER)

# Mostrar ajuda
help:
	@echo "Makefile para Ray Casting"
	@echo ""
	@echo "Comandos disponíveis:"
	@echo "  make                 - Compila todos os programas"
	@echo "  make clean           - Remove arquivos compilados"
	@echo "  make run             - Compila e executa versão normal"
	@echo "  make run-interactive - Compila e executa versão interativa"
	@echo "  make run-capela      - Compila e executa cena da capela"
	@echo "  make run-viewer      - VISUALIZADOR 3D INTERATIVO (RAY CASTING!)"
	@echo "  make viewer          - Compila apenas o visualizador"
	@echo "  make help            - Mostra esta ajuda"
	@echo ""
	@echo "Versões:"
	@echo "  raycaster    - Renderiza cena pré-definida (sala)"
	@echo "  interactive  - Interface para parametrizar a cena"
	@echo "  capela       - Cena da capela com luz do sol e vela"
	@echo "  viewer       - NAVEGAÇÃO 3D EM TEMPO REAL (100% ray casting!)"

.PHONY: all clean run run-interactive run-capela run-viewer viewer help
