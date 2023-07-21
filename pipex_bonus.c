/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 09:20:47 by arasal            #+#    #+#             */
/*   Updated: 2022/08/19 00:19:38 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_str(char **a)
{
	int		j;

	j = 0;
	if (!a)
		return ;
	while (a[j])
	{
		free (a[j]);
		j++;
	}
	free(a);
	a = NULL;
}

void	open_file(int i, int file[2], char **argv, int argc)
{
	if (i == 1)
	{
		file[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (file[1] == -1)
			ft_error_outfile(argv[argc - 1]);
	}
	else if (i == 2)
	{
		file[0] = open(argv[1], O_RDONLY, 0777);
		if (file[0] == -1)
			ft_error_infile(argv[1]);
		file[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (file[1] == -1)
			ft_error_outfile(argv[argc - 1]);
	}
}

int	main(int argc, char **argv, char **env)
{
	int		i;
	int		file[2];

	if (argc < 5)
		ft_error();
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		i = 4;
		open_file(1, file, argv, argc);
		here_doc_pipe(argv);
	}
	else
	{
		open_file(2, file, argv, argc);
		if (dup2(file[0], STDIN_FILENO) == -1)
			ft_error();
		close(file[0]);
		i = 3;
	}
	while (i++ < argc - 1)
		ft_pipe(argv[i - 2], env);
	if (dup2(file[1], STDOUT_FILENO) == -1)
		ft_error();
	close(file[1]);
	ft_exec(argv[i - 2], env);
}
