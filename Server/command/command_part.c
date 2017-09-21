/*
** command_part.c for command_part in /home/lak_r/rendu/Semester4/Unix_prog/PSU_2016_myirc/Server/command
**
** Made by remi
** Login   <remi.lak@epitech.eu>
**
** Started on  Mon Jun  5 20:03:05 2017 remi
** Last update Sun Jun 11 22:25:07 2017 minikali
*/

#include <string.h>
#include "server.h"
#include "utils.h"

static int		part_channel(t_env *e, int fd_client, char *str)
{
  char			msg[100];
  t_channel		*ch;
  t_client		*client;

  if (!(client = e->clients[fd_client]))
    return (0);
  ch = e->channels;
  while (1)
    {
      if (strcmp(ch->name, str) == 0)
	{
	  ch->users[fd_client] = PART;
	  sprintf(msg, "[console]: Left '%s'\r\n", str);
	  if (cb_push_back(&client->cb, msg, strlen(msg)) != 0)
	    return (1);
	}
      ch = ch->next;
      if (ch == e->channels)
	break;
    }
  return (0);
}

static int		set_user_new_channel(t_env *e, int fd_client)
{
  t_client		*client;
  t_channel		*ch;

  if (!(client = e->clients[fd_client]))
    return (1);
  if ((ch = e->channels) == NULL)
    return (1);
  client->channel = NULL;
  if (ch->users[fd_client] == JOIN)
    {
      client->channel = ch;
      return (0);
    }
  ch = ch->next;
  while (ch != e->channels)
    {
      if (ch->users[fd_client] == JOIN)
	{
	  client->channel = ch;
	  return (0);
	}
      ch = ch->next;
    }
  return (0);
}

int			command_part(t_env *e, int fd_client, char *buf, int r)
{
  char			msg[128];
  char			**tab;
  int			i;

  (void)r;
  tab = NULL;
  tab = strtab(buf + strlen("PART"), ",");
  if (!tab)
    {
      sprintf(msg, "461 /part :Not enough parameters\r\n");
      cb_push_back(&e->clients[fd_client]->cb, msg, strlen(msg));
    }
  i = 0;
  while (tab[i])
    {
      if (part_channel(e, fd_client, tab[i]) != 0)
	return (1);
      i++;
    }
  if (set_user_new_channel(e, fd_client) != 0)
    return (1);
  return (0);
}
