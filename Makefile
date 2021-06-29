NAME = ircserv

BONUS = ircserv_bonus

CC = clang++

CFLAGS = -Wall -Wextra -Werror

SRCS = src/main.cpp src/Server.cpp src/Msg.cpp src/Client.cpp src/Channel.cpp src/Initcmds.cpp src/Command.cpp

BONUS_SRCS = src_bonus/main.cpp src_bonus/Server.cpp src_bonus/Msg.cpp src_bonus/Client.cpp src_bonus/Channel.cpp src_bonus/Initcmds.cpp src_bonus/Command.cpp

OBJS = $(SRCS:.cpp=.o)

BONUS_OBJS = $(BONUS_SRCS:.cpp=.o)

$(%.o): $(%.cpp) $(%.hpp)
	$(CC) $(CFLAGS) -o $@ -c $<

all: $(NAME)

bonus: $(BONUS)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(BONUS): $(BONUS_OBJS)
	@$(CC) $(CFLAGS) -o $(BONUS) $(BONUS_OBJS)
	@$(CC) $(CFLAGS) bot.cpp -o client

clean:
	@echo "\033[0;32m"
	@echo "\nDeleting binaries..."
	@rm -f $(OBJS) $(BONUS_OBJS)
	@echo "\033[0m"

fclean:
	@echo "\033[0;32m"
	@echo "\nDeleting objects..."
	@rm -f $(OBJS) $(BONUS_OBJS)
	@echo "\nDeleting executable..."
	@rm -f $(NAME) $(BONUS) client
	@echo "\033[0m"

re: fclean all