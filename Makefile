.DEFAULT_GOAL := all

CC = cc
RM = rm -f

CFLAGS = -Wall -Wextra -Werror -MMD -MP -g -Imlx
MLXFLAGS = -lmlx -Lmlx -framework OpenGL -framework AppKit

NAME = miniRT
SRCS = main.c \
		parse.c \
		parse_obj.c \
		parse_obj2.c \
		object.c \
		hit_obj.c \
		hit_obj_cy.c \
		hit_obj_co.c \
		discriminant.c \
		darray.c \
		error.c \
		math_vector.c \
		math_vector2.c \
		math_vector3.c \
		matrix.c \
		scene.c \
		phong.c \
		settings.c \
		utils.c \
		utils2.c \
		utils3.c \
		texture.c \
		mapping.c

# BNS_SRCS =

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)
# BNS_OBJS = $(BNS_SRCS:%.c=%.o)
# BNS_DEPS = $(BNS_SRCS:%.c=%.d)
MLX_DIR = ./mlx
MLX_LIB = libmlx.dylib
LIBFT_DIR = ./Libft/libft
LIBFT_LIB = libft.a
GNL_DIR = ./Libft/gnl
GNL_LIB = libftgnl.a
-include $(DEPS)
# -include $(BNS_DEPS)

ifdef ADD_BNS
        OBJS := $(BNS_OBJS)
endif

all : $(NAME)

# bonus: 
#     @ADD_BNS=1 make

$(NAME) : $(OBJS) $(MLX_DIR)/$(MLX_LIB) $(LIBFT_DIR)/$(LIBFT_LIB) $(GNL_DIR)/$(GNL_LIB)
	$(CC) $(CFLAGS) $(MLXFLAGS) $^ -o $(NAME)
	install_name_tool -change libmlx.dylib mlx/libmlx.dylib $(NAME)

$(MLX_DIR)/$(MLX_LIB) :
	make -C $(MLX_DIR)

$(LIBFT_DIR)/$(LIBFT_LIB) :
	make -C $(LIBFT_DIR)

$(GNL_DIR)/$(GNL_LIB) :
	make -C $(GNL_DIR)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS) $(DEPS)
	make clean -C $(MLX_DIR)
	make clean -C $(GNL_DIR)
	make clean -C $(LIBFT_DIR)

fclean : clean
	$(RM) $(NAME)
	$(RM) $(LIBFT_DIR)/$(LIBFT_LIB)
	$(RM) $(GNL_DIR)/$(GNL_LIB)

re : fclean all

.PHONY : all clean fclean re
