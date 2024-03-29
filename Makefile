NAME = pipex

SRC_PATH = sources/
OBJ_PATH = obj/
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g

SRC = checker.c \
	cmd.c \
	error.c \
	free_path.c \
	pipex.c \
	process.c

SRCS = $(addprefix $(SRC_PATH), $(SRC))
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))
INCS = -I ./includes/

all: $(OBJ_PATH) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

$(OBJ_PATH):
	mkdir $(OBJ_PATH)

$(NAME): $(OBJS) libft/libft.a
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -Llibft/ -lft

libft/libft.a:
	make -C libft/

clean:
	rm -rf $(OBJ_PATH)
	make -C libft/ clean

fclean: clean
	rm -rf $(NAME)
	make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re
