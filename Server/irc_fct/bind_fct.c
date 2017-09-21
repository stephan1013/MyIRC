/*
** bind_fct.c for bind_fct in /home/lak_r/rendu/Semester4/Unix_prog/PSU_2016_myirc/v2/Server/irc_fct
** 
** Made by remi
** Login   <remi.lak@epitech.eu>
** 
** Started on  Thu Jun  8 15:07:45 2017 remi
** Last update Thu Jun  8 20:36:18 2017 minikali
*/

#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>

int			bind_fct(int socket, int port)
{
  struct sockaddr_in	sin;

  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr  = INADDR_ANY;
  if (bind(socket, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
    {
      perror("bind");
      return (1);
    }
  return (0);
}
