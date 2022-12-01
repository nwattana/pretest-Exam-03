/* ************************************************************************** */
#include "get_next_line.h"
/*
#define BUFFER_SIZE 42
int	main(void)
{
	int fd = open("multiple_line_no_nl", O_RDONLY);
	char	*line;
	int		i = 0;

	printf("BUFFER_SIZE = %d\n", BUFFER_SIZE);
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("result = \e[1;31m|%ld|%s|\e[0m",ft_strlen(line), line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);

}
*/
void	ft_bzero(char *str, size_t size)
{
	size_t	i = 0;
	while (i < size)
	{
		str[i] = 0;
		i++;
	}
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
	if (*(ft_strchr(buff, '\n')) != '\n')
		read_file(&buff, fd);
	res = get_line(buff);
	update_buff(&buff);
	return (res);
}

char	*ft_strchr(char *str, int n)
{
	char	*tmp;
	tmp = str;
	while (*tmp && *tmp != n)
	{
		tmp++;
	}
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
		*buffer = ft_strappend(buffer, tmp, size);
		if (*(ft_strchr(*buffer, '\n')) == '\n')
			break;
		ft_bzero(tmp, BUFFER_SIZE);
		size = read(fd, tmp, BUFFER_SIZE);
	};
	free(tmp);
	tmp = NULL;
}

char 	*ft_strappend(char **str1,char *str2,  int size)
{
	size_t len1 = ft_strlen(*str1);
	size_t len2 = ft_strlen(str2);
	char	*tmp;
	int	i = 0;
	int	j = 0;
	char	*res = malloc(sizeof(char) * (len1 + len2 + 1));

	ft_bzero(res, (len1 + len2 + 1));
	tmp = *str1;
	while (tmp[i])
	{
		res[i] = tmp[i];
		i++;
	}
	while (str2[j] && size--)
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
	char	*res;
	char	*tmp;
	int		i = 0;
	
	tmp = ft_strchr(buff, '\n');
	if (*buff == 0 || ft_strlen(buff) <= 0)
		return (NULL);
	res = malloc(sizeof(char) * (tmp - buff + 1 + (*tmp != '\0')));
	ft_bzero(res, tmp - buff + 2);
	while (buff[i] != '\n' && buff[i] != '\0')
	{
		res[i] = buff[i];
		i++;
	}
	if (*tmp != '\0')
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
	if (*tmp2 == '\n')
	{
		++tmp2;
		if (*tmp2 == '\0')
		{
			free(*buff);
			*buff = NULL;
			return ;
		}
		len = ft_strlen(tmp2);
		res = malloc(len + 1);
		res[len] = '\0';
		while (tmp2[i])
		{
			res[i] = tmp2[i];
			i++;
		}
		tmp2[i] = '\0';
		while (tmp <= tmp2)
			*tmp++ = 0;
		free(*buff);
		*buff = res;
	}
	else
	{
		free(*buff);
		*buff = NULL;
	}
}
