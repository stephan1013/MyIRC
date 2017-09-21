/*
** utils.c for utils in /home/stephan/PSU_2016_myirc/Client
**
** Made by stephan
** Login   <stephane.nagamouttou@epitech.eu>
**
** Started on  Sun Jun 11 18:07:51 2017 stephan
** Last update Sun Jun 11 18:30:38 2017 stephan
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include "utils.h"
#include "client.h"

void	sig_handle(int sig)
{
  if (sig == SIGINT)
    {
      dprintf(g_fd_server, "quit\r\n");
      close(g_fd_server);
      exit (0);
    }
}

void	read_server(t_client *client)
{
  client->buffer = get_next_line(g_fd_server);
  printf("%s\r\n", client->buffer);
}

void	free_tab(char **tab)
{
  int	i;

  i = 0;
  while (tab[i] != NULL)
    {
      free(tab[i]);
      ++i;
    }
  free(tab);
}

void	read_fd(t_client *client)
{
  if (FD_ISSET(0, &client->fd_read))
    client->e.fct_read[0](client);
  if (client->e.fd_type[1] != FD_FREE &&
      FD_ISSET(g_fd_server, &client->fd_read))
    client->e.fct_read[1](client);
}

void	set_fd(t_client *client)
{
  if (client->e.fd_type[1] == FD_FREE)
    FD_SET(0, &client->fd_read);
  else
    {
      FD_SET(0, &client->fd_read);
      FD_SET(g_fd_server, &client->fd_read);
    }
}
