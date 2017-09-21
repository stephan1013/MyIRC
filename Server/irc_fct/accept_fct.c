/*
** accept_fct.c for accept_fct in /home/lak_r/rendu/Semester4/Unix_prog/PSU_2016_myirc/v2/Server/irc_fct
** 
** Made by remi
** Login   <remi.lak@epitech.eu>
** 
** Started on  Thu Jun  8 15:09:34 2017 remi
** Last update Sun Jun 11 18:24:02 2017 remi
*/

#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

int			accept_fct(int fd_server, int *fd_client)
{
  struct sockaddr_in	client_sin;
  socklen_t		client_sin_size;

  client_sin_size = sizeof(client_sin);
  *fd_client = accept(fd_server,
		      (struct sockaddr *)&client_sin, &client_sin_size);
  if (*fd_client == -1)
    {
      perror("accept");
      return (1);
    }
  printf("New client from %s:%d\n",
	 inet_ntoa(client_sin.sin_addr), ntohs(client_sin.sin_port));
  return (0);
}
