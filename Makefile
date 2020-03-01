ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif


NAME = libft_malloc_$(HOSTTYPE).so

LINK = libft_malloc.so

SRC_DIR = srcs

OBJ_DIR = objs

INCLUDE_DIR = includes

HEADER = $(INCLUDE_DIR)/malloc.h

SRCS = 	ft_malloc.c realloc.c alloc_handler.c link_zones.c find_free_space.c \
		ft_free.c free_block.c split_chunk.c unlink_zone.c show_alloc_mem.c \
		strings.c conversion.c

CC = gcc  -I $(INCLUDE_DIR)/malloc.h

AR = ar rcs

OBJS = $(SRCS:.c=.o)

#OBJS = $(addprefix $(OBJ_DIR)/,$(notdir $(SRC_DIR)))

CFLAGS = -Wall -Werror -Wextra -Iincludes

$(NAME): $(OBJS:%.o=$(OBJ_DIR)/%.o) $(HEADER) Makefile
	@$(CC) $(CFLAGS) -shared -o $(NAME) $(OBJS:%.o=$(OBJ_DIR)/%.o)
	@ln -sf $(NAME) $(LINK)
	@echo "\033[0;36m            ==== Creating Library ===="

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
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
