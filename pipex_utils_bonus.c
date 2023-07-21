/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 09:23:01 by arasal            #+#    #+#             */
/*   Updated: 2022/08/21 20:36:08 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	here_doc_pipe(char **argv)
{
	int		pfd[2];
	int		pid;

	if (pipe(pfd) == -1)
		ft_error();
	pid = fork();
	if (pid < 0)
		ft_error();
	if (pid == 0)
		here_doc_child(argv, pfd);
	if (dup2(pfd[0], STDIN_FILENO) == -1)
		ft_error();
	close(pfd[0]);
	close(pfd[1]);
	waitpid(pid, NULL, 0);
}

void	here_doc_child(char **argv, int pfd[2])
{
	char	*line;

	while (1)
	{
		close(pfd[0]);
		ft_putstr_fd("pipex_here_doc: ", 1);
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
		{
			free(line);
			exit (0);
		}
		ft_putstr_fd(line, pfd[1]);
		free(line);
	}
}
