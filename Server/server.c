/*
** toto.c for toto in /home/lak_r/rendu/Semester4/Unix_prog/PSU_2016_myirc/Server
**
** Made by remi
** Login   <remi.lak@epitech.eu>
**
** Started on  Thu Jun  1 15:55:55 2017 remi
** Last update Sun Jun 11 20:51:53 2017 remi
*/

#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "circular_buffer.h"
#include "server.h"

g_env *e_ext = NULL;

static int		refresh_fds(t_env *e, fd_set *readfds, fd_set *writefds)
{
  int			i;

  i = 0;
  FD_ZERO(readfds);
  FD_ZERO(writefds);
  while (i < MAX_FD)
    {
      if (e->fd_type[i] != FD_FREE)
	{
	  FD_SET(i, readfds);
	  FD_SET(i, writefds);
	}
      i++;
    }
  return (0);
}

int			server(int port)
{
  t_env			e;
  struct timeval	tv;
  fd_set		readfds;
  fd_set		writefds;

  if (init_server(&e, port, &tv) != 0)
    return (1);
  while (1)
    {
      if (refresh_fds(&e, &readfds, &writefds) != 0)
	return (1);
      if (select_fct(&e, &readfds, &writefds, &tv) != 0)
	return (1);
      if (read_from_client(&e, &readfds) != 0)
	return (1);
      if (write_to_client(&e, &writefds) != 0)
	return (1);
    }
  return (0);
}

int			main(int ac, char **av)
{
  if (ac != 2)
    {
      dprintf(2, "usage: %s port\n", av[0]);
      return (84);
    }
  else if (strcmp(av[1], "--help") == 0)
    {
      dprintf(1, "usage: %s port\n", av[0]);
      return (0);
    }
  if (server(atoi(av[1])) != 0)
    return (84);
  return (0);
}
