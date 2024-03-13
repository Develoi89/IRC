CLEAN_CAR	=	\033[2K\r

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

%.o:	%.cpp %.tpp %.hpp Makefile
		@$(CC) ${CFLAGS} -o $@ -c $<@

$(NAME)		:	$(OBJ) $(HDS)
		@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
		@sleep 0.2
		@echo "$(CLEAN_CAR)$(OK_COLOR)IRC Compiled!$(NO_COLOR)"
		@echo "Use $(BLUE_COLOR)./ircserv$(NO_COLOR) to launch the program"
					
all			:	$(NAME)

clean		:
		@rm -rf  $(OBJ)
		@echo "$(ERROR_COLOR)Dependencies and objects removed$(NO_COLOR)"

fclean		:	clean
		@rm -rf $(NAME) $(OBJ)
		@echo "$(ERROR_COLOR)$(NAME) removed$(NO_COLOR)"

re			:	fclean	all

.PHONY		:	all clean fclean re

run:		all
			@echo ""
			@echo "$(OK_COLOR)Launching IRC...$(NO_COLOR)"
			@echo ""
			@./ircserv 6667 teo

leak:		all
			@echo ""
			@echo "$(OK_COLOR)Launching IRC...$(NO_COLOR)"
			@echo ""
			@leaks -atExit -- ./ircserv 6667 teo

################################################################################
#                                    COLOR                                     #
################################################################################

NO_COLOR		=	\x1b[0m
OK_COLOR		=	\x1b[32;01m
ERROR_COLOR		=	\x1b[31;01m
WARN_COLOR		=	\x1b[33;01m
BLUE_COLOR		=	\x1b[34;01m

OK_STRING		=	$(OK_COLOR)[OK]$(NO_COLOR)
ERROR_STRING	=	$(ERROR_COLOR)[ERRORS]$(NO_COLOR)
WARN_STRING		=	$(WARN_COLOR)[WARNINGS]$(NO_COLOR)