NAME		=	ircserv

SRC			=	main.cpp\
				Utils.cpp\
				Invite.cpp\
				Join.cpp\
				Kick.cpp\
				Mode.cpp\
				Ping.cpp\
				Pong.cpp\
				Topic.cpp\
				server.cpp\
				Client.cpp\
				Channel.cpp\
				Comands.cpp\
				Privmsg.cpp\
				Nick.cpp\
				User.cpp

HDS			=	Utils.hpp\
				server.hpp\
				Client.hpp\
				Channel.hpp

OBJ			=	$(SRC:.cpp=.o)

CC			=	c++
CFLAGS		=	-Wall -Wextra -Werror -std=c++98

%.o:	%.cpp %.tpp %.hpp
		$(CC) ${CFLAGS} -o $@ -c $<

$(NAME)		:	$(OBJ) $(HDS)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
					
all			:	$(NAME)

clean		:
		@rm -rf  $(OBJ)

fclean		:	clean
		@rm -rf $(NAME) $(OBJ)

re			:	fclean	all

.PHONY		:	all clean fclean re