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
SOURCES = $(filter-out $(SRC_DIR)/main.cpp $(SRC_DIR)/interactive.cpp $(SRC_DIR)/capela.cpp $(SRC_DIR)/capela_textured.cpp $(SRC_DIR)/pick_demo.cpp $(SRC_DIR)/projection_demo.cpp $(SRC_DIR)/transform_demo.cpp $(SRC_DIR)/interactive_sdl.cpp $(SRC_DIR)/interactive_opengl.cpp, $(wildcard $(SRC_DIR)/*.cpp))
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
EXECUTABLE = $(BIN_DIR)/raycaster
INTERACTIVE = $(BIN_DIR)/interactive
INTERACTIVE_SDL = $(BIN_DIR)/interactive_sdl
INTERACTIVE_GL = $(BIN_DIR)/interactive_opengl
CAPELA = $(BIN_DIR)/capela
CAPELA_TEX = $(BIN_DIR)/capela_textured
PICKDEMO = $(BIN_DIR)/pick_demo
PROJDEMO = $(BIN_DIR)/projection_demo
TRANSFORMDEMO = $(BIN_DIR)/transform_demo

# SDL2 flags
SDL2_CFLAGS = $(shell pkg-config --cflags sdl2)
SDL2_LIBS = $(shell pkg-config --libs sdl2)

# OpenGL flags
OPENGL_LIBS = -lGL -lGLU

# Regra principal
all: $(EXECUTABLE) $(INTERACTIVE) $(INTERACTIVE_SDL) $(INTERACTIVE_GL) $(CAPELA) $(CAPELA_TEX) $(PICKDEMO) $(PROJDEMO) $(TRANSFORMDEMO)

# Criar executável principal
$(EXECUTABLE): $(OBJECTS) $(OBJ_DIR)/main.o | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(OBJ_DIR)/main.o -o $@ $(LDFLAGS)
	@echo "Build completo! Executável: $(EXECUTABLE)"

# Criar executável interativo
$(INTERACTIVE): $(OBJECTS) $(OBJ_DIR)/interactive.o | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(OBJ_DIR)/interactive.o -o $@ $(LDFLAGS)
	@echo "Build completo! Executável interativo: $(INTERACTIVE)"

# Criar executável interativo SDL2
$(INTERACTIVE_SDL): $(OBJECTS) $(OBJ_DIR)/interactive_sdl.o | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SDL2_CFLAGS) $(OBJECTS) $(OBJ_DIR)/interactive_sdl.o -o $@ $(LDFLAGS) $(SDL2_LIBS)
	@echo "Build completo! Executável interativo SDL2: $(INTERACTIVE_SDL)"

# Compilar interactive_sdl.o com flags SDL2
$(OBJ_DIR)/interactive_sdl.o: $(SRC_DIR)/interactive_sdl.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(SDL2_CFLAGS) -c $< -o $@

# Criar executável interativo OpenGL
$(INTERACTIVE_GL): $(OBJ_DIR)/interactive_opengl.o | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SDL2_CFLAGS) $(OBJ_DIR)/interactive_opengl.o -o $@ $(LDFLAGS) $(SDL2_LIBS) $(OPENGL_LIBS)
	@echo "Build completo! Executável interativo OpenGL: $(INTERACTIVE_GL)"

# Compilar interactive_opengl.o com flags SDL2 e OpenGL
$(OBJ_DIR)/interactive_opengl.o: $(SRC_DIR)/interactive_opengl.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(SDL2_CFLAGS) -c $< -o $@

# Criar executável da capela
$(CAPELA): $(OBJECTS) $(OBJ_DIR)/capela.o | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(OBJ_DIR)/capela.o -o $@ $(LDFLAGS)
	@echo "Build completo! Executável da capela: $(CAPELA)"

# Criar executável da capela com texturas de imagem
$(CAPELA_TEX): $(OBJECTS) $(OBJ_DIR)/capela_textured.o | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(OBJ_DIR)/capela_textured.o -o $@ $(LDFLAGS)
	@echo "Build completo! Executável da capela com texturas: $(CAPELA_TEX)"

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
	rm -rf $(OBJ_DIR) $(EXECUTABLE) $(INTERACTIVE) $(INTERACTIVE_SDL) $(INTERACTIVE_GL) $(CAPELA) $(CAPELA_TEX) $(PICKDEMO) $(PROJDEMO) $(TRANSFORMDEMO)
	@echo "Arquivos limpos!"

# Executar versão normal
run: $(EXECUTABLE)
	./$(EXECUTABLE)

# Executar versão interativa
run-interactive: $(INTERACTIVE)
	./$(INTERACTIVE)

# Executar interface SDL2 interativa (WASD + Mouse)
run-sdl: $(INTERACTIVE_SDL)
	./$(INTERACTIVE_SDL)

# Executar interface OpenGL (WASD + SOFTWARE RENDERING - SEM GPU!)
run-opengl: $(INTERACTIVE_GL)
	@echo "Iniciando OpenGL com SOFTWARE RENDERING (sem GPU)..."
	@echo "Forçando software rendering via variáveis de ambiente..."
	LIBGL_ALWAYS_SOFTWARE=1 MESA_GL_VERSION_OVERRIDE=2.1 ./$(INTERACTIVE_GL)

# Executar cena da capela
run-capela: $(CAPELA)
	./$(CAPELA)

# Executar cena da capela com texturas de imagem
run-capela-textured: $(CAPELA_TEX)
	./$(CAPELA_TEX)

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
	@echo "  make run                   - Cena com textura xadrez"
	@echo "  make run-interactive       - Interface parametrizável (terminal)"
	@echo "  make run-opengl            - 🎮 INTERFACE OPENGL (WASD + Mouse Picking - SOFTWARE RENDERING SEM GPU)"
	@echo "  make run-sdl               - 🎮 INTERFACE SDL2 (WASD + Mouse Picking - ray tracing CPU)"
	@echo "  make run-capela            - Capela com texturas procedurais"
	@echo "  make run-capela-textured   - Capela com texturas de imagem"
	@echo "  make run-pick              - Demonstração de picking"
	@echo "  make run-projections       - Demonstração de projeções"
	@echo "  make run-transforms        - Demonstração de transformações"
	@echo "  make help                  - Mostra esta ajuda"
	@echo ""
	@echo "Programas disponíveis:"
	@echo "  raycaster            - Cena com textura xadrez"
	@echo "  interactive          - Interface terminal"
	@echo "  interactive_opengl   - 🎮 INTERFACE OPENGL (WASD + Mouse - SOFTWARE RENDERING SEM GPU)"
	@echo "  interactive_sdl      - 🎮 INTERFACE SDL2 (WASD + Mouse Picking - ray tracing CPU)"
	@echo "  capela               - Capela procedural"
	@echo "  capela_textured      - Capela com texturas de imagem"
	@echo "  pick_demo            - Demo picking"
	@echo "  projection_demo      - Demo projeções"
	@echo "  transform_demo       - Demo transformações"
	@echo ""
	@echo "📝 Como trocar texturas:"
	@echo "  1. Coloque suas imagens em textures/"
	@echo "  2. Renomeie para: wood.jpg e stained_glass.jpg"
	@echo "  3. Execute: make run-capela-textured"
	@echo ""
	@echo "🎮 Interface SDL2:"
	@echo "  W/A/S/D - Mover câmera"
	@echo "  Q/E     - Subir/Descer"
	@echo "  Setas   - Rotacionar view"
	@echo "  Mouse   - Click para PICKING"
	@echo "  ESC     - Sair"

.PHONY: all clean run run-interactive run-sdl run-opengl run-capela run-capela-textured run-pick run-projections run-transforms help
