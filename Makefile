##
## EPITECH PROJECT, 2018
## cpp_plazza
## File description:
## Makefile
##

NAME	=	plazza

CC	=	g++

RM	=	rm -f

LIST	=	classes/Task				\
		classes/Worker				\
		classes/WorkerPool			\
		classes/WorkerOutputHandler		\
		classes/Slave				\
		classes/SlavePool			\
		classes/Parser				\
		classes/Scrapper			\
		classes/Fork				\
		classes/UserInterface			\
		classes/WebServer			\
		classes/socket/Socket			\
		classes/socket/TCPSocket		\
		classes/socket/ServerTCPSocket		\
		classes/socket/ClientTCPSocket		\
		classes/socket/UnixSocket		\
		classes/socket/ServerUnixSocket		\
		classes/socket/ClientUnixSocket		\
		main

SRCDIR	=	src
OBJDIR	=	build

SORTED	=	$(sort $(LIST))
SRCS	=	$(SORTED:%=$(SRCDIR)/%.cpp)
OBJS	=	$(SORTED:%=$(OBJDIR)/%.o)

CPPFLAGS	=	-I ./src/classes/
CPPFLAGS	+=	-W -Wall -Wextra -std=c++14 -g

LDFLAGS	+=	-pthread

ui:	$(OBJDIR)/classes/socket $(NAME)

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

$(OBJDIR)/%.o:	$(SRCDIR)/%.cpp
		$(CC) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)/classes/socket:	$(OBJDIR)/classes
			mkdir -p $(OBJDIR)/classes/socket

$(OBJDIR)/classes:	$(OBJDIR)
			mkdir -p $(OBJDIR)/classes

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	$(RM) -r $(OBJDIR)

fclean:	clean
	$(RM) $(NAME)

re:	fclean ui

.PHONY:	ui clean fclean re
