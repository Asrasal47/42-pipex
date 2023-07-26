/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 03:23:47 by arasal            #+#    #+#             */
/*   Updated: 2023/07/26 17:33:34 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	find_path(char **env)
{
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=/", 6) != 0)
		i++;
	if (!env[i])
		return (-1);
	return (i);
}

static void	set_path_helper(char **path, char ***path1, char ***cmd)
{
	int	i;

	i = 0;
	while ((*path1)[i] != NULL)
	{
		*path = ft_strjoin((*path1)[i++], "/");
		*path = ft_strjoin(*path, *cmd[0]);
		if (!access(*path, F_OK))
			break ;
		free(*path);
	}
	free_str(*path1);
}

char	*set_path(char **env, char *str, char ***cmd)
{
	char	**path1;
	char	*path;
	int		i;

	i = find_path(env);
	if (i == -1)
	{
		*cmd = ft_split(str, ' ');
		if (!access(*cmd[0], F_OK) && !access(*cmd[0], X_OK))
		{
			path = ft_strdup(*cmd[0]);
			return (path);
		}
		return (NULL);
	}
	path1 = ft_split(env[i], '=');
	path1 = ft_split(path1[1], ':');
	*cmd = ft_split(str, ' ');
	if (!access(*cmd[0], F_OK))
	{
		free_str(path1);
		return (*cmd[0]);
	}
	set_path_helper(&path, &path1, cmd);
	return (path);
}

void	ft_exec(char *argv, char **env)
{
	char	**cmd;
	char	*path;

	path = set_path(env, argv, &cmd);
	ft_putstr_fd(argv, 1);
	if (execve(path, cmd, env) == -1)
		ft_error_cmd(cmd);
}

void	ft_pipe(char *argv, char **env)
{
	int		pfd[2];
	int		pid;

	if (pipe(pfd) == -1)
		ft_error();
	pid = fork();
	if (pid < 0)
		ft_error();
	if (pid == 0)
	{
		close(pfd[0]);
		if (dup2(pfd[1], STDOUT_FILENO) == -1)
			ft_error();
		close(pfd[1]);
		ft_exec(argv, env);
	}
	close(pfd[1]);
	if (dup2(pfd[0], STDIN_FILENO) == -1)
		ft_error();
	close(pfd[0]);
	waitpid(pid, NULL, 0);
}
