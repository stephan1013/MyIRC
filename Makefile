##
## Makefile for Makefile in /home/lak_r/rendu/Semester4/Unix_prog/PSU_2016_myirc
## 
## Made by remi
## Login   <remi.lak@epitech.eu>
## 
## Started on  Tue May 30 13:58:20 2017 remi
## Last update Thu Jun  1 18:33:18 2017 remi
##

all:
	$(MAKE) -C Lib
	$(MAKE) -C Client
	$(MAKE) -C Server

server:
	$(MAKE) -C Lib
	$(MAKE) -C Server

client:
	$(MAKE) -C Lib
	$(MAKE) -C Client

clean:
	$(MAKE) -C Lib		clean
	$(MAKE) -C Server	clean
	$(MAKE) -C Client	clean

fclean:
	$(MAKE) -C Lib		fclean
	$(MAKE) -C Server	fclean
	$(MAKE) -C Client	fclean

re:	fclean all

.PHONY:	all client server clean fclean re
