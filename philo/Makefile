HDIR				=	inc
SDIR				=	src
ODIR				=	obj

CC					=	gcc
CFLAGS				=	-Wall -Wextra -Werror -I$(HDIR)

NAME				=	philo

VPATH				=	$(SDIR)

SRCS				=	init.c libft.c main.c monitor.c mutex.c parse.c phil.c utils.c
OBJS				:=	$(patsubst %.c, $(ODIR)/%.o, $(SRCS))

all: $(NAME)

$(ODIR)/%.o: %.c | $(ODIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -pthread $(OBJS) -o $@

$(ODIR):
	mkdir -p $@

compiledb:
	@compiledb make -n all > /dev/null 2>&1

clean:
	@rm -rf $(ODIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
