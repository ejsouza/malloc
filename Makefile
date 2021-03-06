# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esouza <esouza@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/11 16:24:33 by esouza            #+#    #+#              #
#    Updated: 2020/03/11 16:24:38 by esouza           ###   ########.fr        #
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

SRCS = 	malloc.c realloc.c calloc.c alloc_handler.c link_zones.c  \
	free.c free_block.c split_chunk.c unlink_zone.c show_alloc_mem.c \
	strings.c conversion.c enlarge_mem.c find_free_space.c hexdump.c \
	write_to_file.c print_memory_historic.c

CC = gcc  -I $(INCLUDE_DIR)/malloc.h

#AR = ar rcs

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Werror -Wextra -mmacosx-version-min=10.10 -Iincludes

$(NAME): $(OBJS:%.o=$(OBJ_DIR)/%.o) $(HEADER) Makefile
	@$(CC) $(CFLAGS) -o $(NAME) -shared $(OBJS:%.o=$(OBJ_DIR)/%.o)
	@ln -sf $(NAME) $(LINK)
	@echo "\033[0;36m            ==== Creating Library ===="

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@$(CC) $(srcs) $(CFLAGS) -fPIC -c $< -o $@
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
