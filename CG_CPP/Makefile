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
PICKDEMO = $(BIN_DIR)/pick_demo
PROJDEMO = $(BIN_DIR)/projection_demo
TRANSFORMDEMO = $(BIN_DIR)/transform_demo

# SDL2 flags (para OpenGL context)
SDL2_CFLAGS = $(shell pkg-config --cflags sdl2)
SDL2_LIBS = $(shell pkg-config --libs sdl2)

# OpenGL flags
OPENGL_LIBS = -lGL -lGLU

# Regra principal
all: $(INTERACTIVE_GL) $(PICKDEMO) $(PROJDEMO) $(TRANSFORMDEMO)

# Criar executável interativo OpenGL
$(INTERACTIVE_GL): $(OBJ_DIR)/interactive_opengl.o $(OBJ_DIR)/Texture.o | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SDL2_CFLAGS) $(OBJ_DIR)/interactive_opengl.o $(OBJ_DIR)/Texture.o -o $@ $(LDFLAGS) $(SDL2_LIBS) $(OPENGL_LIBS)
	@echo "Build completo! Executável interativo OpenGL: $(INTERACTIVE_GL)"

# Compilar interactive_opengl.o com flags SDL2 e OpenGL
$(OBJ_DIR)/interactive_opengl.o: $(SRC_DIR)/interactive_opengl.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(SDL2_CFLAGS) -c $< -o $@

# Criar executável de demonstração de picking
$(PICKDEMO): $(OBJECTS) $(OBJ_DIR)/pick_demo.o | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(OBJ_DIR)/pick_demo.o -o $@ $(LDFLAGS)
	@echo "Build completo! Executável de picking: $(PICKDEMO)"

# Criar executável de demonstração de projeções
$(PROJDEMO): $(OBJECTS) $(OBJ_DIR)/projection_demo.o | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(OBJ_DIR)/projection_demo.o -o $@ $(LDFLAGS)
	@echo "Build completo! Executável de projeções: $(PROJDEMO)"

# Criar executável de demonstração de transformações
$(TRANSFORMDEMO): $(OBJ_DIR)/transform_demo.o | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJ_DIR)/transform_demo.o -o $@ $(LDFLAGS)
	@echo "Build completo! Executável de transformações: $(TRANSFORMDEMO)"

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
	rm -rf $(OBJ_DIR) $(INTERACTIVE_GL) $(PICKDEMO) $(PROJDEMO) $(TRANSFORMDEMO)
	@echo "Arquivos limpos!"

# Executar interface OpenGL interativa (PRINCIPAL)
run: $(INTERACTIVE_GL)
	@echo "Iniciando OpenGL com SOFTWARE RENDERING (sem GPU)..."
	LIBGL_ALWAYS_SOFTWARE=1 MESA_GL_VERSION_OVERRIDE=2.1 ./$(INTERACTIVE_GL)

# Alias para run
run-opengl: run

# Executar demonstração de picking
run-pick: $(PICKDEMO)
	./$(PICKDEMO)

# Executar demonstração de projeções
run-projections: $(PROJDEMO)
	./$(PROJDEMO)

# Executar demonstração de transformações
run-transforms: $(TRANSFORMDEMO)
	./$(TRANSFORMDEMO)

# Mostrar ajuda
help:
	@echo "Makefile para Ray Casting"
	@echo ""
	@echo "Comandos disponíveis:"
	@echo "  make                       - Compila todos os programas"
	@echo "  make clean                 - Remove arquivos compilados"
	@echo "  make run                   - 🎮 INTERFACE OPENGL (WASD + Mouse Picking - SOFTWARE RENDERING SEM GPU)"
	@echo "  make run-opengl            - Alias para 'make run'"
	@echo "  make run-pick              - Demonstração de picking"
	@echo "  make run-projections       - Demonstração de projeções"
	@echo "  make run-transforms        - Demonstração de transformações"
	@echo "  make help                  - Mostra esta ajuda"
	@echo ""
	@echo "Programas disponíveis:"
	@echo "  interactive_opengl   - 🎮 Interface principal OpenGL (software rendering)"
	@echo "  pick_demo            - Demo de picking"
	@echo "  projection_demo      - Demo de projeções"
	@echo "  transform_demo       - Demo de transformações"
	@echo ""
	@echo "📝 Como trocar texturas:"
	@echo "  1. Coloque suas imagens em textures/"
	@echo "  2. Renomeie para: wood.jpg, stained_glass.jpg, wall.jpg"
	@echo "  3. Execute: make run"
	@echo ""
	@echo "🎮 Controles OpenGL:"
	@echo "  W/A/S/D - Mover câmera"
	@echo "  Q/E     - Subir/Descer"
	@echo "  Setas   - Rotacionar view"
	@echo "  Mouse   - Click para PICKING"
	@echo "  ESC     - Sair"

.PHONY: all clean run run-opengl run-pick run-projections run-transforms help
