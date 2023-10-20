/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:08:03 by fserpe            #+#    #+#             */
/*   Updated: 2023/10/20 16:23:12 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	msg(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (1);
}

void	close_pipe(t_pip *pipex)
{
	close(pipex->fd[0]);
	close(pipex->fd[1]);
}

int	ft_error(char *str)
{
	perror(str);
	exit (0);
}

int	free_parent(t_pip *pipex)
{
	close(pipex->fd_in);
	close(pipex->fd_out);
	free_tab(pipex->path);
	exit (0);
}

int	free_child(t_pip *pipex)
{
	free_tab(pipex->cmd_opt);
	free_tab(pipex->path);
	free(pipex->cmd_path);
	exit (0);
}
