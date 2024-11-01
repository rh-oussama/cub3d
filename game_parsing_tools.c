#include "cub3d.h"

static int	count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s == c)
			in_word = 0;
		else if (in_word == 0)
		{
			in_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static char	*get_next_word(char **s, char c)
{
	char	*start;
	const char	*end;
	char		*wd;

	while (**s == c)
		(*s)++;
	start = *s;
	while (**s && **s != c)
		(*s)++;
	end = *s;
	wd = ft_substr(start, 0, end - start);
	return (wd);
}

char	**ft_split(char *s, char c)
{
	char	**res;
	int		word_count;
	int		i;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	res = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		res[i] = get_next_word(&s, c);
		if (!res[i])
			return (NULL);
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	error_msg(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	exit(1);
}

char	*ft_strstr(char *str, char *to_find)
{
	int i;
	int j;

	i = 0;
	if (to_find[0] == '\0')
		return (str);
	while (str[i] != '\0')
	{
		j = 0;
		while (str[i + j] != '\0' && str[i + j] == to_find[j])
		{
			if (to_find[j + 1] == '\0')
				return (&str[i]);
			++j;
		}
		++i;
	}
	return (0);
}

int	ft_isalpha_num(int i)
{
	return ((i >= 'A' && i <= 'Z') || (i >= 'a' && i <= 'z') || ('0' <= i && i <= '9'));
}

int ft_is_num(int i)
{
	return ('0' <= i && i <= '9');
}

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int flag;

	res = 0;
	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] && str[i] >= '0' && str[i] <= '9' && str[i] != ' ' && str[i] != '\n')
		{
			flag = 1;
			res = res * 10 + (str[i] - 48);
		}
		i++;
	}
	if (flag == 0)
		error_msg("Invalid color");
	return (res);
}
