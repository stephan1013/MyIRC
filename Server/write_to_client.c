/*
** write_to_client.c for write_to_client in /home/lak_r/rendu/Semester4/Unix_prog/PSU_2016_myirc/Server
**
** Made by remi
** Login   <remi.lak@epitech.eu>
**
** Started on  Mon Jun  5 16:51:55 2017 remi
** Last update Sun Jun 11 18:56:57 2017 stephan
*/

#include <errno.h>
#include <unistd.h>
#include "server.h"

int			client_write(t_env *e, int fd_client)
{
  t_client		*client;
  char			buf[BUFFSIZE];
  int			r;

  client = e->clients[fd_client];
  while ((r = cb_pop_front(&client->cb, buf, BUFFSIZE)))
    {
      if (write(fd_client, buf, r) == -1)
	{
	  if (errno == EPIPE)
	    {
	      e->fd_type[fd_client] = FD_FREE;
	      free(e->clients[fd_client]);
	      close(fd_client);
	      e->clients[fd_client] = NULL;
	    }
	  return (1);
	}
    }
  return (0);
}

int			write_to_client(t_env *e, fd_set *writefds)
{
  int			i;

  i = 0;
  while (i < MAX_FD)
    {
      if (FD_ISSET(i, writefds) && e->fd_type[i] == FD_CLIENT)
	e->fct_write[i](e, i);
      i++;
    }
  return (0);
}
