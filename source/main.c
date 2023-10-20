/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:25:23 by fserpe            #+#    #+#             */
/*   Updated: 2023/10/20 16:22:47 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	set_fd(int ac, char **av, t_pip *pipex)
{
	pipex->fd_in = open(av[1], O_RDONLY);
	if (pipex->fd_in < 0)
		return (ft_error(ERR_INFILE));
	pipex->fd_out = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0777);
	if (pipex->fd_out < 0)
		return (ft_error(ERR_OUTFILE));
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_pip	pipex;

	if (ac != 5)
		return (msg(ERR_ARG));
	set_fd(ac, av, &pipex);
	pipex.path = ft_split(find_path(env), ':');
	if (pipe(pipex.fd) < 0)
		ft_error(ERR_PIPE);
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		ft_error(ERR_FORK);
	if (!pipex.pid1)
		child_one(pipex, av, env);
	pipex.pid2 = fork();
	if (pipex.pid2 < 0)
		ft_error(ERR_FORK);
	if (!pipex.pid2)
		child_two(pipex, av, env);
	close_pipe(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	free_parent(&pipex);
	return (0);
}
