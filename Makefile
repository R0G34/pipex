# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abausa-v <abausa-v@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/30 16:31:33 by abausa-v          #+#    #+#              #
#    Updated: 2024/03/30 16:34:41 by abausa-v         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = sources/pipex.c \
      sources/pipex_utils.c

OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(patsubst %.c,%.o,$(SRC))))

CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -g
INCLUDE = -I include
MAKE = make -C
LIBFT_PATH = libft
LIBFT = -L ${LIBFT_PATH} -lft

$(OBJ_DIR)/%.o: sources/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJ_DIR) $(OBJS)
	$(MAKE) $(LIBFT_PATH) all
	$(CC) $(OBJS) $(LIBFT) -o $(NAME)

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(MAKE) $(LIBFT_PATH) clean
	$(RM) $(OBJS)
	$(RM) $(OBJ_DIR)

fclean: clean
	$(MAKE) $(LIBFT_PATH) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
