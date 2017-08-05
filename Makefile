NAME = fractol

C_DIR = src
C_DIRS = $(shell find $(C_DIR) -type d -follow -print | grep -v '/tests_')
C_FILES = $(shell find $(C_DIRS) -type f -follow -print | grep "\.c" | grep -v '.swp')

O_DIR =	.tmp/obj
O_DIRS = $(C_DIRS:$(C_DIR)%=$(O_DIR)%)
O_FILES = $(C_FILES:$(C_DIR)%.c=$(O_DIR)%.o)

FLAGS = -Wall -Wextra -Werror
INCLUDES = -I ./include -I ./libft/includes -I./minilibx_macos
LIB = -L./minilibx_macos -lmlx -framework OpenGL -framework AppKit -L./libft -lft

CC = gcc

all: $(NAME)

$(NAME): $(O_FILES)
	make -C libft
	make -C minilibx_macos
	$(CC) $(FLAGS) $^ $(INCLUDES) $(LIB) -o $@

$(O_DIR)%.o: $(C_DIR)%.c
	@mkdir -p $(O_DIRS) $(O_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

clean:
	make clean -C libft
	make clean -C minilibx_macos
	@rm -Rf $(O_DIR)

fclean: clean
	make fclean -C libft
	@rm $(NAME) || true
	@rm -Rf .tmp/

debug:
	make -C libft
	$(CC) $(FLAGS) -g $(C_FILES) $(INCLUDES) $(LIB) -o $(NAME)_debug

re: fclean all

.PHONY: clean all fclean re
