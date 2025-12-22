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
SOURCES = $(filter-out $(SRC_DIR)/main.cpp $(SRC_DIR)/interactive.cpp $(SRC_DIR)/capela.cpp, $(wildcard $(SRC_DIR)/*.cpp))
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
EXECUTABLE = $(BIN_DIR)/raycaster
INTERACTIVE = $(BIN_DIR)/interactive
CAPELA = $(BIN_DIR)/capela

# Regra principal
all: $(EXECUTABLE) $(INTERACTIVE) $(CAPELA)

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
	rm -rf $(OBJ_DIR) $(EXECUTABLE) $(INTERACTIVE) $(CAPELA)
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
	@echo "  make help            - Mostra esta ajuda"
	@echo ""
	@echo "Versões:"
	@echo "  raycaster    - Renderiza cena pré-definida (sala)"
	@echo "  interactive  - Interface para parametrizar a cena"
	@echo "  capela       - Cena da capela com luz do sol e vela"

.PHONY: all clean run run-interactive run-capela help
