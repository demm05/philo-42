HDIR				=	inc
SDIR				=	src
ODIR				=	obj

CC					=	gcc
CFLAGS				=	-g -Wall -Wextra -O0 -I$(HDIR)

NAME				=	philo

VPATH				=	$(SDIR):$(SDIR)/shared:$(SDIR)/push_swap:$(SDIR)/checker:$(HDIR)

SRCS				:=	$(wildcard $(SDIR)/*.c)
OBJS				:=	$(patsubst $(SDIR)/%.c, $(ODIR)/%.o, $(SRCS))

all: $(NAME)

$(ODIR)/%.o: $(SDIR)/%.c | $(ODIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -pthread $(OBJS) -o $@

$(ODIR):
	mkdir -p $@

clean:
	@rm -rf $(ODIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
