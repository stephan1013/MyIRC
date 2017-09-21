/*
** comment_users.c for commend_users in /home/lak_r/rendu/Semester4/Unix_prog/PSU_2016_myirc/Server/command
**
** Made by remi
** Login   <remi.lak@epitech.eu>
**
** Started on  Mon Jun  5 20:25:28 2017 remi
** Last update Sun Jun 11 22:47:45 2017 minikali
*/

#include <string.h>
#include "server.h"

int			command_users(t_env *e, int fd_client, char *buf, int r)
{
  char			msg[100];
  int			i;

  (void)buf;
  (void)r;
  sprintf(msg, "392 :/users\r\n");
  cb_push_back(&e->clients[fd_client]->cb, msg, strlen(msg));
  i = 0;
  while (i < MAX_FD)
    {
      if (e->fd_type[i] == FD_CLIENT)
	{
	  sprintf(msg, "393 :%s\r\n", e->clients[i]->name);
	  cb_push_back(&e->clients[fd_client]->cb, msg, strlen(msg));
	}
      i++;
    }
  sprintf(msg, "394 :End of users\r\n");
  cb_push_back(&e->clients[fd_client]->cb, msg, strlen(msg));
  return (0);
}
