/*
** channel_pop.c for channel_pop in /home/lak_r/rendu/Semester4/Unix_prog/PSU_2016_myirc/Server/channel_fct
** 
** Made by remi
** Login   <remi.lak@epitech.eu>
** 
** Started on  Sun Jun 11 19:03:48 2017 remi
** Last update Sun Jun 11 19:08:50 2017 remi
*/

#include <stdlib.h>
#include "server.h"

int		channel_pop(t_env *e, t_channel *chan)
{
  t_channel	*ch;

  if (!e->channels)
    return (0);
  ch = e->channels;
  while (1)
    {
      if (ch == chan)
	break;
      ch = ch->next;
      if (ch == e->channels)
	return (0);
    }
  if (ch == e->channels)
    e->channels = e->channels->prev;
  ch->prev->next = ch->next;
  ch->next->prev = ch->prev;
  free(ch);
  return (0);
}
