#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int	fd = open("test", O_RDONLY);
	char *res;

	res = get_next_lint(fd);
	printf("%s", res);
	free(res);
}

char	*get_next_line(int fd)
{
	static char *buff;
	char		*res;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (buff)
		{
			free(buff);
			buff = NULL;
		}
		return (NULL);
	}
	if (!buff)
	{
		buff = malloc(sizeof(char));
		*buff = '\0';
	}
	// found new line if return > buff Not found return == buff
	if (*(check_new_line(buff) == 0))
	{
		read_file(buff, fd);
	}
	res = get_line(buff);
}


char	*get_line(char *str)
{
	char *res;
	char	*dst = check_new_line(dst);
	char	*last = check_new_line(dst);
	int	i = 0;
	int	lens=ft_strlen(str);

	if (*(last) == '\0')
	{
		res = malloc(sizeof(char) * (lens + 2));
		res[lens + 1] = '\0';
		res[lens] = '\n';
	}
	else
	{
		res = malloc(sizeof(char) * (len + 1));
		res[len] = '\0';
	}
	while (str + i <= last && str[i])
	{
		res[i] = str[i];
		i++;
	}
	return (res);
}

void	read_file(buff, fd)
{
	char	*res;
	char	*buffer;
	int		size;


	size = 0;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	size = read(fd, buffer, BUFFER_SIZE);
	while (size > 0)
	{
		buff = ft_strappend(buff, buffer);
		if(*(check_new_line(buffer) != '\0')
			break;
		// to set all addr to NULL terminate
		ft_bzero(buffer, BUFFER_SIZE + 1);
		size = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);

}

void	ft_bzero(char *s, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		s[i] = 0;
		i++;
	}
}

char	*ft_strappend(char *buff, char *buffer)
{
	char	*res;
	int		a = ft_strlen(buff);
	int		b = ft_strlen(buffer);
	int		i = 0;
	int		j = 0;

	res = malloc(sizeof(char) * (a + b + 1));
	while (i < a)
	{
		res[i] = buff[i];
		i++;
	}
	while (j < b)
	{
		res[i + j] = buffer[j];
		j++;
	}
	free(buff);
	return (res);
}

char	*check_new_line(char *str)
{
	int	i;
	char *tmp;
	
	tmp = str;
	while (*tmp && *tmp != '\n' && tmp++);
	return (tmp);
}
// tmp[i] = '\n' -> return tmp[i++]

char	*ft_strdup(char *str)
{
	int	size;
	int	i;
	int	*res;
	
	i = 0;
	if (!str)
		return (NULL);
	size = ft_strlen(str);
	res = malloc(sizeof(char) * (size + 1));
	while (*str)
	{
		res[i] = *str++;
		i++;
	}
	return (res);
}

int		ft_strlen(char *str)
{
	int	i;
	
	while (str[i])
		i++;
	return (i);
}
