/*
** socket_fct.c for socket_fct in /home/lak_r/rendu/Semester4/Unix_prog/PSU_2016_myirc/v2/Server/irc_fct
** 
** Made by remi
** Login   <remi.lak@epitech.eu>
** 
** Started on  Thu Jun  8 15:07:13 2017 remi
** Last update Thu Jun  8 20:35:53 2017 minikali
*/

#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>

int			socket_fct(int *fd)
{
  struct protoent	*pe;

  pe = getprotobyname("TCP");
  if (!pe)
    {
      dprintf(2, "%s\n", "Error: getprotobyname failed\n");
      return (1);
    }
  *fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
  if (*fd == -1)
    {
      perror("socket");
      return (1);
    }
  return (0);
}
