CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

EJECUTABLES = ejercicio1/eje1 ejercicio2/eje2 ejercicio3/eje3 ejercicio4/eje4

all: $(EJECUTABLES)

# Regla general para compilar cada archivo .cpp en su respectivo ejecutable
%/eje%: %/eje%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

run: all
	@echo "Ejecutando ejercicio 1..."
	@./ejercicio1/eje1
	@echo "Ejecutando ejercicio 2..."
	@./ejercicio2/eje2
	@echo "Ejecutando ejercicio 3..."
	@./ejercicio3/eje3
	@echo "Ejecutando ejercicio 4..."
	@./ejercicio4/eje4

clean:
	rm -f $(EJECUTABLES)