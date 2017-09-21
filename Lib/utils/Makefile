##
## Makefile for Makefile in /home/lak_r/rendu/Semester4/Unix_prog/PSU_2016_myirc/Lib/get_next_line
## 
## Made by remi
## Login   <remi.lak@epitech.eu>
## 
## Started on  Tue May 30 13:45:22 2017 remi
## Last update Sat Jun 10 21:01:52 2017 minikali
##

NAME	=	../libutils.a

SRCS	=	\
		strtab.c \
		get_next_line.c \
		is_blank.c \
		epur_str.c \
		free_tab.c \

OBJS	=	$(SRCS:.c=.o)

CFLAGS	+=	-I./../Include/

CC	=	gcc

RM	=	rm -rfv

all:		$(NAME)

$(NAME):	$(OBJS)
		ar rc $(NAME) $(OBJS)
		ranlib $(NAME)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
