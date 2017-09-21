/*
** epur_str.c for epur_str in /home/minikali/projets/PSU_2016_myirc/Lib/utils
** 
** Made by minikali
** Login   <remi.lak@epitech.eu>
** 
** Started on  Sat Jun 10 20:30:11 2017 minikali
** Last update Sat Jun 10 20:30:40 2017 minikali
*/

#include <string.h>
#include "utils.h"

char		*epur_str(char *str)
{
  char		tmp[strlen(str)];
  int		i;
  int		j;

  i = 0;
  j = 0;
  if (!str)
    return (str);
  strcpy(tmp, str);
  while (tmp[i] != 0)
    {
      while (tmp[i] != 0 && is_blank(tmp[i]))
	i++;
      while (tmp[i] != 0 && !is_blank(tmp[i]))
	str[j++] = tmp[i++];
      while (tmp[i] != 0 && is_blank(tmp[i]))
	i++;
      if (tmp[i] != 0)
	str[j++] = ' ';
    }
  str[j] = 0;
  return (str);
}

