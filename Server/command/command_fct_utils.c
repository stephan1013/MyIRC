/*
** command_fct_utils.c for command_fct_utils.c in /home/lak_r/rendu/Semester4/Unix_prog/PSU_2016_myirc/v2/Server/command
** 
** Made by remi
** Login   <remi.lak@epitech.eu>
** 
** Started on  Thu Jun  8 15:58:00 2017 remi
** Last update Sun Jun 11 18:26:26 2017 remi
*/

#include <string.h>
#include <time.h>
#include "server.h"
#include "utils.h"

char		*cmd_clean_input(char *str, int offset)
{
  char		*ptr;

  str += offset;
  if ((ptr = strstr(str, "\r\n")))
    *ptr = 0;
  return (str);
}

void		cmd_get_hour(char hour[5])
{
  char		*ptr;
  char		*hh;
  char		*mm;
  time_t	t;

  t = time(NULL);
  ptr = asctime(localtime(&t));
  ptr = strtok(ptr, " ");
  ptr = strtok(NULL, " ");
  ptr = strtok(NULL, " ");
  hh = strtok(NULL, ":");
  mm = strtok(NULL, ":");
  sprintf(hour, "%s:%s", hh, mm);
}

char		*cmd_format_message(t_env *e, int fd_client, char *str)
{
  char		*res;
  char		*nickname;
  char		*channel;
  char		hour[5];

  cmd_get_hour(hour);
  nickname = e->clients[fd_client]->name;
  channel = e->clients[fd_client]->channel->name;
  res = malloc(sizeof(char) * (strlen(hour)
			       + strlen(str) + NAME_SIZE + 9
			       + strlen(channel)));
  if (!res)
    {
      perror("malloc");
      return (NULL);
    }
  if (sprintf(res, "[%s]%s(%s): %s\r\n",
	      hour, nickname, channel, str) == -1)
    {
      perror("sprintf");
      return (NULL);
    }
  return (res);
}
