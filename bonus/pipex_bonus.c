/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pi_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:26:38 by fserpe            #+#    #+#             */
/*   Updated: 2023/10/19 14:22:58 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

void	set_fd(int in, int out)
{
	dup2(in, 0);
	dup2(out, 1);
}

void	child(t_pip pi, char **av, char **env)
{
	pi.pid = fork();
	if (!pi.pid)
	{
		if (pi.idx == 0)
			set_fd(pi.fd_in, pi.pipe[1]);
		else if (pi.idx == pi.cmd_nb - 1)
			set_fd(pi.pipe[2 * pi.idx - 2], pi.fd_out);
		else
			set_fd(pi.pipe[2 * pi.idx - 2], pi.pipe[2 * pi.idx + 1]);
		close_pipes(&pi);
		write(1, "here\n", 6);
		pi.cmd_opt = ft_split(av[2 + pi.idx + pi.here_doc], ' ');
		if (!pi.cmd_opt)
		{
			free_child(&pi);
			ft_error(ERR_CMD);
		}
		pi.cmd_path = get_cmd(pi.path, pi.cmd_opt[0]);
		if (!pi.cmd_path)
		{
			free_child(&pi);
			ft_error(ERR_CMD);
		}
		execve(pi.cmd_path, pi.cmd_opt, env);
	}
}
