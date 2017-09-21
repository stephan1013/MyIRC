/*
** is_blank.c for is_blank in /home/lak_r/rendu/Semester4/Unix_prog/PSU_2016_myirc/v2/Lib/utils
** 
** Made by remi
** Login   <remi.lak@epitech.eu>
** 
** Started on  Thu Jun  8 15:05:32 2017 remi
** Last update Thu Jun  8 15:05:54 2017 remi
*/

int		is_blank(char c)
{
  return (c == ' ' || c == '\t' ? 1 : 0);
}
