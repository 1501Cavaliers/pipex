/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:25:23 by fserpe            #+#    #+#             */
/*   Updated: 2023/10/18 16:16:17 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char **av, char **env)
{
	t_pip	pipex;

	if (ac != 5)
		return (ft_error(ERR_ARG));
	pipex.fd_in = open(av[1], O_RDONLY);
	if (pipex.fd_in < 0)
		return (ft_error(ERR_OPEN));
	pipex.fd_out = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0777);
	if (pipex.fd_out < 0)
		return (ft_error(ERR_OPEN));
	pipex.path = ft_split(find_path(env), ':');
	pip_hub(&pipex, av, env);
	return (0);
}