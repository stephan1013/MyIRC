/*
** get_next_line.c for getnext in /home/stephan/Rendu/Reseau
**
** Made by stephan
** Login   <stephane.nagamouttou@epitech.eu>
**
** Started on  Fri May 19 11:09:32 2017 stephan
** Last update Thu Jun  8 20:21:12 2017 minikali
*/

#include <stdlib.h>
#include <unistd.h>
#include "utils.h"

static char	*my_realloc(char *str, int size)
{
  char		*tmp;
  int		i;

  i = 0;
  if (!(tmp = malloc(sizeof(char) * size)))
    return (NULL);
  while (i < (size - (READ_SIZE + 1)))
    {
      tmp[i] = str[i];
      i = i + 1;
    }
  free(str);
  return (tmp);
}

static char	get_char(const int fd)
{
  static int	pos = 0;
  static char	*pt;
  static char	buff[READ_SIZE];
  char		c;

  if (pos == 0)
    {
      if ((pos = read(fd, buff, READ_SIZE)) == -1)
	return (-1);
      pt = &buff[0];
      if (pos == 0)
	return (0);
    }
  if (fd < 0)
    return (-1);
  c = *pt;
  pt = pt + 1;
  pos = pos - 1;
  return (c);
}

char		*get_next_line(const int fd)
{
  char		c;
  char		*str;
  int		i;

  i = 0;
  if (!(str = malloc(sizeof(char) * READ_SIZE + 1)))
    return (NULL);
  if ((c = get_char(fd)) == -1)
    return (NULL);
  while (c != '\n' && c != '\0')
    {
      str[i] = c;
      if ((c = get_char(fd)) == -1)
	return (NULL);
      i = i + 1;
      if (i % (READ_SIZE + 1) == 0)
	if ((str = my_realloc(str, i + READ_SIZE + 1)) == NULL)
	  return (NULL);
    }
  if (i != 0 && str[i - 1] == '\r')
    str[i - 1] = '\0';
  else
    str[i] = '\0';
  return (str);
}
