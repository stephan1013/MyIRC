/*
** client_struct_fct.c for client_struct_fct in /home/lak_r/rendu/Semester4/Unix_prog/PSU_2016_myirc/v2/Server
** 
** Made by remi
** Login   <remi.lak@epitech.eu>
** 
** Started on  Thu Jun  8 14:54:35 2017 remi
** Last update Fri Jun  9 23:38:15 2017 minikali
*/

#include <unistd.h>
#include "server.h"

int		csf_modify_name(t_env *e, int fd_client, char *str)
{
  t_client	*client;

  if (!(client = e->clients[fd_client]))
    return (1);
  strncpy(client->name, str, NAME_SIZE);
  return (0);
}

t_client	*csf_seek_client_by_name(t_env *e, char *name)
{
  int		i;

  i = 0;
  while (i < MAX_FD)
    {
      if (e->clients[i] &&
	  strcmp(e->clients[i]->name, name) == 0)
	return (e->clients[i]);
      i++;
    }
  return (NULL);
}

void		csf_free_single_client(t_env *e, int fd)
{
  t_client	*client;

  if (!(client = e->clients[fd]))
    {
      cb_free(&e->clients[fd]->cb);
      free(e->clients[fd]);
      e->clients[fd] = NULL;
      close(fd);
      e->clients[fd] = NULL;
    }
}

void		csf_free_all_client(t_env *e)
{
  int		i;

  i = 0;
  while (i < MAX_FD)
    {
      if (e->clients[i])
	{
	  cb_free(&e->clients[i]->cb);
	  free(e->clients[i]);
	  close(i);
	  e->clients[i] = NULL;
	}
      i++;
    }
}

char		*csf_get_name(t_env *e, int fd_client)
{
  t_client	*client;

  client = e->clients[fd_client];
  return (client->name);
}
