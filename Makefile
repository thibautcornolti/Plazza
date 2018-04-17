NAME	= plazza

CC	= g++

RM	= rm -f

SRCS	= ./src/classes/Task.cpp \
	  ./src/classes/Worker.cpp \
	  ./src/classes/Slave.cpp \
	  ./src/main.cpp 

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS = -I ./src/classes/pp
CPPFLAGS += -W -Wall -Wextra

LDFLAGS += -pthread

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
