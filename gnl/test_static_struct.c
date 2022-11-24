#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct s_str
{
	char *str;
	int	len;
}		t_string;


int		test(void)
{
	static t_string s;
	
	if (!s.str)
	{
		s.str = malloc(13);
		strcpy(s.str, "hello");
		s.len = strlen(s.str);
	}
	printf("%s\n", s.str);
	s.len++;
	s.str++;
	return (s.len);

}


int	main(void)
{
	int		i;

	printf("%d %d\n",i++, test()); 
	printf("%d %d\n",i++, test()); 
	printf("%d %d\n",i, test()); 
}
