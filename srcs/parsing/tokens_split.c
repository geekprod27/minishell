#include "minishell.h"


static int	is_whitesp(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static void *strtrim(char **str)
{
	void	*ptr;
	int		i;

	ptr = *str;
	i = 0;
	while (**str == ' ')
		++*str;
	while ((*str)[i])
		++i;
	while ((*str)[--i] == ' ')
		;
	*(*str + i + 1) = 0;
	return (ptr);
}

t_token *mktok(char *value, size_t len)
{
	t_token	*ret;

	ret = ft_calloc(sizeof(*ret), 1);
	if (!ret)
		return (NULL);
	ret->value = ft_strndup(value, len);
	ret->type = STR;
	value = value + len;
	return (ret);
}

t_list *tokens_split(char *str)
{
	t_list	*ret;
	char		*start;

	ret = NULL;
	strtrim(&str);
	if (is_whitesp(*str))
		return (NULL);
	while (*str)
	{
		start = str;
		if (*str == '\'' || *str == '"')
		{
			str = ft_strchr(str + 1, *str);
		}
		else if (!is_whitesp(*str))
		{
			while (*str && !is_whitesp(*str))
				++str;
			if (is_whitesp(*str))
				*str = 0;
		}
		if (!*start)
			break ;
		ft_lstadd_back(&ret, ft_lstnew(mktok(start, ++str - (start - 1))));
	}
	return (ret);
}