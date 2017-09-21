/*
** comment_users.c for commend_users in /home/lak_r/rendu/Semester4/Unix_prog/PSU_2016_myirc/Server/command
**
** Made by remi
** Login   <remi.lak@epitech.eu>
**
** Started on  Mon Jun  5 20:25:28 2017 remi
** Last update Sun Jun 11 22:42:11 2017 minikali
*/

#include <string.h>
#include "server.h"
#include "utils.h"

static int			print_names(t_env *e, char *channel_name,
					    int fd_client)
{
  char				msg[1000];
  t_channel			*ch;
  int				i;

  if (seek_channel_by_name(&e->channels, channel_name) != 0)
    return (0);
  ch = e->channels;
  sprintf(msg, "353 %s :", channel_name);
  if (cb_push_back(&e->clients[fd_client]->cb, msg, strlen(msg)) != 0)
    return (1);
  i = 0;
  while (i < MAX_FD)
    {
      if (ch->users[i] == JOIN)
	sprintf(msg, "%s ", e->clients[i]->name);
      i++;
    }
  sprintf(msg, "%s\r\n", msg);
  cb_push_back(&e->clients[fd_client]->cb, msg, strlen(msg));
  return (0);
}

int				print_req(t_env *e, int fd_client, char **tab)
{
  int				i;

  i = 0;
  while (tab[i])
    {
      print_names(e, tab[i], fd_client);
      i++;
    }
  free_tab(tab);
  return (0);
}

int				print_all(t_env *e, int fd_client)
{
  t_channel			*root;
  t_channel			*ch;

  root = e->channels;
  ch = e->channels;
  while (e->channels)
    {
      print_names(e, ch->name, fd_client);
      ch = ch->next;
      if (ch == root)
	break;
    }
  return (0);
}

int				command_names(t_env *e, int fd_client,
					      char *buf, int r)
{
  char				msg[128];
  char				**tab;

  (void)r;
  tab = strtab(buf + strlen("NAMES"), ",");
  if (tab)
    print_req(e, fd_client, tab);
  else
    print_all(e, fd_client);
  sprintf(msg, "366 %s :End of /NAMES list\r\n",
	  e->clients[fd_client]->channel->name);
  cb_push_back(&e->clients[fd_client]->cb, msg, strlen(msg));
  return (0);
}
