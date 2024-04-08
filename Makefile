.DEFAULT_GOAL := all

CC = cc
RM = rm -f

CFLAGS = -Wall -Wextra -Werror -Imlx
MLXFLAGS = -lmlx -Lmlx -framework OpenGL -framework AppKit

NAME = miniRT
SRCS = main.c vector.c
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)
MLX_DIR = ./mlx
MLX_LIB = libmlx.dylib

all : $(NAME)

$(NAME) : $(OBJS) $(MLX_DIR)/$(MLX_LIB)
	$(CC) $(CFLAGS) $(MLXFLAGS) $^ -o $(NAME)
	install_name_tool -change libmlx.dylib mlx/libmlx.dylib $(NAME)

$(MLX_DIR)/$(MLX_LIB) :
	make -C $(MLX_DIR)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS) $(DEPS)
	make clean -C $(MLX_DIR)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
