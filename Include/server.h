/*
** server.h for  in /home/stephan/Rendu/Reseau/PSU_2016_myirc/Include
**
** Made by stephan
** Login   <stephane.nagamouttou@epitech.eu>
**
** Started on  Fri May 26 12:31:53 2017 stephan
** Last update Sun Jun 11 23:34:25 2017 stephan
*/

#ifndef _SERVER_H_
# define _SERVER_H_

# define FD_FREE 0
# define FD_CLIENT 1
# define FD_SERVER 2

# define MAX_FD 255
# define NAME_SIZE 20

# define RNTAG ("\r\n")

# define TABSIZE(x) (sizeof(x) / sizeof(x[0]))

# include "circular_buffer.h"

typedef struct s_env	t_env;

/*
** channel
*/

# define JOIN 1
# define PART 0

typedef struct		s_channel
{
  char			name[NAME_SIZE];
  int			users[MAX_FD];
  struct s_channel	*next;
  struct s_channel	*prev;
}			t_channel;

void			chsf_free_all_channel(t_env *e);
int			chsf_free_single_channel(t_env *e, char *name);
int			add_channel(t_channel **root, char *name);
int			pop_channel(t_channel **root, char *name);
t_channel		*front_channel(t_channel *channel);
t_channel		*back_channel(t_channel *channel);
t_channel		*change_channel(t_channel *channel, int n);
int			seek_channel_by_name(t_channel **channels, char *name);
int			channel_pop(t_env *e, t_channel *chan);

/*
** main
*/

typedef struct		s_client
{
  int			fd;
  char			name[NAME_SIZE];
  t_channel		*channel;
  char			*ip;
  int			port;
  t_cb			cb;
}			t_client;

typedef int		(*fct)(t_env *e, int fd);

typedef struct		s_env
{
  char			fd_type[MAX_FD];
  fct			fct_read[MAX_FD];
  fct			fct_write[MAX_FD];
  int			port;
  t_client		*clients[MAX_FD];
  t_channel		*channels;
}			t_env;
typedef t_env		g_env;

extern g_env		*e_ext;

int			csf_modify_name(t_env *e, int fd_client, char *str);
t_client		*csf_seek_client_by_name(t_env *e, char *name);
void			csf_free_single_client(t_env *e, int fd);
void			csf_free_all_client(t_env *e);
char			*csf_get_name(t_env *e, int fd_client);
int			init_server(t_env *e, int port, struct timeval *tv);
int			read_from_client(t_env *e, fd_set *readfds);
int			write_to_client(t_env *e, fd_set *writefds);
int			client_write(t_env *e, int fd_client);
int			accept_client(t_env *e, int fd);

/*
** irc functions
*/

int			select_fct(t_env *e, fd_set *readfds,
				   fd_set *writefds, struct timeval *tv);
int			socket_fct(int *fd);
int			bind_fct(int socket, int port);
int			listen_fct(int fd, int n);
int			accept_fct(int fd_server, int *fd_client);

/*
** command
*/

typedef struct		s_cmd_fct
{
  char			flag[10];
  int			(*fct)(t_env *e, int fd_client, char *buf, int r);
}			t_cmd_fct;

int			parse_command(t_env *e, int fd_client,
				      char *buf, int r);
int			command_list(t_env *e, int fd_client, char *buf, int r);
int			command_nick(t_env *e, int fd_client, char *buf, int r);
int			command_join(t_env *e, int fd_client, char *buf, int r);
int			command_part(t_env *e, int fd_client, char *buf, int r);
int			command_users(t_env *e, int fd_client,
				      char *buf, int r);
int			command_names(t_env *e, int fd_client,
				      char *buf, int r);
int			command_upper_nick(t_env *e, int fd_client,
					   char *buf, int r);
int			command_quit(t_env *e, int fd_client, char *buf, int r);
int                     command_user(t_env *e, int fd_client,
				     char *buf, int r);
int			command_msg(t_env *e, int fd_client, char *buf, int r);
int			send_msg(t_env *e, char *buf);
int			send_file(t_env *e, char *buf);
int			send_msg_fct(t_env *e, int fd_client, char *buf);
int			send_file_fct(t_env *, int fd_client, char *buf);
char			*cmd_clean_input(char *str, int offset);
void			cmd_get_hour(char hour[5]);
char			*cmd_format_message(t_env *e, int fd_client, char *str);

#endif /* _SERVER_H_ */
