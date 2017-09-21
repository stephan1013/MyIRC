/*
** listen_fct.c for listen_fct in /home/lak_r/rendu/Semester4/Unix_prog/PSU_2016_myirc/v2/Server/irc_fct
** 
** Made by remi
** Login   <remi.lak@epitech.eu>
** 
** Started on  Thu Jun  8 15:08:04 2017 remi
** Last update Thu Jun  8 20:35:17 2017 minikali
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

int			listen_fct(int fd, int n)
{
  if (listen(fd, n) == -1)
    {
      perror("listen");
      return (1);
    }
  return (0);
}
