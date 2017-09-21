/*
** command_msg.c for command_msg in /home/lak_r/rendu/Semester4/Unix_prog/PSU_2016_myirc/Server/command
** 
** Made by remi
** Login   <remi.lak@epitech.eu>
** 
** Started on  Mon Jun  5 21:27:57 2017 remi
** Last update Sun Jun 11 18:43:57 2017 remi
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

int			command_msg(t_env *e, int fd_client, char *buf, int r)
{
  (void)r;
  if (send_msg(e, buf) == 1)
    send_msg_fct(e, fd_client, buf);
  else if (send_file(e, buf) == 1)
    send_file_fct(e, fd_client, buf);
  else
    usage(e, fd_client);
  return (0);
}
