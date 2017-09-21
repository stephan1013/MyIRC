/*
** free_tab.c for free_tab in /home/minikali/projets/PSU_2016_myirc/Lib/utils
** 
** Made by minikali
** Login   <remi.lak@epitech.eu>
** 
** Started on  Sat Jun 10 21:00:58 2017 minikali
** Last update Sat Jun 10 21:01:45 2017 minikali
*/

#include <stdlib.h>

void		free_tab(char **tab)
{
  int		i;

  i = 0;
  while (tab[i])
    free(tab[i++]);
  free(tab[i]);
  free(tab);
}
