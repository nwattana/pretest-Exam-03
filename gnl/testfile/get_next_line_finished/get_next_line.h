#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
char	*ft_strchr(char *str, int n);
void	read_file(char **buffer, int fd);
char 	*ft_strappend(char **str1,char *str2, int size);
char *get_line(char *buff);
void	update_buff(char **buff);
size_t	ft_strlen(char *str);
void	ft_bzero(char *str, size_t size);

#endif
