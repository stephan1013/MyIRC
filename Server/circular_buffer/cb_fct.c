/*
** cb_fct.c for cb_fct in /home/lak_r/rendu/Semester4/Unix_prog/PSU_2016_myirc/v2/Server/circular_buffer
** 
** Made by remi
** Login   <remi.lak@epitech.eu>
** 
** Started on  Thu Jun  8 14:20:49 2017 remi
** Last update Sun Jun 11 18:07:46 2017 remi
*/

#include "circular_buffer.h"

int		cb_count_free_space(t_cb *cb)
{
  if (!cb)
    return (-1);
  else if (cb->readp < cb->writep)
    return (cb->writep - cb->readp);
  else
    return ((cb->size - cb->readp) + cb->writep);
}

int			cb_init(t_cb *cb, size_t size)
{
  if (size <= 0)
    {
      dprintf(2, "error: size of the circular buffer has to be positive\n");
      return (1);
    }
  if (!(cb->buffer = malloc(sizeof(char) * size)))
    {
      perror("malloc\n");
      return (1);
    }
  memset(cb->buffer, 0, size);
  cb->readp = 0;
  cb->writep = 0;
  cb->size = size;
  cb->count = 0;
  return (0);
}

void			cb_free(t_cb *cb)
{
  free(cb->buffer);
  cb->readp = 0;
  cb->writep = 0;
  cb->size = 0;
  cb->count = 0;
}
