CC = gcc
INC = lib
SRC = src
OBJ = object
DOCS = document
SRCS = $(SRC)/memoryManagement.c $(SRC)/user.c 
OBJS = $(OBJ)/memoryManagement.o $(OBJ)/user.o 

DEPS = $(INC)/memoryManagement.h

process: $(OBJS)
	$(CC) $(OBJS) -o process

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -I $(INC) -c $< -o $@ -w

doc:
	doxygen Doxyfile

clean:
	rm  -rf ./process 

docclean:
	rm  -rf $(DOCS)/* 

