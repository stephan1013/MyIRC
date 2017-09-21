/*
** command_list.c for command_list in /home/lak_r/rendu/Semester4/Unix_prog/PSU_2016_myirc/Server/command
**
** Made by remi
** Login   <remi.lak@epitech.eu>
**
** Started on  Mon Jun  5 18:08:31 2017 remi
** Last update Sun Jun 11 21:50:36 2017 minikali
*/

#include <string.h>
#include "server.h"
#include "utils.h"

static int			print_channels(t_env *e, int fd_client,
					       char *str)
{
  char				msg[128];
  t_channel			*ch;
  t_client			*client;

  ch = e->channels;
  if (!(client = e->clients[fd_client]))
    return (1);
  while (e->channels)
    {
      if (!str || strstr(ch->name, str))
	{
	  sprintf(msg, "%s\r\n", ch->name);
	  if (cb_push_back(&client->cb, msg, strlen(msg)) != 0)
	    return (1);
	}
      ch = ch->next;
      if (ch == e->channels)
	break;
    }
  return (0);
}

int			command_list(t_env *e, int fd_client, char *buf, int r)
{
  char			msg[128];
  char			**tab;
  int			i;

  (void)r;
  tab = strtab(buf + strlen("/list"), ",");
  sprintf(msg, "321 %s :%s\r\n",
	  e->clients[fd_client]->channel->name,
	  e->clients[fd_client]->name);
  cb_push_back(&e->clients[fd_client]->cb, msg, strlen(msg));
  if (!tab || !tab[0])
    print_channels(e, fd_client, NULL);
  else
    {
      i = 0;
      while (tab[i])
	print_channels(e, fd_client, tab[i++]);
      free_tab(tab);
    }
  sprintf(msg, "323 :End of /LIST\r\n");
  cb_push_back(&e->clients[fd_client]->cb, msg, strlen(msg));
  return (0);
}
