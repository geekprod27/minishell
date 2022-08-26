/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 21:00:27 by nfelsemb          #+#    #+#             */
/*   Updated: 2022/08/25 17:25:50 by nfelsemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/include/libft.h"
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>

# define MAX_TOKENS 12

/* parsing */
int		quote_checker(char *str);
t_list	*tokens_split(char *str);

# define YELLOW "\033[0;33m"
# define RESET "\033[0m"
typedef	enum	e_type
{
	STR = 0,
	PIPE = '|',
	OUT_FILE = '>',
	OUT_FILE_APPEND = '>' + 1,
	IN_FILE = '<',
	IN_HEREDOC = '<' + 1
} t_type;

typedef	struct	s_token
{
	char	*value;
	t_type		type;
} t_token;

/* end parsing */

typedef struct s_pipe	t_pipe;
struct s_pipe
{
	t_pipe	*prev;
	int		in;
	int		out;
	int		pid;
	t_pipe	*next;
};

typedef struct s_cmd
{
	char	*name;
	char	**arg;
	int		fd_in;
	int		fd_out;
}				t_cmd;

typedef struct s_env	t_env;
void	chose(t_env *enviro, t_cmd *cmd);
void	ctrlc(int i);
int		pwd(void);
int		envi( t_env *enviro);
char	*ft_strjoinchar(char const *s1, char const s2);
t_env	*initenv(char **env);
int		export(t_cmd *cmd, t_env *un);
void	changedeb(t_env *un);
int		unset(char *cmd, t_env *un);
int		cd(char	**cmd, t_env	*envi);
int		echo(char	**cmd);
char	*getvale(char *name, t_env *un);
void	lexe(t_cmd *cmd, t_env *envi);
void	exitfree(t_env *un);
void	freeenv(t_env *un);
int		checkname(char *name);
void	exed(t_cmd *cmd, t_env *envi);
char	**getenvchar(t_env *enviro);
void	freetr(char	**pa, char *name, int i);
char	*getna(char *cmd);
void	child(char *path, char **argv, char**env, char *name);
void	coredump(int sig);
void	childctrlc(int sig);
void	freetab(char **tab);
void	addele(t_env *un, char **retsplit);
int		exportun(t_env *un);
int		exportd(char *cmd, t_env *un);
void	piped(t_cmd **retsplit, t_env *enviro);
void	pipe2(t_cmd **retsplit, t_env *enviro, t_pipe *pl);
void	childpipe(int i, t_pipe *pl, t_cmd **retsplit, t_env *enviro);
int		tablen(t_cmd **tab);
char	*heredoc(char *deli);
void	infile(char *path);
void	outfile(char *path);
void	outfileapp(char *path);

struct s_env
{
	t_env	*deb;
	int		haveeq;
	char	*name;
	char	*value;
	t_env	*next;
};

#endif
