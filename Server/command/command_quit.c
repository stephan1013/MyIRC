/*
** command_upper_quit.c for command_upper_quit in /home/lak_r/rendu/Semester4/Unix_prog/PSU_2016_myirc/Server/command
** 
** Made by remi
** Login   <remi.lak@epitech.eu>
** 
** Started on  Wed Jun  7 18:39:27 2017 remi
** Last update Sun Jun 11 18:51:23 2017 remi
*/

#include <unistd.h>
#include "server.h"

int			command_quit(t_env *e, int fd_client, char *buf, int r)
{
  t_client		*client;
  char			msg[100];

  (void)buf;
  (void)r;
  if (!(client = e->clients[fd_client]))
    return (1);
  sprintf(msg, "003 Disconnected\r\n");
  cb_push_back(&client->cb, msg, strlen(msg));
  close(fd_client);
  e->fd_type[fd_client] = FD_FREE;
  return (0);
}

