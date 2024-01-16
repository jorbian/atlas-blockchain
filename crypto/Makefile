CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -Wno-deprecated-declarations
LDFLAGS = -lssl -lcrypto
LIB = lib_hblk_crypto.a
OBJ_DIR = ./obj

$(LIB): $(patsubst %.c, $(OBJ_DIR)/%.o, $(wildcard *.c))
	@ar rcs $@ $^

$(OBJ_DIR)/%.o: %.c | dirmake
	@$(CC) -c $(CFLAGS) -o $@ $<

dirmake:
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -f $(OBJ_DIR)/*.o $(LIB) Makefile.bak

rebuild: clean $(LIB)
