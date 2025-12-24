#!/bin/bash
# Script para organizar repositório do trabalho final de CG

echo "=========================================="
echo "  ORGANIZANDO REPOSITÓRIO - CG FINAL"
echo "=========================================="

# Verificar se está na raiz do repositório
if [ ! -d "src" ] || [ ! -d "include" ]; then
    echo "❌ ERRO: Execute este script na raiz do repositório CG/"
    echo "   Certifique-se que existe src/ e include/"
    exit 1
fi

echo ""
echo "📁 1. Criando estrutura de diretórios..."
mkdir -p docs
mkdir -p output
echo "   ✅ docs/ criado"
echo "   ✅ output/ verificado"

echo ""
echo "📄 2. Criando .gitignore..."
cat > .gitignore << 'EOF'
# Executáveis
raycaster
interactive
capela
viewer

# Objetos
obj/
*.o

# Temporários
*.swp
*.swo
*~

# IDE
.vscode/
.idea/
*.sublime-*

# Sistema
.DS_Store
EOF
echo "   ✅ .gitignore criado"

echo ""
echo "📝 3. Criando README.md..."
cat > README.md << 'EOF'
# 🎨 Computação Gráfica - Ray Casting

Trabalho final da disciplina de Computação Gráfica - Capela renderizada com ray casting.

![Capela](output/capela.png)

## ✨ Características

✅ Ray Casting completo  
✅ Texturas procedurais (madeira + vitral colorido)  
✅ Primitivas: Cone, Cilindro, Esfera, Malha  
✅ Sombras realistas  
✅ Iluminação Phong (ambiente + direcional + pontual)  
✅ Visualizador 3D interativo  

## 🚀 Compilar e Executar

### Renderizar imagem final (800×600):
```bash
make capela
./capela
# Gera: output/capela.ppm
```

### Visualizador 3D interativo:
```bash
# Primeiro instale SDL2:
sudo apt-get install libsdl2-dev

# Compile e execute:
make viewer
./viewer
```

## 🎮 Controles do Visualizador

- **W/A/S/D** - Mover (frente/esquerda/trás/direita)
- **Space** - Subir
- **Shift** - Descer
- **Setas** - Olhar ao redor
- **ESC** - Sair

## 📚 Documentação

- 📖 [Documentação Completa](docs/PROJETO_FINAL.md)
- 🐛 [Bug Corrigido](docs/BUG_CORRIGIDO.md)
- 🎮 [Manual do Visualizador](docs/README_VIEWER.md)
- 🤔 [SDL2 vs OpenGL](docs/SDL2_vs_OpenGL.md)

## 🎓 Requisitos Cumpridos

### Obrigatórios (10.0):
- [x] Cone, Cilindro, Esfera, Malha
- [x] 4+ materiais diferentes
- [x] Texturas procedurais
- [x] Transformações (translação, rotação, escala)
- [x] Luz pontual + ambiente
- [x] Câmera configurável
- [x] Projeção perspectiva
- [x] Sombras
- [x] 800×600 pixels

### Bônus (+0.5):
- [x] Luz direcional

**Nota esperada: 10.5/10.0** ⭐
EOF
echo "   ✅ README.md criado"

echo ""
echo "🖼️  4. Convertendo imagem para PNG..."
if [ -f "output/capela.ppm" ]; then
    if command -v magick &> /dev/null; then
        magick output/capela.ppm output/capela.png
        echo "   ✅ capela.png criado"
    elif command -v convert &> /dev/null; then
        convert output/capela.ppm output/capela.png
        echo "   ✅ capela.png criado"
    else
        echo "   ⚠️  ImageMagick não encontrado. Instale com:"
        echo "      sudo apt-get install imagemagick"
        echo "   Pulando conversão..."
    fi
else
    echo "   ⚠️  output/capela.ppm não encontrado"
    echo "   Execute './capela' primeiro para gerar a imagem"
fi

echo ""
echo "📊 5. Verificando arquivos necessários..."

FILES_TO_CHECK=(
    "src/viewer_raycasting.cpp"
    "docs/PROJETO_FINAL.md"
    "docs/BUG_CORRIGIDO.md"
    "docs/README_VIEWER.md"
    "docs/SDL2_vs_OpenGL.md"
)

MISSING_FILES=()

for file in "${FILES_TO_CHECK[@]}"; do
    if [ ! -f "$file" ]; then
        MISSING_FILES+=("$file")
    fi
done

if [ ${#MISSING_FILES[@]} -eq 0 ]; then
    echo "   ✅ Todos os arquivos necessários presentes!"
else
    echo "   ⚠️  Arquivos faltando:"
    for file in "${MISSING_FILES[@]}"; do
        echo "      - $file"
    done
    echo ""
    echo "   📥 Baixe estes arquivos do Claude e coloque nos locais indicados:"
    echo ""
    echo "   viewer_raycasting.cpp    → src/"
    echo "   PROJETO_FINAL.md         → docs/"
    echo "   BUG_CORRIGIDO.md         → docs/"
    echo "   README_VIEWER.md         → docs/"
    echo "   SDL2_vs_OpenGL.md        → docs/"
    echo ""
fi

echo ""
echo "📋 6. Estrutura final do repositório:"
echo ""
tree -L 2 -I 'obj' 2>/dev/null || find . -maxdepth 2 -type f -o -type d | grep -v ".git" | sort

echo ""
echo "=========================================="
echo "  ✅ ORGANIZAÇÃO COMPLETA!"
echo "=========================================="
echo ""
echo "🚀 Próximos passos:"
echo ""
echo "1. Se faltam arquivos, baixe-os do Claude"
echo "2. Compile e teste:"
echo "   make capela"
echo "   make viewer"
echo ""
echo "3. Faça commit:"
echo "   git add ."
echo "   git status"
echo "   git commit -m 'Trabalho final: texturas + visualizador 3D'"
echo "   git push"
echo ""
echo "4. Verifique no GitHub se a imagem aparece no README!"
echo ""
