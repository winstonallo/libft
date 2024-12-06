CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_FLAGS = -L./libft -lft

SRC_DIR = src
OBJ_DIR = obj

SRCS =  alloc/alloc.c \
        mem/mem.c \

OBJS = $(patsubst $(SRCS).c, $(OBJ_DIR)/%.o, $(SRCS))

NAME = libft.a

.PHONY: all clean fclean re

all: $(OBJ_DIR) $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

