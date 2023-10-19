/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:26:40 by fserpe            #+#    #+#             */
/*   Updated: 2023/10/19 15:29:22 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	crash_here_doc(void)
{
	unlink(".heredoc_tmp");
	ft_error(ERR_HEREDOC);
}

void	close_pipes(t_pip *pipex)
{
	int	i;

	i = 0;
	while (i < (pipex->pipe_nb))
	{
		close(pipex->pipe[i]);
		i++;
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}
