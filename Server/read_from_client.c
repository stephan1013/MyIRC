/*
** read_from_client.c for read_from_client in /home/lak_r/rendu/Semester4/Unix_prog/PSU_2016_myirc/Server
**
** Made by remi
** Login   <remi.lak@epitech.eu>
**
** Started on  Mon Jun  5 16:47:59 2017 remi
** Last update Sun Jun 11 19:08:31 2017 stephan
*/

#include <unistd.h>
#include "server.h"

int			client_read(t_env *e, int fd_client)
{
  t_client		*client;
  char			buf[BUFFSIZE];
  int			r;
  int			read_size;

  memset(buf, 0, BUFFSIZE);
  client = e->clients[fd_client];
  if ((read_size = cb_count_free_space(&client->cb)) == -1)
    return (1);
  if ((r = read(fd_client, buf, read_size)) > 0)
    {
      cmd_clean_input(buf, 0);
      if (*buf != 0)
	if (parse_command(e, fd_client, buf, r) != 0)
	  return (1);
    }
  else if (r < 0)
    {
      perror("read");
      return (1);
    }
  return (0);
}

int			add_client(t_env *e, int fd_client)
{
  t_client		*new;

  if (!(new = malloc(sizeof(t_client))))
    {
      perror("malloc");
      return (1);
    }
  new->fd = fd_client;
  new->channel = NULL;
  sprintf(new->name, "client-%d", fd_client);
  if (cb_init(&new->cb, BUFFSIZE) != 0)
    return (1);
  e->clients[fd_client] = new;
  return (0);
}

int			accept_client(t_env *e, int fd)
{
  int			cs;

  if (accept_fct(fd, &cs) != 0)
    return (1);
  e->fd_type[cs] = FD_CLIENT;
  e->fct_read[cs] = client_read;
  e->fct_write[cs] = client_write;
  if (add_client(e, cs) != 0)
    return (1);
  return (0);
}

int			read_from_client(t_env *e, fd_set *readfds)
{
  int			i;

  i = 0;
  while (i < MAX_FD)
    {
      if (FD_ISSET(i, readfds) && e->fct_read[i])
	e->fct_read[i](e, i);
      i++;
    }
  return (0);
}
