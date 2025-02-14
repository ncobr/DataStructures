# Nombre del ejecutable
TARGET = mtplotlibExample

# Compilador
CXX = clang++

# Flags de compilación
CXXFLAGS = -I/usr/include/python3.13 -lpython3.13

# Regla para compilar
all: $(TARGET)

$(TARGET): $(TARGET).cc
	$(CXX) $^ -o $@ $(CXXFLAGS)

# Limpiar archivos generados
clean:
	rm -f $(TARGET)

