/*
** handle_server.c for handle_server in /home/stephan/PSU_2016_myirc/Client
**
** Made by stephan
** Login   <stephane.nagamouttou@epitech.eu>
**
** Started on  Sun Jun 11 18:18:37 2017 stephan
** Last update Sun Jun 11 18:29:02 2017 stephan
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "client.h"

static void	connect_to_server(t_client *client)
{
  client->host_port = my_str_to_wordtab(client->command[1], ':');
  if (client->host_port[0] != NULL)
    {
      if (!(build_client(client)))
	client->connect = TRUE;
      else
	{
	  close(g_fd_server);
	  g_fd_server = 0;
	  dprintf(2, "Error: invalid port\r\n");
	}
    }
  else
    dprintf(2, "Error: invalid host\r\n");
}

static void	change_server(t_client *client)
{
  if (client->connect != FALSE)
    {
      dprintf(g_fd_server, "QUIT\r\n");
      client->connect = FALSE;
      close(g_fd_server);
      g_fd_server = 0;
      client->e.fd_type[1] = FD_FREE;
      if (client->host_port != NULL)
	free_tab(client->host_port);
    }
  connect_to_server(client);
}

static void	my_capitalize(t_client *client)
{
  int	i;

  if (client->buffer != NULL &&
      client->buffer[0] == '/')
    {
      i = 1;
      while (client->buffer[i] != ' ' &&
	     client->buffer[i] != '\0')
	{
	  client->buffer[i - 1] = client->buffer[i] - 32;
	  ++i;
	}
      while (client->buffer[i] != '\0')
	{
	  client->buffer[i - 1] = client->buffer[i];
	  ++i;
	}
      client->buffer[i - 1] = '\0';
    }
}

void	read_standar(t_client *client)
{
  client->buffer = get_next_line(0);
  client->command = my_str_to_wordtab(client->buffer, ' ');
  my_capitalize(client);
  if (client->command != NULL)
    {
      if (!strncmp(client->buffer, "SERVER", 6) && client->command[1] != NULL)
	change_server(client);
      if (!strncmp(client->buffer, "QUIT", 4))
	{
	  if (g_fd_server != 0)
	    {
	      dprintf(g_fd_server, "QUIT\r\n");
	      close(g_fd_server);
	    }
	  free(client->buffer);
	  free_tab(client->command);
	  if (client->host_port != NULL)
	    free_tab(client->host_port);
	  exit (0);
	}
    }
  if (client->e.fd_type[1] != FD_FREE)
    dprintf(g_fd_server, "%s\r\n", client->buffer);
}
