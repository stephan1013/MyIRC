/*
** circular_buffer.h for circular_buffer in /home/lak_r/rendu/Semester4/Unix_prog/PSU_2016_myirc/Include
** 
** Made by remi
** Login   <remi.lak@epitech.eu>
** 
** Started on  Sun Jun  4 09:13:19 2017 remi
** Last update Sun Jun 11 21:53:58 2017 minikali
*/

#ifndef _CIRCULAR_BUFFER_H_
# define _CIRCULAR_BUFFER_H_

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define BUFFSIZE 1000

typedef struct		s_cb
{
  char			*buffer;
  size_t		readp;
  size_t		writep;
  size_t		size;
  size_t		count;
}			t_cb;

int			cb_init(t_cb *cb, size_t size);
void			cb_free(t_cb *cb);
int			cb_push_back(t_cb *cb, char *str, int read_size);
int			cb_pop_front(t_cb *cb, char *buf, int buffsize);
int			cb_count_free_space(t_cb *cb);

#endif
