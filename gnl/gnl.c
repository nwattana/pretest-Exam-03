#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4
#endif

int	read_line(char **s, int fd);
int		checknewline(char *s);
char	*get_line(char **src);
char *get_next_line(int fd);
int tn_strappend(char **dst, char *src);
char tn_strlen(char *s);
char *tn_strdup(char *s);

int	main(void)
{
	int fd = open("test", O_RDONLY);
	char *res;
	int a=23;

	while (a--)
	{
		res = get_next_line(fd);
		if (res == NULL)
			break;
		printf("%s", res);
		free(res);
	}
	close(fd);
//	fd = open("test3",O_RDONLY);
//	res = get_next_line(fd);
//	printf("%s\n", res);
//	free(res);
}

char tn_strlen(char *s)
{
	int	i;

	i = 0;
	while (*(s + i))
		i++;
	return (i);
}

char *tn_strdup(char *s)
{
	char *res;
	char *tmp;

	res = malloc(sizeof(char) * (tn_strlen(s) + 1));
	if (!res)
		return (NULL);
	tmp = res;
	while (*s)
		*tmp++ = *s++;
	*tmp = '\0';
	return (res);
}

int tn_strappend(char **dst, char *src)
{
	char *tmp;
	char	*s_ds;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (**dst == '\0')
	{
		free(*dst);
		*dst = tn_strdup(src);
		return (tn_strlen(*dst));
	}
	s_ds = *dst;
	tmp = malloc(sizeof(char) * (tn_strlen(s_ds) + tn_strlen(src) + 1));
	if (!tmp)
		return (0);
	while (s_ds[i])
	{
		tmp[i] = s_ds[i];
		i++;
	}
	while (src[j])
	{
		tmp[i + j] = src[j];
		j++;
	}
	tmp[i + j] = '\0';
	free(*dst);
	*dst = tmp;
	return (tn_strlen(*dst));
}

int	read_line(char **s, int fd)
{
	char *buffer;
	int	size;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
	buffer[BUFFER_SIZE] = '\0';
	size = read(fd, buffer, BUFFER_SIZE);
	if (size > 0)
		tn_strappend(s, buffer);
	while (size > 0 && !checknewline(*s))
	{
		size = read(fd, buffer, BUFFER_SIZE);
		if (size > 0)
			tn_strappend(s, buffer);
	}
	free(buffer);
	return (size);

}

int		checknewline(char *s)
{
	if (!s)
		return (-1);
	while (*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

char	*get_line(char **src)
{
	char *tmp;
	char *res;
	int		i;
	int		j;


	i = 0;
	j = 0;
	tmp = *src;
	while (tmp[i] != '\n')
		i++;
	res = malloc(sizeof(char) * i + 1);
	if (!res)
		return (NULL);
	while (j <= i)
	{
		res[j] = tmp[j];
		j++;
	}
	res[j] = '\0';

	tmp = malloc(sizeof(char) * tn_strlen(*src + i) + 1);
	if (!tmp)
	{
		free(res);
		return (NULL);
	}
	i++;
	j = 0;
	while (*(*src + i))
	{
		tmp[j] = *(*src + i);
		i++;
		j++;
	}
	free(*src);
	*src = tmp;
	return (res);
}

char *get_next_line(int fd)
{
	static char *but;
	char 		*res;
	char		isend;

//	printf("but at start >|%s|<\n",but);
	isend = 1;
	res = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!but)
	{
		but = malloc(sizeof(char) * 1);
		if (!but)
			return (NULL);
		*but = '\0';
	}
	if (checknewline(but))
	{
//		printf("case 3\n");
		res = get_line(&but);
	}
	else
	{
//		printf("case 4\n");
		isend = read_line(&but, fd);
		if (isend || tn_strlen(but))
			res = get_line(&but);
	}
	if (res == NULL)
		free(but);
//	printf("size of but%d\n",tn_strlen(but));
	if (tn_strlen(but) == 0)
	{
		free(but);
		but = NULL;
	}
//	printf("return val %s\n", res);
//	printf("but at end >|%s|<\n",but);
	return (res);
}
