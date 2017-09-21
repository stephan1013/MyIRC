/*
** command_join.c for command_join in /home/lak_r/rendu/Semester4/Unix_prog/PSU_2016_myirc/Server/command
**
** Made by remi
** Login   <remi.lak@epitech.eu>
**
** Started on  Mon Jun  5 18:12:14 2017 remi
** Last update Sun Jun 11 22:24:47 2017 minikali
*/

#include <string.h>
#include "server.h"
#include "utils.h"

static int		join_channel(t_env *e, int fd_client, char *str)
{
  char			msg[100];
  t_client		*client;

  if (!(client = e->clients[fd_client]))
    return (0);
  if (strlen(str) > NAME_SIZE)
    sprintf(msg,
	    "475 [console]: Channel's name cannot exceed '%d' characters\r\n",
	    NAME_SIZE);
  else if (!e->channels || seek_channel_by_name(&e->channels, str) != 0)
    {
      add_channel(&e->channels, str);
      client->channel = e->channels;
      e->channels->users[fd_client] = JOIN;
      sprintf(msg, "332 [console]: Created channel '%s'\r\n", str);
    }
  else
    {
      e->channels->users[fd_client] = JOIN;
      client->channel = e->channels;
      sprintf(msg, "332 [console]: Joined '%s'\r\n", str);
    }
  if (cb_push_back(&client->cb, msg, strlen(msg)) != 0)
    return (1);
  return (0);
}

int			command_join(t_env *e, int fd_client, char *buf, int r)
{
  char			msg[128];
  char			**tab;
  int			i;

  (void)r;
  tab = NULL;
  tab = strtab(buf + strlen("JOIN"), ",");
  if (!tab)
    {
      sprintf(msg, "461 JOIN :Not enough parameters\r\n");
      cb_push_back(&e->clients[fd_client]->cb, msg, strlen(msg));
      return (0);
    }
  i = 0;
  while (tab[i])
    {
      if (join_channel(e, fd_client, tab[i]) != 0)
	return (1);
      i++;
    }
  return (0);
}
