/*
** strtab.c for strtab in /home/lak_r/rendu/Semester4/Unix_prog/PSU_2016_myirc/Server
**
** Made by remi
** Login   <remi.lak@epitech.eu>
**
** Started on  Mon Jun  5 21:30:16 2017 remi
** Last update Sun Jun 11 18:52:47 2017 remi
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

static int	count_word(char *str, char *del)
{
  int		count;

  count = 0;
  while ((str = strstr(str, del)))
    {
      str += strlen(del);
      count++;
    }
  return (count + 1);
}

static int	distance(char *start, char *end)
{
  int		c;

  c = 0;
  while (start != end)
    {
      start++;
      c++;
    }
  return (c);
}

static char	**fill_tab(char **tab, char *str, char *del)
{
  char		*tmp;
  int		i;
  int		d;

  i = 0;
  while ((tmp = strstr(str, del)))
    {
      if (tmp != str)
	{
	  d = distance(str, tmp);
	  tab[i] = epur_str(strndup(str, d));
	  str += (strlen(tab[i]) + strlen(del));
	  i++;
	}
      else
	str += strlen(del);
    }
  if (*str != 0)
    tab[i++] = epur_str(strndup(str, strlen(str)));
  tab[i] = NULL;
  return (tab);
}

char		**strtab(char *str, char *del)
{
  char		**tab;
  int		count;

  str = epur_str(str);
  if (*str == 0)
    return (NULL);
  count = count_word(str, del);
  if (!(tab = malloc(sizeof(char *) * (count + 1))))
    {
      perror("malloc");
      return (NULL);
    }
  if (!(tab = fill_tab(tab, str, del)))
    return (NULL);
  return (tab);
}
