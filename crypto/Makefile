CC = gcc
CFLAGS =-Wall -Werror -Wextra -pedantic -Wno-deprecated-declarations
LDFLAGS=-lssl -lcrypto
OUTFILE =./hblk_crypto.a

OBJ_DIR=./obj

$(OUTFILE): $(patsubst %.c,$(OBJ_DIR)/%.o,$(wildcard *.c))
	ar -r -o $@ $^

$(OBJ_DIR)/%.o: %.c dirmake
	$(CC) -c $(CFLAGS) -o $@  $< $(LDFLAGS)
	
dirmake:
	@mkdir -p $(OBJ_DIR)
	
clean:
	rm -f $(OBJ_DIR)/*.o $(OUTFILE) Makefile.bak

rebuild: clean build

