NAME = ircserv

CC = clang++

FLAGS = -Wall -Wextra -Werror

SRCS = main.cpp Server.cpp Msg.cpp Client.cpp Channel.cpp Initcmds.cpp Command.cpp

OBJS = $(SRCS:.cpp=.o)

$(%.o): $(%.cpp) $(%.hpp)
	$(CC) $(FLAGS) -o $@ -c $<

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS)

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