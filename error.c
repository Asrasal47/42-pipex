/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 01:30:40 by arasal            #+#    #+#             */
/*   Updated: 2023/01/05 17:41:02 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(void)
{
	ft_putstr_fd("Syntax Error :\n./pipex infile cmd cmd outfile\n\
Or\n./pipex here_doc LIMITER cmd cmd outfile.", 2);
	exit(0);
}

void	ft_error_infile(char	*file)
{
	if (access(file, F_OK) != 0)
		ft_putstr_fd("pipex: no such file or directory: ", 2);
	else if (access(file, R_OK) != 0)
		ft_putstr_fd("pipex: permission denied: ", 2);
	ft_putendl_fd(file, 2);
	exit(0);
}

void	ft_error_outfile(char	*file)
{
	if (access(file, W_OK) != 0)
		ft_putstr_fd("pipex: permission denied: ", 2);
	ft_putendl_fd(file, 2);
	exit(0);
}

void	ft_error_cmd(char **cmd)
{
	ft_putstr_fd("pipex: command not found: ", 2);
	ft_putendl_fd(cmd[0], 2);
	exit(0);
}
