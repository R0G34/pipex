# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abausa-v <abausa-v@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/21 18:57:50 by abausa-v          #+#    #+#              #
#    Updated: 2024/06/21 18:58:38 by abausa-v         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT_FLAGS = -lft -L $(LIBFT_DIR)
INCLUDES_FLAG = -Iincludes -I$(LIBFT_DIR)

SRCS = sources/main.c sources/pipex.c sources/garbage_collector.c
OBJS = $(SRCS:soures/%.c=objs/%.o)

MKDIR = mkdir -p
RM = rm -rf

RED = "\\033[31m"
RESET = "\\033[0m"

all: $(NAME)

$(NAME): $(OBJS)
	@echo $(RED) " - Compiling" $(RESET)
	@for i in 1 2 3 4; do echo -n " .. "; sleep 1; done
	@echo
	@$(MAKE) -s -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_FLAGS) -o $(NAME)
	@echo $(RED) " - Done!" $(RESET)

objs/%.o: soures/%.c
	@$(MKDIR) objs
	@$(CC) $(CFLAGS) $(INCLUDES_FLAG) -c $< -o $@

clean:
	@$(RM) objs
	@echo $(RED) " - Cleaned!" $(RESET)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@echo $(RED) " - Full Cleaned!" $(RESET)

re: fclean all

.PHONY: all clean fclean re
