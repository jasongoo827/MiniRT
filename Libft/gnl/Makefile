.DEFAULT_GOAL := all

NAME = libftgnl.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

SRCS = get_next_line.c get_next_line_utils.c
OBJS = $(SRCS:%.c=%.o)
INC = get_next_line.h

all: $(NAME)
	
$(NAME): $(OBJS) $(INC)
	ar rcs $(NAME) $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
