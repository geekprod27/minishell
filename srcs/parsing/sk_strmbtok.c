#include "minishell.h"

struct s_block
{
	bool	is_there;
	int		index;
	char	*open;
	char	*close;
};

static void	sk_strmbtok_loop(char **save, char *delimit, struct s_block block)
{
	while (**save)
	{
		if (block.is_there)
		{
			if (block.close[block.index] == **save)
				block.is_there = false;
			++*save;
			continue ;
		}
		if (ft_strchr(block.open, **save))
		{
			block.is_there = true;
			block.index = ft_strchr(block.open, **save) - block.open;
			++*save;
			continue ;
		}
		if (ft_strchr(delimit, **save))
		{
			**save = 0;
			++*save;
			break ;
		}
		++*save;
	}
}

char	*sk_strmbtok(char *input, char *delimit, char *o_blks, char *c_blks)
{
	static char		*save = NULL;
	struct s_block	block;
	char			*lead;

	if (input != NULL)
	{
		save = input;
		lead = input;
	}
	else
	{
		lead = save;
		if (!*save)
			lead = NULL;
	}
	block = (struct s_block){false, 0, o_blks, c_blks};
	sk_strmbtok_loop(&save, delimit, block);
	return (lead);
}
