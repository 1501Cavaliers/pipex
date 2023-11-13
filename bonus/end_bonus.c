/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:26:34 by fserpe            #+#    #+#             */
/*   Updated: 2023/10/23 11:17:34 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	free_pipe(t_pip *pipex)
{
	close(pipex->fd_in);
	close(pipex->fd_out);
	if (pipex->here_doc)
		unlink(".heredoc_tmp");
	free(pipex->pipe);
	msg(ERR_ENV);
	exit(1);
}

void	free_child(t_pip *pipex)
{
	free_tab(pipex->cmd_opt);
	free_tab(pipex->path);
	free(pipex->cmd_path);
	free(pipex->pipe);
}

void	free_parent(t_pip *pipex)
{
	close(pipex->fd_in);
	close(pipex->fd_out);
	if (pipex->here_doc)
		unlink(".heredoc_tmp");
	free_tab(pipex->path);
	free(pipex->pipe);
}

int	ft_error(char *str)
{
	perror(str);
	exit(1);
}

int	msg(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}
