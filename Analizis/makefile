# Nombre del ejecutable y directorios
TARGET = sortAlgorithmsAnalizis
SRC_DIR = .
BIN_DIR = bin
LIB_DIR = lib

# Compilador
CXX = clang++

# Obtener flags de Python y NumPy automáticamente
PYTHON_CFLAGS  = $(shell pkg-config --cflags python3)
NUMPY_INCLUDE  = $(shell python3 -c "import numpy; print(numpy.get_include())")

# Flags de compilación
CXXFLAGS = $(PYTHON_CFLAGS) -I$(NUMPY_INCLUDE) -I$(LIB_DIR)

# Regla para compilar
all: $(BIN_DIR)/$(TARGET)

# Crear el binario en bin/
$(BIN_DIR)/$(TARGET): $(SRC_DIR)/$(TARGET).cc | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

# Crear el directorio bin si no existe
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Limpiar archivos generados
clean:
	rm -rf $(BIN_DIR)

