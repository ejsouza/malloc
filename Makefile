# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esouza <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/23 15:15:48 by esouza            #+#    #+#              #
#    Updated: 2019/10/29 11:42:49 by esouza           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif


NAME = libft_malloc_$(HOSTTYPE).so

LINK = libft_malloc.so

SRC_DIR = srcs

OBJ_DIR = objs

INCLUDE_DIR = includes

HEADER = $(INCLUDE_DIR)/malloc.h

SRCS = malloc.c ft_strlen.c

CC = gcc  -I $(INCLUDE_DIR)/malloc.h

AR = ar rcs

OBJS = $(SRCS:.c=.o)

#OBJS = $(addprefix $(OBJ_DIR)/,$(notdir $(SRC_DIR)))

CFLAGS = -Wall -Werror -Wextra -Iincludes

$(NAME): $(OBJS:%.o=$(OBJ_DIR)/%.o) $(HEADER) Makefile
	@$(AR) $@ $(OBJS:%.o=$(OBJ_DIR)/%.o)
	@ln -sf $(NAME) $(LINK)
	@echo "\033[0;36m            ==== Creating Library ===="

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(srcs) $(CFLAGS) -c $< -o $@
	@echo "\033[32m         ==== Creating Objcts Files ===="

all: $(NAME)

clean:
	@rm -f $(OBJS:%.o=$(OBJ_DIR)/%.o)
	 @echo "\033[33m    ==== All Object files deleted ===="

fclean: clean
	 @rm -f $(NAME) $(LINK)
	 @echo "\033[31m       ==== Everything deleted ===="

re: fclean all

.PHONY: all clean fclean re
