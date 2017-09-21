/*
** command_nick.c for command_nick in /home/lak_r/rendu/Semester4/Unix_prog/PSU_2016_myirc/Server/command
**
** Made by remi
** Login   <remi.lak@epitech.eu>
**
** Started on  Mon Jun  5 18:10:55 2017 remi
** Last update Sun Jun 11 20:16:41 2017 stephan
*/

#include <ctype.h>
#include <string.h>
#include "server.h"

static int		is_special(char c)
{
  if (c == '-' || c == '[' || c == ']' || c == '\\' ||
      c == '`' || c == '^' || c == '{' || c == '}')
    return (1);
  else
    return (0);
}

static int		is_valid_nick(char *str)
{
  int			bool;
  char			ptr;

  if (!str || *str != ' ' || strlen(str) > NAME_SIZE)
    return (0);
  ptr = *++str;
  if (isalpha(ptr) == 0)
    return (0);
  str++;
  bool = 0;
  while (*str)
    {
      if (is_special(*str) != 1 && isalnum(*str) == 0)
	return (0);
      str++;
      bool = 1;
    }
  return (bool);
}

static int		usage(t_env *e, int fd_client)
{
  char			msg[100];
  t_client		*client;

  if (!(client = e->clients[fd_client]))
    return (1);
  sprintf(msg, "431 [console]: /nick $username (2-%d characters)\r\n",
	  NAME_SIZE);
  if (cb_push_back(&client->cb, msg, strlen(msg)) != 0)
    return (1);
  return (0);
}

int			command_nick(t_env *e, int fd_client, char *buf, int r)
{
  t_client		*client;
  char			msg[64 + NAME_SIZE];

  (void)r;
  buf = cmd_clean_input(buf, strlen("NICK"));
  if (!(client = e->clients[fd_client]))
    return (1);
  if (is_valid_nick(buf++) != 1)
    {
      if (usage(e, fd_client) != 0)
	return (1);
      return (0);
    }
  if (csf_modify_name(e, fd_client, buf) != 0)
    return (1);
  sprintf(msg, "001 You're now known as '%s'\r\n", csf_get_name(e, fd_client));
  if (cb_push_back(&client->cb, msg, strlen(msg)) != 0)
    return (1);
  return (0);
}
