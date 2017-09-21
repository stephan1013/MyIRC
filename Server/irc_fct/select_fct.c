/*
** select_fct.c for select_fct in /home/lak_r/rendu/Semester4/Unix_prog/PSU_2016_myirc/Server
** 
** Made by remi
** Login   <remi.lak@epitech.eu>
** 
** Started on  Mon Jun  5 16:45:40 2017 remi
** Last update Sun Jun 11 18:24:17 2017 remi
*/

#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "server.h"

static int		max_fd(t_env *e)
{
  int			fd;
  int			i;

  i = 0;
  fd = 0;
  while (i < MAX_FD)
    {
      if (e->fd_type[i] != FD_FREE)
	fd = i;
      i++;
    }
  return (fd);
}

int			select_fct(t_env *e, fd_set *readfds,
				   fd_set *writefds, struct timeval *tv)
{
  if (select(max_fd(e) + 1, readfds, writefds, NULL, tv) == -1)
    {
      perror("select");
      return (1);
    }
  return (0);
}
