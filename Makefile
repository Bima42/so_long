NAME = so_long

NAME_BONUS = so_long_bonus

CC = gcc

CFLAGS = -Wall -Wextra -Werror

MLX_PATH = mlx/

MLX_LIB = $(MLX_PATH)libmlx.a

MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

LIBFT_PATH = libft/

LIBFT_LIB = $(LIBFT_PATH)libft.a

Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

CFILES = \
		src/so_long.c\
		src/check_error.c\
		src/parsing_map.c\
		src/clear.c\
		src/draw.c\
		src/texture.c\
		src/init.c\
		src/move.c\
		src/utils.c\
		src/get_next_line/get_next_line.c\
		src/get_next_line/get_next_line_utils.c


SRCS_BONUS	= \
		bonus/so_long_bonus.c\
		bonus/anim_bonus.c\
		bonus/print_bonus.c\
		bonus/monster_move_bonus.c\
		bonus/check_error_bonus.c\
		bonus/parsing_map_bonus.c\
		bonus/clear_bonus.c\
		bonus/draw_bonus.c\
		bonus/texture_bonus.c\
		bonus/move_bonus.c\
		bonus/init_bonus.c\
		bonus/utils_bonus.c\
		bonus/get_next_line/get_next_line.c\
		bonus/get_next_line/get_next_line_utils.c

OBJECTS = $(CFILES:.c=.o)
OBJ_BONUS = $(SRCS_BONUS:.c=.o)

all: subsystems $(NAME)

%.o : %.c
	@echo $(Y)Compiling [$<]...$(X)
	@$(CC) $(CFLAGS) -Imlx -c -o $@ $<
	@printf $(UP)$(CUT)

subsystems:
	@echo $(B)
	make -C $(MLX_PATH) all
	@echo $(B)
	make -C $(LIBFT_PATH) all

$(NAME): $(OBJECTS)
	@echo $(Y)Compiling [$(CFILES)]...$(X)
	@echo $(G)Finished [$(CFILES)]$(X)
	@echo
	@echo $(Y)Compiling [$(NAME)]...$(X)
	@$(CC) $(CFLAGS) $(MLX_FLAGS) $(OBJECTS) $(MLX_LIB) $(LIBFT_LIB) -o $(NAME)
	@echo $(G)Finished [$(NAME)]$(X)

$(NAME_BONUS): $(OBJ_BONUS)
	@echo $(Y)Compiling [$(SRCS_BONUS)]...$(X)
	@echo $(G)Finished [$(SRCS_BONUS)]$(X)
	@echo
	@echo $(Y)Compiling [$(NAME_BONUS)]...$(X)
	@$(CC) $(CFLAGS) $(MLX_FLAGS) $(OBJ_BONUS) $(MLX_LIB) $(LIBFT_LIB) -o $(NAME_BONUS)
	@echo $(G)Finished [$(NAME_BONUS)]$(X)

bonus: $(NAME_BONUS)

clean:
	@make -C $(MLX_PATH) clean
	@make -C $(LIBFT_PATH) clean
	@rm -f $(OBJECTS) $(OBJ_BONUS)
	@echo $(R)Removed [$(OBJECTS)][$(OBJ_BONUS)]$(X)

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)
	@echo $(R)Removed [$(NAME)][$(NAME_BONUS)]$(X)

re: fclean all

.PHONY: all clean fclean re bonus
