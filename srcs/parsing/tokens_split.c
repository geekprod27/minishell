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
	int			i;

	ret = NULL;
	strtrim(&str);
	if ((is_whitesp(*str)))
		return (NULL);
	i = -1;
	while (str[++i])
	{
		start = str;
		if (str[i] == '\'' || str[i] == '"')
		{
			str = ft_strchr(start + i + 1, str[i]);
		}
		else if (!is_whitesp(str[i]))
		{
			while (*str && !is_whitesp(*str))
				++str;
			if (is_whitesp(*str))
				*str = 0;
		}
		ft_lstadd_back(&ret, ft_lstnew(mktok(start, ++str - (start + i))));
	}
	return (ret);
}