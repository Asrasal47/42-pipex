/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 22:39:47 by arasal            #+#    #+#             */
/*   Updated: 2022/08/19 00:40:36 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	main(int argc, char **argv, char **env)
{
	int		i;
	int		file[2];

	if (argc != 5)
		ft_error();
	file[0] = open(argv[1], O_RDONLY, 0777);
	if (file[0] == -1)
		ft_error_infile(argv[1]);
	file[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file[1] == -1)
		ft_error_outfile(argv[argc - 1]);
	if (dup2(file[0], STDIN_FILENO) == -1)
		ft_error();
	close(file[0]);
	i = 4;
	ft_pipe(argv[i - 2], env);
	if (dup2(file[1], STDOUT_FILENO) == -1)
		ft_error();
	close(file[1]);
	ft_exec(argv[i - 1], env);
}
