#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

typedef struct my_gnl
{
	char *str;
	int		len;
	int		nnl;
	int		ret_size;
}		my_gnl;

char *get_next_line(int fd);
void	update_g(my_gnl *gnl, char *res);
char *get_line(my_gnl *gnl);
void	readfile(my_gnl *b, int fd);
char *tn_strjoin(char *s1, char *s2, my_gnl *g);
void *tn_strchr(char *s, int x);
int	tn_strlen(char *s);
#endif
