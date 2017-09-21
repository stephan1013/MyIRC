/*
** my_str_to_wordtab.c for str_to_word_tab in /home/stephan/Rendu/Reseau
**
** Made by stephan
** Login   <stephane.nagamouttou@epitech.eu>
**
** Started on  Fri May 19 13:54:06 2017 stephan
** Last update Wed May 31 11:09:49 2017 stephan
*/

#include <stdlib.h>
#include "client.h"

static char	**one_command(const char *str, char **wordtab)
{
  int		i;

  i = 0;
  while (str[i] != '\0')
    {
      wordtab[0][i] = str[i];
      i++;
    }
  wordtab[0][i] = '\0';
  wordtab[1] = NULL;
  return (wordtab);
}

static char	**two_command(const char *str, char **wordtab)
{
  int		i;
  int		j;

  i = 0;
  j = 0;
  while (str[i] != ' ')
    {
      wordtab[0][i] = str[i];
      i++;
    }
  wordtab[0][i] = '\0';
  i++;
  while (str[i] != '\0')
    {
      wordtab[1][j] = str[i];
      j++;
      i++;
    }
  wordtab[1][j] = '\0';
  wordtab[2] = NULL;
  return (wordtab);
}

static char	**malloc_wordtab(const char *str, char **wordtab)
{
  int	i;
  int	j;

  i = 0;
  j = 0;
  while (str[i] != '\0' && str[i] != ' ')
      i++;
  if (!(wordtab[0] = malloc(i + 1)))
    return (NULL);
  if (str[i] == '\0')
    return (one_command(str, wordtab));
  j = i;
  while (str[j] != '\0')
      j++;
  if (!(wordtab[1] = malloc(((j - i) + 1))))
    return (NULL);
  return (two_command(str, wordtab));
}

char	**command_to_wordtab(const char *str)
{
  char	**wordtab;

  if (str == NULL)
    return (NULL);
  if (!(wordtab = malloc(sizeof(char *) * 3)))
    return (NULL);
  return (malloc_wordtab(str, wordtab));
}
