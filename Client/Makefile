##
## Makefile for Makefile in /home/lak_r/rendu/Semester4/Unix_prog/PSU_2016_myirc/Server
## 
## Made by remi
## Login   <remi.lak@epitech.eu>
## 
## Started on  Tue May 30 13:53:27 2017 remi
## Last update Sun Jun 11 18:53:44 2017 remi
##

NAME	=	../client

SRCS	=	client.c \
		utils.c \
		handle_server.c \
		my_str_to_wordtab.c

OBJS	=	$(SRCS:.c=.o)

CFLAGS	+=	-W -Wall -Wextra
CFLAGS	+=	-I./../Include/ -I./../Lib/Include

LDFLAGS	+=	-L./../Lib/ -lutils

CC	=	gcc

RM	=	rm -rfv

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(LDFLAGS)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
