#
# Makefile de EXEMPLO
#
# OBRIGATÓRIO ter uma regra "all" para geração da biblioteca e de uma
# regra "clean" para remover todos os objetos gerados.
#
# É NECESSARIO ADAPTAR ESSE ARQUIVO de makefile para suas necessidades.
#  1. Cuidado com a regra "clean" para não apagar o "support.o"
#
# OBSERVAR que as variáveis de ambiente consideram que o Makefile está no diretótio "cthread"
#

CC=gcc
CFLAGS=-Wall -g
LIB_DIR=./lib
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src
TST_DIR=./exemplos
TST_PRG=exemplo

all: clear $(BIN_DIR)/cdata.o $(BIN_DIR)/cthread.o $(BIN_DIR)/cfila.o $(BIN_DIR)/support.o
	ar rcs $(LIB_DIR)/libcthread.a $(BIN_DIR)/cdata.o $(BIN_DIR)/cthread.o $(BIN_DIR)/cfila.o $(BIN_DIR)/support.o

$(BIN_DIR)/cdata.o: $(SRC_DIR)/cdata.c
	$(CC) $(CFLAGS) -c -o $(BIN_DIR)/cdata.o -I$(INC_DIR) $(SRC_DIR)/cdata.c

$(BIN_DIR)/cthread.o: $(SRC_DIR)/cthread.c
	$(CC) $(CFLAGS) -c -o $(BIN_DIR)/cthread.o -I$(INC_DIR) $(SRC_DIR)/cthread.c

$(BIN_DIR)/cfila.o: $(SRC_DIR)/cfila.c
	$(CC) $(CFLAGS) -c -o $(BIN_DIR)/cfila.o -I$(INC_DIR) $(SRC_DIR)/cfila.c

# copy support.o, cleans files and then copies support.o back into $(BIN_DIR)
clean:
	cp $(BIN_DIR)/support.o support.o
	rm -rf $(LIB_DIR)/*.a $(BIN_DIR)/*.o $(SRC_DIR)/*~ $(INC_DIR)/*~ *~
	cp support.o $(BIN_DIR)/support.o
	rm support.o

# Build tools
dev: build
	@echo "\n"
	${TST_DIR}/${TST_PRG}
	@echo "\n\nTest program ended."

build: all
	@make -C "exemplos" -s ${TST_PRG}

# Testes
testes: all
	@make -C "testes"
	./testes/testcFila

clear:
	clear
