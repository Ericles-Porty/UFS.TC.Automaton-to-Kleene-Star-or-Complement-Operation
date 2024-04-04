# Definição de variáveis
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
INCLUDES = -Iincludes
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# Lista de arquivos fonte e objeto
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

# Nome do executável
TARGET = minerador.exe
BAT_SCRIPT = run_minerador.bat

# Regras de compilação
all: $(BINDIR)/$(TARGET) $(BAT_SCRIPT)

$(BINDIR)/$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ -c $<

# Criação de diretórios
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

# Regra para criar o arquivo batch
$(BAT_SCRIPT): $(BINDIR)/$(TARGET)
	echo "$(BINDIR)/$(TARGET)" > $(BAT_SCRIPT)

# Regra para limpar arquivos intermediários e o executável
clean:
	del /Q $(OBJDIR)\*.o
	del /Q $(BINDIR)\$(TARGET) $(BAT_SCRIPT)

# Phony targets
.PHONY: all clean
