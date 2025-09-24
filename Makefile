CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2 -g
LDFLAGS = -lm
TARGET = numerical_integration
SOURCES = main.c numerical_integration.c
OBJECTS = $(SOURCES:.c=.o)
HEADERS = numerical_integration.h

# Default target
.DEFAULT_GOAL := help

.PHONY: all clean help run debug install uninstall test check format

# Colors for output
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
NC = \033[0m # No Color

## Show this help message
help:
	@echo "$(BLUE)Numerical Integration Project$(NC)"
	@echo "$(BLUE)=============================$(NC)"
	@echo ""
	@echo "$(GREEN)Available targets:$(NC)"
	@echo "  $(YELLOW)all$(NC)       - Build the project"
	@echo "  $(YELLOW)run$(NC)       - Build and run the program"
	@echo "  $(YELLOW)debug$(NC)     - Build with debug symbols and run with gdb"
	@echo "  $(YELLOW)clean$(NC)     - Remove all build artifacts"
	@echo "  $(YELLOW)test$(NC)      - Run automated tests"
	@echo "  $(YELLOW)check$(NC)     - Run static analysis (cppcheck if available)"
	@echo "  $(YELLOW)format$(NC)    - Format code (clang-format if available)"
	@echo "  $(YELLOW)install$(NC)   - Install the program to /usr/local/bin"
	@echo "  $(YELLOW)uninstall$(NC) - Remove the program from /usr/local/bin"
	@echo "  $(YELLOW)help$(NC)      - Show this help message"
	@echo ""
	@echo "$(GREEN)Examples:$(NC)"
	@echo "  make all     # Build the project"
	@echo "  make run     # Quick build and run"
	@echo "  make clean   # Clean build files"

## Build the project
all: $(TARGET)
	@echo "$(GREEN)Build completed successfully!$(NC)"

$(TARGET): $(OBJECTS)
	@echo "$(BLUE)Linking $(TARGET)...$(NC)"
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

%.o: %.c
	@echo "$(BLUE)Compiling $<...$(NC)"
	$(CC) $(CFLAGS) -c $< -o $@

## Build and run the program
run: $(TARGET)
	@echo "$(GREEN)Running $(TARGET)...$(NC)"
	@echo "$(YELLOW)================================$(NC)"
	./$(TARGET)

## Build with debug symbols and run with gdb
debug: CFLAGS += -DDEBUG -O0
debug: $(TARGET)
	@echo "$(GREEN)Starting debug session...$(NC)"
	gdb ./$(TARGET)

## Remove all build artifacts
clean:
	@echo "$(RED)Cleaning build artifacts...$(NC)"
	rm -f $(OBJECTS) $(TARGET)
	@echo "$(GREEN)Clean completed!$(NC)"

## Run automated tests
test: $(TARGET)
	@echo "$(BLUE)Running automated tests...$(NC)"
	@echo "Test 1: Integration from 0 to 1"
	@echo "0\n1" | ./$(TARGET) > test_output.txt
	@if [ -f test_output.txt ]; then \
		echo "$(GREEN)✓ Test 1 completed$(NC)"; \
	else \
		echo "$(RED)✗ Test 1 failed$(NC)"; \
	fi
	@echo "Test 2: Integration from -1 to 1"
	@echo "-1\n1" | ./$(TARGET) >> test_output.txt
	@if [ -f test_output.txt ]; then \
		echo "$(GREEN)✓ Test 2 completed$(NC)"; \
		echo "$(BLUE)Test results saved to test_output.txt$(NC)"; \
	else \
		echo "$(RED)✗ Test 2 failed$(NC)"; \
	fi

## Run static analysis
check:
	@echo "$(BLUE)Running static analysis...$(NC)"
	@if command -v cppcheck >/dev/null 2>&1; then \
		cppcheck --enable=all --std=c99 $(SOURCES); \
		echo "$(GREEN)Static analysis completed!$(NC)"; \
	else \
		echo "$(YELLOW)cppcheck not found. Install with: sudo apt install cppcheck$(NC)"; \
	fi

## Format code
format:
	@echo "$(BLUE)Formatting code...$(NC)"
	@if command -v clang-format >/dev/null 2>&1; then \
		clang-format -i $(SOURCES) $(HEADERS); \
		echo "$(GREEN)Code formatting completed!$(NC)"; \
	else \
		echo "$(YELLOW)clang-format not found. Install with: sudo apt install clang-format$(NC)"; \
	fi

## Install the program
install: $(TARGET)
	@echo "$(BLUE)Installing $(TARGET) to /usr/local/bin...$(NC)"
	sudo cp $(TARGET) /usr/local/bin/
	sudo chmod +x /usr/local/bin/$(TARGET)
	@echo "$(GREEN)Installation completed!$(NC)"
	@echo "You can now run '$(TARGET)' from anywhere"

## Uninstall the program
uninstall:
	@echo "$(RED)Removing $(TARGET) from /usr/local/bin...$(NC)"
	sudo rm -f /usr/local/bin/$(TARGET)
	@echo "$(GREEN)Uninstallation completed!$(NC)"

# Dependency tracking
main.o: main.c $(HEADERS)
numerical_integration.o: numerical_integration.c $(HEADERS)

# Detect missing files
$(SOURCES) $(HEADERS):
	@if [ ! -f $@ ]; then \
		echo "$(RED)Error: Required file $@ is missing!$(NC)"; \
		echo "$(YELLOW)Please ensure all source files are present.$(NC)"; \
		exit 1; \
	fi