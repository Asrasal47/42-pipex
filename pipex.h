/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 22:40:07 by arasal            #+#    #+#             */
/*   Updated: 2022/08/19 00:31:01 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "./Libft/libft.h"

char	*set_path(char **env, char *str, char ***cmd);
char	*set_path2(char **env, char *str, char ***cmd);
void	ft_exec(char *argv, char **env);
void	ft_pipe(char *argv, char **env);
void	ft_error(void);
void	ft_error_infile(char	*file);
void	ft_error_outfile(char	*file);
void	ft_error_cmd(char **cmd);
void	free_str(char **str);

#endif