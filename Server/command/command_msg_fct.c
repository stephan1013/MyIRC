/*
** command_msg_fct.c for command_msg_fct in /home/lak_r/rendu/Semester4/Unix_prog/PSU_2016_myirc/Server/command
** 
** Made by remi
** Login   <remi.lak@epitech.eu>
** 
** Started on  Sun Jun 11 18:14:04 2017 remi
** Last update Sun Jun 11 18:44:59 2017 remi
*/

#include <string.h>
#include "server.h"
#include "utils.h"

static int		usage(t_env *e, int fd_client)
{
  t_client		*client;
  char			buf[500];

  if (!(client = e->clients[fd_client]))
    return (1);
  sprintf(buf, "%s\r\n%s\r\n%s\r\n",
	  "/msg [nickname] [message]:\t\tsends message to a specific user",
	  "/msg [channel] [nickname] [file]:\tsends a file to a user",
	  "/accept_file [nickname]:\t\taccepts the reception of a\
file coming from one of the channel's user");
  printf("buf %s\n", buf);
  cb_push_back(&client->cb, buf, strlen(buf));
  return (0);
}

int			send_msg(t_env *e, char *buf)
{
  char			**tab;

  if (!(tab = strtab(buf, " ")) || tab[1] == NULL)
    return (0);
  if (csf_seek_client_by_name(e, tab[1]) == NULL)
    return (0);
  if (tab[2] == NULL)
    return (0);
  else
    return (1);
  return (0);
}

int			send_file(t_env *e, char *buf)
{
  char			**tab;

  if (!(tab = strtab(buf, " ")) || tab[1] == NULL)
    return (0);
  if (seek_channel_by_name(&e->channels, tab[1]) != 0)
    return (0);
  if (tab[2] == NULL || tab[3] == NULL)
    return (0);
  else
    return (1);
  return (0);
}

int			send_msg_fct(t_env *e, int fd_client, char *buf)
{
  t_client		*dest;
  t_client		*sender;
  char			*name;
  char			*to_send;
  char			msg[100];

  strtok(buf, " ");
  name = strtok(NULL, " ");
  to_send = strtok(NULL, "\0");
  dest = csf_seek_client_by_name(e, name);
  if (!(sender = e->clients[fd_client]))
    return (1);
  if (!name || !dest || !sender)
    {
      usage(e, fd_client);
      return (1);
    }
  sprintf(msg, "from[%s]: %s\r\n", sender->name, to_send);
  cb_push_back(&dest->cb, msg, strlen(msg));
  return (0);
}

int			send_file_fct(t_env *e, int fd_client, char *buf)
{
  t_client		*client;
  char			msg[100];

  (void)buf;
  if (!(client = e->clients[fd_client]))
    return (1);
  sprintf(msg, "%s", "function not yet implemented\r\n");
  cb_push_back(&client->cb, msg, strlen(msg));
  return (0);
}
