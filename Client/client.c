/*
** client.c for client in /home/stephan/PSU_2016_myirc/Client
**
** Made by stephan
** Login   <stephane.nagamouttou@epitech.eu>
**
** Started on  Sun Jun 11 18:05:19 2017 stephan
** Last update Sun Jun 11 18:47:04 2017 stephan
*/

#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "client.h"

static int		config_socket(t_client *client)
{
  struct sockaddr_in	s_in_server;

  s_in_server.sin_family = AF_INET;
  if (client->host_port[1] != NULL)
    s_in_server.sin_port = htons(atoi(client->host_port[1]));
  else
    s_in_server.sin_port = htons(6667);
  s_in_server.sin_addr.s_addr = inet_addr(client->host_port[0]);
  if (connect(g_fd_server, (struct sockaddr *)&s_in_server,
	      sizeof(s_in_server)) == -1)
    return (0);
  client->e.fd_type[1] = FD_SERVER;
  client->e.fct_read[1] = read_server;
  client->e.fct_write[1] = NULL;
  return (1);
}

int			build_client(t_client *client)
{
  struct protoent	*pe;

  if ((pe = getprotobyname("TCP")) == NULL)
    {
      dprintf(2, "Getprotobyname fail\n");
      return (1);
    }
  else if ((g_fd_server = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    {
      dprintf(2, "Creation of socket fail\n");
      return (1);
    }
  else
    if (!(config_socket(client)))
      return (1);
  return (0);
}

void			init_client(t_client *client)
{
  client->connect = FALSE;
  client->e.fd_type[0] = FD_STAND;
  client->e.fct_read[0] = read_standar;
  client->e.fct_write[0] = NULL;
  client->host_port = NULL;
}

static void		handle_client(t_client *client)
{
  init_client(client);
  while (1)
    {
      client->buffer = NULL;
      client->command = NULL;
      FD_ZERO(&client->fd_read);
      set_fd(client);
      if (select(g_fd_server + 1, &client->fd_read, NULL, NULL, NULL) == -1)
	perror("select");
      read_fd(client);
      if (client->buffer != NULL && client->command != NULL)
	{
	  free(client->buffer);
	  free_tab(client->command);
	}
    }
}

int			main(int ac, char **av)
{
  t_client		client;

  (void)av;
  if (ac != 1)
    return (1);
  else
    {
      g_fd_server = 0;
      memset(client.e.fd_type, FD_FREE, MAX_FD);
      signal(SIGINT, sig_handle);
      handle_client(&client);
    }
}
