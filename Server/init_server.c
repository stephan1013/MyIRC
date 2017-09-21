/*
** init_server.c for init_server.c in /home/lak_r/rendu/Semester4/Unix_prog/PSU_2016_myirc/Server
** 
** Made by remi
** Login   <remi.lak@epitech.eu>
** 
** Started on  Mon Jun  5 16:54:12 2017 remi
** Last update Thu Jun  8 21:07:40 2017 minikali
*/

#include <signal.h>
#include <unistd.h>
#include "server.h"

static void		sigpipe_handler(int sig)
{
  printf("Caught SIGPIPE %d\n", sig);
}

static void		sigint_handler(int sig)
{
  int			i;

  i = 0;
  (void)sig;
  while (i < MAX_FD)
    {
      if (e_ext->fd_type[i] != FD_FREE)
	{
	  close(i);
	  e_ext->fd_type[i] = FD_FREE;
	}
      i++;
    }
  if (e_ext->clients != NULL)
    csf_free_all_client(e_ext);
  if (e_ext->channels != NULL)
    chsf_free_all_channel(e_ext);
  exit(0);
}

static int		signal_fct()
{
  if (signal(SIGPIPE, sigpipe_handler) == SIG_ERR)
    {
      perror("signal");
      return (1);
    }
  if (signal(SIGINT, sigint_handler) == SIG_ERR)
    {
      perror("signal");
      return (1);
    }
  return (0);
}

int			init_server(t_env *e, int port, struct timeval *tv)
{
  int			i;
  int			fd_server;

  i = 0;
  if (signal_fct() != 0)
    return (1);
  memset(e->fd_type, FD_FREE, MAX_FD);
  while (i < MAX_FD)
    e->clients[i++] = NULL;
  e->channels = NULL;
  e->port = port;
  if (socket_fct(&fd_server) != 0 ||
      bind_fct(fd_server, port) != 0 ||
      listen_fct(fd_server, 42) != 0)
    return (1);
  e->fd_type[fd_server] = FD_SERVER;
  e->fct_read[fd_server] = accept_client;
  e->fct_write[fd_server] = NULL;
  tv->tv_sec = 20;
  tv->tv_usec = 0;
  e_ext = e;
  return (0);
}
