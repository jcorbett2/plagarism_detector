# Compiler settings
CC = gcc
CXX = g++
LEX = flex

CFLAGS = -Wall
LFLAGS = -lfl

# Files
LEX_FILE = cmos.l
LEX_OUT = lex.yy.c

MAIN = cmos-file-output.c
FINGERPRINT = cmos.cc

EXEC = lexer
FP_EXEC = cmos

# Directory to process
INPUT_DIR = Examples

# Default target
all: $(EXEC) $(FP_EXEC)

# Step 1: Generate lex.yy.c from tokenizer.l
$(LEX_OUT): $(LEX_FILE)
	$(LEX) $(LEX_FILE)

# Step 2: Compile lexer (main + lex.yy.c)
$(EXEC): $(LEX_OUT) $(MAIN)
	$(CC) $(CFLAGS) $(LEX_OUT) $(MAIN) -o $(EXEC) $(LFLAGS)

# Step 3: Compile fingerprint program
$(FP_EXEC): $(FINGERPRINT)
	$(CXX) $(FINGERPRINT) -o $(FP_EXEC)

# Step 4: Run tokenizer on directory
tokens: $(EXEC)
	./$(EXEC) $(INPUT_DIR)

# Step 5: Run full pipeline (tokenize + fingerprint)
run: tokens $(FP_EXEC)
	./$(FP_EXEC)

# Clean up
clean:
	rm -f $(EXEC) $(FP_EXEC) $(LEX_OUT) tokens.txt