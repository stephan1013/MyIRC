/*
** server.h for  in /home/stephan/Rendu/Reseau/PSU_2016_myirc/Include
**
** Made by stephan
** Login   <stephane.nagamouttou@epitech.eu>
**
** Started on  Fri May 26 12:31:53 2017 stephan
** Last update Sun Jun 11 18:29:11 2017 stephan
*/

#ifndef _CLIENT_H_
# define _CLIENT_H_

#define FD_FREE 0
#define FD_STAND 1
#define FD_SERVER 2
#define MAX_FD 2

#include <arpa/inet.h>

typedef void(*fct)();

typedef struct	s_env
{
  char		fd_type[MAX_FD];
  fct		fct_read[MAX_FD];
  fct		fct_write[MAX_FD];
}		t_env;

typedef enum	s_bool
  {
    FALSE = 0,
    TRUE = 1
  }		t_bool;

typedef struct	s_client
{
  const char	*ip;
  char		*buffer;
  char		**command;
  char		**host_port;
  t_bool	connect;
  fd_set	fd_read;
  t_env		e;
}		t_client;

int		g_fd_server;

char		**my_str_to_wordtab(const char *str, char c);
void		sig_handle(int sig);
void		read_server(t_client *client);
void		free_tab(char **tab);
void		read_fd(t_client *client);
void		set_fd(t_client *client);
void		read_standar(t_client *client);
int             build_client(t_client *client);

#endif /* _CLIENT_H_ */
