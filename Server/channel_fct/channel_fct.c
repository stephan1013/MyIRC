/*
** llist_channel.c for list_channel in /home/lak_r/test_folder
** 
** Made by remi
** Login   <remi.lak@epitech.eu>
** 
** Started on  Tue May 30 13:37:16 2017 remi
** Last update Sun Jun 11 19:02:56 2017 remi
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "server.h"

void			chsf_free_all_channel(t_env *e)
{
  t_channel		*ch;
  t_channel		*tmp;

  ch = e->channels;
  while (ch != ch->next)
    {
      tmp = ch;
      ch->prev->next = ch->next;
      ch->next->prev = ch->prev;
      ch = ch->next;
      free(tmp);
    }
  free(ch);
  e->channels = NULL;
}

int			chsf_free_single_channel(t_env *e, char *name)
{
  t_channel		*ch;
  t_channel		*tmp;

  ch = e->channels;
  while (1)
    {
      if (strcmp(ch->name, name) == 0)
	{
	  tmp = ch;
	  ch->prev->next = ch->next;
	  ch->next->prev = ch->prev;
	  ch = ch->next;
	  if (tmp == tmp->next)
	    e->channels = NULL;
	  else if (e->channels == tmp)
	    e->channels = tmp->next;
	  free(tmp);
	  return (0);
	}
    }
  return (1);
}

int			seek_channel_by_name(t_channel **channels, char *name)
{
  t_channel		*ch;

  if (*channels == NULL)
    return (1);
  ch = *channels;
  while (1)
    {
      if (strcmp(ch->name, name) == 0)
	{
	  *channels = ch;
	  return (0);
	}
      ch = ch->next;
      if (ch == *channels)
	break;
    }
  return (1);
}

static void		fill_channel(t_channel **new, char *name)
{
  strncpy((*new)->name, name, NAME_SIZE);
  memset((*new)->users, PART, MAX_FD);
  (*new)->next = (*new);
  (*new)->prev = (*new);
}

int			add_channel(t_channel **root, char *name)
{
  t_channel		*new;

  if (!(new = malloc(sizeof(t_channel))))
    {
      perror("malloc");
      return (1);
    }
  fill_channel(&new, name);
  if ((*root) == NULL)
    (*root) = new;
  else
    {
      (*root)->prev->next = new;
      new->prev = (*root)->prev;
      (*root)->prev = new;
      new->next = (*root);
      *root = new;
    }
  return (0);
}
