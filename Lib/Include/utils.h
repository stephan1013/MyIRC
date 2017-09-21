/*
** utils.h for utils in /home/lak_r/rendu/Semester4/Unix_prog/PSU_2016_myirc/v2/Lib/Include
** 
** Made by remi
** Login   <remi.lak@epitech.eu>
** 
** Started on  Thu Jun  8 15:03:25 2017 remi
** Last update Sat Jun 10 21:02:34 2017 minikali
*/

#ifndef _UTILS_H_
# define _UTILS_H_

/*
** getnextline
*/
# define READ_SIZE (1)

char *get_next_line(int fd);

/*
** utils
*/

char			**strtab(char *str, char *del);
int			is_blank(char c);
char			*epur_str(char *str);
void			free_tab(char **tab);

#endif /* !_UTILS_H_ */
