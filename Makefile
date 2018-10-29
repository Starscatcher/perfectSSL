NAME = ft_ssl

SRC = 	./MD5.c \
      	./SHA256.c \
      	./algoStruct.c \
      	./flagsStruct.c \
      	./alignment.c \
      	./bitsOper.c \
      	./findAlgo.c \
      	./findFunc.c \
      	./fromStdin.c \
      	./main.c \
      	./sslSplit.c \
      	./sslError.c \
      	./readFd.c \
      	./readArgs.c \
      	./mdStruct.c \
      	./SHA512.c \
      	./SHA224.c \
      	./SHA384.c \
      	./BASE64.c

MLIB = make -C libftprintf

LIB = libftprintf/libftprintf.a

all: $(NAME)

$(NAME): $(SRC)
	$(MLIB)
	gcc -Wall -Wextra -Werror $(SRC) $(LIB) -o $(NAME)

clean:
	rm -f $(OBJ)
	$(MLIB) clean

fclean: clean
	rm -f $(NAME)
	$(MLIB) fclean

re: fclean all
