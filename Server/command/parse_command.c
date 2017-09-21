/*
** parse_command.c for parse_command in /home/lak_r/rendu/Semester4/Unix_prog/PSU_2016_myirc/Server
** 
** Made by remi
** Login   <remi.lak@epitech.eu>
**
** Started on  Mon Jun  5 17:20:11 2017 remi
** Last update Sun Jun 11 18:42:11 2017 remi
*/

#include <unistd.h>
#include <string.h>
#include "server.h"

static int		error_client_not_in_channel(t_env *e, int fd_client)
{
  char			msg[300];

  memset(msg, 0, 300);
  sprintf(msg, "/!\\ You need to join a channel.\r\n\
Type /list to list the avaible channels.\r\n\
Type /join [channel name] to join/create a channel\r\n");
  if (e->clients[fd_client] &&
      cb_push_back(&e->clients[fd_client]->cb, msg, strlen(msg)) != 0)
    return (1);
  return (0);
}

static int		add_to_client_write_queue(t_env *e, int fd_client,
						  char *str, int read_size)
{
  int			i;

  (void)read_size;
  i = 0;
  while (i < MAX_FD)
    {
      if (e->clients[i] != NULL &&
	  e->fd_type[i] == FD_CLIENT &&
	  i != fd_client &&
	  (e->clients[i]->channel == e->clients[fd_client]->channel))
	{
	  str = cmd_format_message(e, fd_client, str);
	  if (cb_push_back(&e->clients[i]->cb, str, strlen(str)) != 0)
	    return (1);
	}
      i++;
    }
  return (0);
}

int			is_user_in_channel(t_env *e, int fd_client)
{
  t_channel		*ch;

  if (e->channels == NULL || e->clients[fd_client]->channel == NULL)
    return (0);
  ch = e->channels;
  if (ch->users[fd_client] == JOIN)
    return (1);
  ch = ch->next;
  while (ch != e->channels)
    {
      if (ch->users[fd_client] == JOIN)
	return (1);
      ch = ch->next;
    }
  return (0);
}

static t_cmd_fct	cmdfct[] =
  {
    {"NICK", &command_nick},
    {"QUIT", &command_quit},
    {"LIST", &command_list},
    {"JOIN", &command_join},
    {"PART", &command_part},
    {"USERS", &command_users},
    {"NAMES", &command_names},
    {"MSG", &command_msg},
  };

int			parse_command(t_env *e, int fd_client, char *buf, int r)
{
  int			i;

  i = 0;
  while (i < (int)TABSIZE(cmdfct))
    {
      if (strncmp(buf, cmdfct[i].flag, strlen(cmdfct[i].flag)) == 0)
	{
	  if (cmdfct[i].fct(e, fd_client, buf, r) != 0)
	    return (1);
	  return (0);
	}
      i++;
    }
  if (is_user_in_channel(e, fd_client) != 1)
    error_client_not_in_channel(e, fd_client);
  else
    {
      if (add_to_client_write_queue(e, fd_client, buf, r) != 0)
	return (1);
    }
  return (0);
}
