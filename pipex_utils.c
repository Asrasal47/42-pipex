/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 03:23:47 by arasal            #+#    #+#             */
/*   Updated: 2022/08/21 20:36:14 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*set_path(char **env, char *str, char ***cmd)
{
	char	**path1;
	char	*path;
	int		i;

	path1 = ft_split(env[4], '=');
	path1 = ft_split(path1[1], ':');
	*cmd = ft_split(str, ' ');
	if (access(*cmd[0], F_OK) == 0)
	{
		free_str(path1);
		return (*cmd[0]);
	}
	i = 0;
	while (path1[i] != NULL)
	{
		path = ft_strjoin(path1[i++], "/");
		path = ft_strjoin(path, *cmd[0]);
		if (access(path, F_OK) == 0)
			break ;
		free(path);
	}
	free_str(path1);
	return (path);
}

void	ft_exec(char *argv, char **env)
{
	char	**cmd;
	char	*path;

	path = set_path(env, argv, &cmd);
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
