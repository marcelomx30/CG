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
SOURCES = $(filter-out $(SRC_DIR)/pick_demo.cpp $(SRC_DIR)/projection_demo.cpp $(SRC_DIR)/transform_demo.cpp $(SRC_DIR)/interactive_opengl.cpp, $(wildcard $(SRC_DIR)/*.cpp))
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
INTERACTIVE_GL = $(BIN_DIR)/interactive_opengl
PROJDEMO = $(BIN_DIR)/projection_demo

# SDL2 flags (para OpenGL context)
SDL2_CFLAGS = $(shell pkg-config --cflags sdl2)
SDL2_LIBS = $(shell pkg-config --libs sdl2)

# OpenGL flags
OPENGL_LIBS = -lGL -lGLU

# Regra principal
all: $(INTERACTIVE_GL) $(PROJDEMO)

# Criar executável interativo OpenGL
$(INTERACTIVE_GL): $(OBJ_DIR)/interactive_opengl.o $(OBJ_DIR)/Texture.o | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SDL2_CFLAGS) $(OBJ_DIR)/interactive_opengl.o $(OBJ_DIR)/Texture.o -o $@ $(LDFLAGS) $(SDL2_LIBS) $(OPENGL_LIBS)
	@echo "Build completo! Executável interativo OpenGL: $(INTERACTIVE_GL)"

# Compilar interactive_opengl.o com flags SDL2 e OpenGL
$(OBJ_DIR)/interactive_opengl.o: $(SRC_DIR)/interactive_opengl.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(SDL2_CFLAGS) -c $< -o $@

# Criar executável de demonstração de projeções (3 planos de fuga)
$(PROJDEMO): $(OBJECTS) $(OBJ_DIR)/projection_demo.o | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(OBJ_DIR)/projection_demo.o -o $@ $(LDFLAGS)
	@echo "Build completo! Executável de projeções: $(PROJDEMO)"

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
	rm -rf $(OBJ_DIR) $(INTERACTIVE_GL) $(PROJDEMO)
	@echo "Arquivos limpos!"

# Executar cena principal interativa (PRINCIPAL)
run: $(INTERACTIVE_GL)
	./$(INTERACTIVE_GL)

# Executar demonstração de projeções (3 planos de fuga - NECESSÁRIO PARA O PROFESSOR)
run-projections: $(PROJDEMO)
	./$(PROJDEMO)

# Mostrar ajuda
help:
	@echo "Makefile para Ray Tracing - Capela 3D"
	@echo ""
	@echo "Comandos disponíveis:"
	@echo "  make                       - Compila todos os programas"
	@echo "  make clean                 - Remove arquivos compilados"
	@echo "  make run                   - 🎮 CENA PRINCIPAL (Ray Tracing interativo)"
	@echo "  make run-projections       - 📐 Demo de 3 projeções (NECESSÁRIO PARA PROFESSOR)"
	@echo "  make help                  - Mostra esta ajuda"
	@echo ""
	@echo "Programas disponíveis:"
	@echo "  ./interactive_opengl       - 🎮 Cena principal com tudo (câmera, transformações, sombras, texturas, picking)"
	@echo "  ./projection_demo          - 📐 Demonstração de 3 planos de fuga (perspectiva, ortográfica, oblíqua)"
	@echo ""
	@echo "🎮 Controles da cena principal:"
	@echo "  W/A/S/D     - Mover câmera"
	@echo "  Q/E         - Subir/Descer"
	@echo "  Setas       - Rotacionar câmera"
	@echo "  I/K/J/L     - Transladar altar"
	@echo "  U/O         - Altar subir/descer"
	@echo "  N/M         - Rotacionar altar"
	@echo "  R           - Resetar altar"
	@echo "  Mouse       - Picking (clique na vela para ligar/desligar)"
	@echo "  ESC         - Sair"
	@echo ""
	@echo "⚙️  Configurações no código: src/interactive_opengl.cpp linhas 21-106"

.PHONY: all clean run run-projections help
