NAME	:= philo_bonus
CC		:= gcc
INCLUDE	:= -I./includes
LIBS	:= -lpthread
CFLAGS	:= -g -Wall -Werror -Wextra $(INCLUDE)
VPATH	:= $(SRCDIR) $(TESTDIR)

SRCDIR	:= srcs/
SRCS	:= main.c utils.c error.c\
			data/settings.c data/table.c \
			data/philo_init.c data/philo_funcs.c
OBJS	:= $(SRCS:%.c=$(SRCDIR)%.o)
DSTRCTR	:= ./destructor.c

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

clean: FORCE
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) -r $(NAME).dSYM

re: fclean all

norm: FORCE
	@printf "\e[31m"; norminette | grep -v ": OK!" \
	&& exit 1 \
	|| printf "\e[32m%s\n\e[m" "Norm OK!"; printf "\e[m"

$(DSTRCTR):
	curl https://gist.githubusercontent.com/ywake/793a72da8cdae02f093c02fc4d5dc874/raw/destructor.c > $(DSTRCTR)

Darwin_leak: $(LIBFT) $(DSTRCTR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(DSTRCTR) -o $(NAME) $(LIBS)

Linux_leak: $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -fsanitize=address $(OBJS) -o $(NAME) $(LIBS)

leak: FORCE $(shell uname)_leak

FORCE:
