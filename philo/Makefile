#############
# Functions #
#############

# define uniq
# 	$(eval seen :=)
# 	$(foreach _,$1,$(if $(filter $_, ${seen}),, $(eval seen += $_)))
# 	$(seen)
# endef

uniq = $(if $1,$(firstword $1) $(call uniq,$(filter-out $(firstword $1),$1)))

#############
# Variables #
#############

NAME	:= philo
CC		:= gcc
INCLUDE	:= -I./includes
LIBS	:= -lpthread
CFLAGS	:= -g -Wall -Werror -Wextra $(INCLUDE)
VPATH	:= srcs/

SRCS	:= main.c thread.c \
			utils/ft_atoi.c utils/ft_calloc.c utils/ft_set.c utils/timestamp.c \
			data/settings.c \
			data/fork.c data/fork_funcs.c \
			data/table.c \
			data/philo.c data/philo_funcs.c
SRCDIRS	:= $(call uniq, $(dir $(SRCS)))

OBJDIR	:= objs/
OBJDIRS	:= $(addprefix $(OBJDIR), $(SRCDIRS))
OBJS	:= $(addprefix $(OBJDIR), $(SRCS:%.c=%.o))

DSTRCTR	:= ./destructor.c

#################
# General rules #
#################

all: $(NAME)

$(NAME): $(OBJDIRS) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

clean: FORCE
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) -r $(NAME).dSYM

re: fclean all

norm: FORCE
	@printf "$(RED)"; norminette | grep -v ": OK!" \
	&& exit 1 \
	|| printf "$(GREEN)%s$(END)\n" "Norm OK"

$(OBJDIRS):
	mkdir -p $@

$(OBJDIR)%.o: %.c
	@printf "$(THIN)$(ITALIC)"
	$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(END)"

.PHONY: FORCE
FORCE:

###############
# Debug rules #
###############

$(DSTRCTR):
	curl https://gist.githubusercontent.com/ywake/793a72da8cdae02f093c02fc4d5dc874/raw/destructor.c > $(DSTRCTR)

sani: $(OBJDIRS) $(OBJS)
	$(CC) $(CFLAGS) -fsanitize=thread $(OBJS) -o $(NAME) $(LIBS)

Darwin_leak: $(DSTRCTR) $(OBJDIRS) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(DSTRCTR) -o $(NAME) $(LIBS)

Linux_leak: $(OBJDIRS) $(OBJS)
	$(CC) $(CFLAGS) -fsanitize=address $(OBJS) -o $(NAME) $(LIBS)

leak: $(shell uname)_leak

##########
# Colors #
##########

END		= \e[0m
BOLD	= \e[1m
THIN	= \e[2m
ITALIC	= \e[3m
U_LINE	= \e[4m
BLACK	= \e[30m
RED		= \e[31m
GREEN	= \e[32m
YELLOW	= \e[33m
BLUE	= \e[34m
PURPLE	= \e[35m
CYAN	= \e[36m
WHITE	= \e[37m
