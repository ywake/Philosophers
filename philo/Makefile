NAME	:= philo
CC		:= gcc
INCLUDE	:= -I./includes
CFLAGS	:= -g -Wall -Werror -Wextra $(INCLUDE)
VPATH	:= srcs

OBJDIR	:= ./objs/
SRCS	:= main.c data.c utils.c
OBJS	:= $(SRCS:%.c=$(OBJDIR)%.o)
DSTRCTR	:= ./tests/destructor.c

.PHONY: all clean fclean re bonus norm leak Darwin_leak Linux_leak tests

all: $(NAME)

$(OBJDIR)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -rf $(NAME).dSYM

re: fclean all

norm:
	@printf "\e[31m"; norminette | grep -v ": OK!" \
	&& exit 1 \
	|| printf "\e[32m%s\n\e[m" "Norm OK!"; printf "\e[m"

$(DSTRCTR):
	curl https://gist.githubusercontent.com/ywake/793a72da8cdae02f093c02fc4d5dc874/raw/destructor.c > $(DSTRCTR)

Darwin_leak: $(LIBFT) $(DSTRCTR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) ./tests/destructor.c -o $(NAME) $(LIBS)

Linux_leak: $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -fsanitize=address $(OBJS) -o $(NAME) $(LIBS)

leak: $(shell uname)_leak

tests: leak
	bash auto_test.sh $(TEST)\
	&& $(MAKE) norm
