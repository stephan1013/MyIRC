## Makefile for Makefile in /home/lak_r/rendu/Semester4/Unix_prog/PSU_2016_myirc/Server
## 
## Made by remi
## Login   <remi.lak@epitech.eu>
## 
## Started on  Tue May 30 13:53:27 2017 remi
## Last update Sun Jun 11 22:59:03 2017 remi
##

NAME		=	../server

ROOT_FILES	=	\
			server.c \
			read_from_client.c \
			write_to_client.c \
			init_server.c \
			client_struct_fct.c \

IRC_FILES	=	\
			select_fct.c \
			accept_fct.c \
			listen_fct.c \
			socket_fct.c \
			bind_fct.c \

CHANNEL_FILES	=	\
			channel_fct.c \
			channel_pop.c \

CMD_FILES	=	\
			parse_command.c \
			command_nick.c \
			command_list.c \
			command_join.c \
			command_part.c \
			command_users.c \
			command_names.c \
			command_msg.c \
			command_msg_fct.c \
			command_quit.c \
			command_fct_utils.c \

CB_FILES	=	\
			circular_buffer.c \
			cb_fct.c \

SRCS		=	$(ROOT_FILES) \
			$(addprefix channel_fct/, $(CHANNEL_FILES)) \
			$(addprefix circular_buffer/, $(CB_FILES)) \
			$(addprefix command/, $(CMD_FILES)) \
			$(addprefix irc_fct/, $(IRC_FILES)) \

OBJS		=	$(SRCS:.c=.o)

CFLAGS		+=	-W -Wall -Wextra
CFLAGS		+=	-I./../Include/ -I./../Lib/Include

LDFLAGS		+=	-L./../Lib/ -lutils

CC		=	gcc

RM		=	rm -rfv

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(LDFLAGS)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
