NAME = ircserv

CC = clang++

CFLAGS = -Wall -Wextra -Werror

SRCS = main.cpp Server.cpp Msg.cpp Client.cpp Channel.cpp Initcmds.cpp Command.cpp

BONUS_SRCS = main.cpp Server.cpp Msg.cpp Client.cpp Channel.cpp Initcmds_bonus.cpp Command_bonus.cpp

OBJS = $(SRCS:.cpp=.o)

BONUS_OBJS = $(BONUS_SRCS:.cpp=.o)

$(%.o): $(%.cpp) $(%.hpp)
	$(CC) $(CFLAGS) -o $@ -c $<

all: $(NAME)

bonus: $(BONUS)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(BONUS): $(BONUS_OBJS)
	@$(CC) $(FLAGS) -o $(BONUS) $(BONUS_OBJS)

clean:
	@echo "\033[0;32m"
	@echo "\nDeleting binaries..."
	@rm -f $(OBJS)
	@echo "\033[0m"

fclean:
	@echo "\033[0;32m"
	@echo "\nDeleting objects..."
	@rm -f $(OBJS)
	@echo "\nDeleting executable..."
	@rm -f $(NAME)
	@echo "\033[0m"

re: fclean all