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

CXX			:= clang++
CXXFLAG		:= -std=c++11 -DDEBUG -g -fsanitize=integer -fsanitize=address -Wno-writable-strings
gTestDir	:= ../gtest
gVersion	:= release-1.11.0
gTestVer	:= googletest-$(gVersion)
gTest		:= $(gTestDir)/gtest $(gTestDir)/$(gTestVer)

TESTDIR		:= ./tests/
TESTSRCS_C	:= $(filter-out main.c,$(SRCS))
TESTSRCS_CPP:= $(wildcard $(TESTDIR)*.cpp)
TESTOBJS	:= $(TESTSRCS_C:%.c=$(SRCDIR)%.o) \
				$(TESTSRCS_CPP:%.cpp=%.o)

%.o: %.cpp
	$(CXX) $(CXXFLAG) -I$(gTestDir) $(INCLUDE) -c $< -o $@

$(gtest):
	mTdir -p $(dir $(gTestDir))
	curl -OL https://github.com/google/googletest/archive/refs/tags/$(gVersion).tar.gz
	tar -xvzf $(gVersion).tar.gz $(gTestVer)
	$(RM) $(gVersion).tar.gz
	python $(gTestVer)/googletest/scripts/fuse_gtest_files.py $(TtestDir)
	mT $(gTestVer) $(gTestDir)

test: FORCE $(gtest) $(TESTOBJS)
	@$(CXX) $(CXXFLAG) \
		$(TESTOBJS) \
		$(gTestDir)/$(gTestVer)/googletest/src/gtest_main.cc \
		$(gTestDir)/gtest/gtest-all.cc \
		-I$(gTestDir) $(INCLUDE) $(LIBS) -o tester
	./tester
	@$(RM) -r tester tester.dSYM

test_clean: FORCE
	$(RM) $(TESTOBJS)
