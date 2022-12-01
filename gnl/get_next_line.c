/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwattana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:36:56 by nwattana          #+#    #+#             */
/*   Updated: 2022/12/02 00:22:57 by nwattana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 3
#endif

char	*get_next_line(int fd);
char	*ft_strchr(char *str, int n);
void	read_file(char **buffer, int fd);
char 	*ft_strappend(char **str1,char *str2);
char *get_line(char *buff);
void	update_buff(char **buff);
size_t	ft_strlen(char *str);

int	main(void)
{
	int fd = open("test", O_RDONLY);
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("result = \e[1;31m%s\e[0m", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

char	*get_next_line(int fd)
{
	static char *buff;
	char	*res;
	if (fd < 0 | BUFFER_SIZE <= 0 | read(fd, 0, 0) < 0)
		return (NULL);
	if (!buff)
	{
		buff = malloc(1);
		buff[0] = '\0';
	}
//	printf("\e[1;32mbuff = %s\e[0m\n", buff);
	if (*(ft_strchr(buff, '\n')) != '\n')
		read_file(&buff, fd);
	res = get_line(buff);
	update_buff(&buff);
//	printf("\e[1;32mbuff = %s\e[0m\n", buff);
//	printf("\e[1;32mres = %s\e[0m\n", res);

	return (res);
}

char	*ft_strchr(char *str, int n)
{
	char	*tmp;
	tmp = str;
	while (*tmp && *tmp != '\n' && tmp++);
	return (tmp);
}

void	read_file(char **buffer, int fd)
{
	int		size = 0;
	char	*tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));

	tmp[BUFFER_SIZE] = '\0';
	size = read(fd, tmp, BUFFER_SIZE);
	while (size > 0)
	{
		*buffer = ft_strappend(buffer, tmp);
		if (*(ft_strchr(*buffer, '\n')) == '\n')
			break;
		size = read(fd, tmp, BUFFER_SIZE);
	};
	free(tmp);
	tmp = NULL;
}

char 	*ft_strappend(char **str1,char *str2)
{
	size_t len1 = ft_strlen(*str1);
	size_t len2 = ft_strlen(str2);
	char	*tmp;
	int	i = 0;
	int	j = 0;
	char	*res = malloc(sizeof(char) * (len1 + len2 + 1));

	tmp = *str1;
	while (tmp[i])
	{
		res[i] = tmp[i];
		i++;
	}
	while (str2[j])
	{
		res[i + j] = str2[j];
		j++;
	}
	res[i + j] = '\0';
	free(*str1);
	*str1 = NULL;
	return (res);
}

char *get_line(char *buff)
{
	char *res;
	char	*tmp = ft_strchr(buff, '\n');
	int		i = 0;
	
//	printf("\e[1;36mbuff in get_line = |%s| %d\n\e[0m", buff, *buff);
	if (*buff == 0 || ft_strlen(buff) <= 0)
	{
		return (NULL);
	}
	res = malloc(sizeof(char) * (tmp - buff + 2));
	res[tmp - buff + 1] = '\0';
	while (buff + i < tmp)
	{
		*(res + i) = *(buff + i);
		i++;
	}
	*(res + i++) = '\n';
	*(res + i) = '\0';
	return (res);
}

void	update_buff(char **buff)
{
	char	*tmp;
	char	*tmp2;
	char	*res;
	size_t	len;
	int		i = 0;

	tmp = *buff;
	tmp2 = ft_strchr(*buff, '\n');
//	printf("\e[1;33mtmp 2 = |%s|\ntmp = |%s| \n\e[0m",tmp2, tmp);
	if (*tmp2 == '\n')
	{
//		printf("tmp2 = \\n\n");
		len = ft_strlen(++tmp2);
		if (len <= 0)
		{
			free(*buff);
			*buff = NULL;
			return ;
		}
		res = malloc(len + 1);
		res[len] = '\0';
		while (tmp2[i])
		{
//			printf("tmp2[i] = %c\n", tmp2[i]);
			res[i] = tmp2[i];
			i++;
		}
		free(*buff);
		*buff = res;
	}
	else
	{
		free(*buff);
		*buff = NULL;
	}
}

size_t	ft_strlen(char *str)
{
	int	i = 0;

	while (*(str + i++));
	return (i);
}
