/*
** circular_buffer.c for circular_buffer in /home/lak_r/rendu/Semester4/Unix_prog/PSU_2016_myirc/Server
**
** Made by remi
** Login   <remi.lak@epitech.eu>
**
** Started on  Sun Jun  4 09:19:14 2017 remi
** Last update Sun Jun 11 23:36:49 2017 stephan
*/

#include <unistd.h>
#include "circular_buffer.h"

static int		cb_realloc(t_cb *cb, int size)
{
  if (!(cb->buffer = realloc(cb->buffer, cb->size + size + 1)))
    {
      perror("realloc");
      return (1);
    }
  cb->size += size;
  return (0);
}

static void		cb_cpy(char *dest, char *src, int n)
{
  int			i;

  i = 0;
  while (i < n)
    {
      dest[i] = src[i];
      i++;
    }
  dest[i] = 0;
}

static void		write_to_buffer_normal(t_cb *cb, char *str,
					       int read_size)
{
  int			i;

  i = 0;
  while (i < read_size)
    {
      cb->buffer[cb->readp] = str[i];
      cb->readp++;
      if (cb->readp >= cb->size)
	cb->readp = 0;
      i++;
    }
}

int			cb_push_back(t_cb *cb, char *str, int read_size)
{
  int			size;
  char			tmp[cb->size];

  size = (cb->readp < cb->writep ?
	  cb->writep - cb->readp : (cb->size - cb->readp) + cb->writep);
  if (size < read_size)
    {
      cb_cpy(tmp, cb->buffer, cb->size);
      if (cb_realloc(cb, read_size) != 0)
	return (1);
      cb_cpy(cb->buffer, tmp, cb->readp);
      strcat(cb->buffer, str);
      strcat(cb->buffer, tmp + cb->readp);
      cb->readp += strlen(str);
    }
  else
    write_to_buffer_normal(cb, str, read_size);
  return (0);
}

int			cb_pop_front(t_cb *cb, char *buf, int buffsize)
{
  int			size;
  int			i;

  i = 0;
  size = cb->readp < cb->writep ?
    (cb->size - cb->readp) + cb->writep : cb->readp - cb->writep;
  while (i < buffsize && i < size)
    {
      buf[i] = cb->buffer[cb->writep];
      cb->writep++;
      i++;
      if (cb->writep == cb->readp)
	break;
      else if (cb->writep >= cb->size)
	cb->writep = 0;
    }
  buf[i] = 0;
  return (i);
}
