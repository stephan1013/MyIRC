/*
** my_str_to_wordtab.c for str_wordtab in /home/stephan/Rendu/PSU_2016_myirc/Client
**
** Made by stephan
** Login   <stephane.nagamouttou@epitech.eu>
**
** Started on  Wed May 31 11:23:21 2017 stephan
** Last update Wed May 31 11:23:24 2017 stephan
*/

#include <stdlib.h>

int	count_words(char *str, char sep)
{
  int	i;
  int	nb;

  i = 0;
  nb = 0;
  if (str == NULL)
    return (0);
  while (str[i] == sep)
    i = i + 1;
  while (str[i] != '\0')
    {
      if (str[i] != sep)
	{
	  while (str[i] != sep && str[i] != '\0')
	    i = i + 1;
	  nb = nb + 1;
	}
      else
	i = i + 1;
    }
  return (nb);
}

int	malloc_wordtab(char *str, char **wordtab, char sep)
{
  int	i;
  int	j;
  int	col;

  i = 0;
  j = 0;
  while (str[i] != '\0')
    {
      col = 0;
      if (str[i] != sep)
	{
	  while (str[i] != sep && str[i] != '\0')
	    {
	      i = i + 1;
	      col = col + 1;
	    }
	  if (!(wordtab[j] = malloc(sizeof(char) * (col + 1))))
	    return (1);
	  j = j + 1;
	}
      else
	i = i + 1;
    }
  return (0);
}

void	fill_tab(char *str, char **wordtab, char sep)
{
  int	i;
  int	j;
  int	col;

  i = 0;
  j = 0;
  while (str[i] != '\0')
    {
      col = 0;
      if (str[i] != sep)
	{
	  while (str[i] != sep && str[i] != '\0')
	    {
	      wordtab[j][col] = str[i];
	      i = i + 1;
	      col = col + 1;
	    }
	  wordtab[j][col] = '\0';
	  j = j + 1;
	}
      else
	i = i + 1;
    }
}

char	**my_str_to_wordtab(char *str, char sep)
{
  char	**wordtab;
  int	nb;
  int	i;

  i = 0;
  if (str == NULL)
    return (NULL);
  while (str[i] != '\0')
    {
      if (str[i] == '\t' || str[i] == '\v')
	str[i] = ' ';
      i = i + 1;
    }
  if ((nb = count_words(str, sep)) == 0)
    return (NULL);
  if (!(wordtab = malloc(sizeof(char *) * (nb + 1))))
    return (NULL);
  if (malloc_wordtab(str, wordtab, sep) != 0)
    return (NULL);
  fill_tab(str, wordtab, sep);
  wordtab[nb] = NULL;
  return (wordtab);
}
