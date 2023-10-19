/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:26:19 by fserpe            #+#    #+#             */
/*   Updated: 2023/10/19 15:50:23 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	get_pipes(t_pip *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_nb - 1)
	{
		if (pipe(pipex->pipe + 2 * i) < 0)
			free_parent(pipex);
		i++;
	}
}

void	get_here_doc(char *av, t_pip *pipex)
{
	int		doc;
	char	*buf;

	doc = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (doc < 0)
		ft_error(ERR_HEREDOC);
	while (1)
	{
		write(1, "heredoc> ", 9);
		buf = get_next_line(0);
		if (!buf)
			ft_error(ERR_GNL);
		if (!ft_strncmp(av, buf, ft_strlen(av)))
			break ;
		write(doc, buf, ft_strlen(buf));
		write(doc, "\n", 1);
		free(buf);
	}
	free(buf);
	close(doc);
	pipex->fd_in = open (".heredoc_tmp", O_RDONLY);
	if (pipex->fd_in < 0)
		crash_here_doc();
}

void	get_in_out(int ac, char **av, t_pip *pipex)
{
	if (pipex->here_doc)
	{
		get_here_doc(av[2], pipex);
		pipex->fd_out = open(av[ac - 1], O_RDWR
				| O_CREAT | O_APPEND, 0000644);
		if (pipex->fd_out < 0)
			ft_error(ERR_OUTFILE);
	}
	else
	{
		pipex->fd_in = open(av[1], O_RDONLY);
		if (pipex->fd_in < 0)
			ft_error(ERR_INFILE);
		pipex->fd_out = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0000644);
		if (pipex->fd_out < 0)
			ft_error(ERR_OUTFILE);
	}
}

int	av_count(char *av, t_pip *pipex)
{
	if (!ft_strncmp(av, "here_doc", 9))
	{
		pipex->here_doc = 1;
		return (6);
	}
	else
	{
		pipex->here_doc = 0;
		return (5);
	}
}

int	main(int ac, char **av, char **env)
{
	t_pip	pipex;

	if (ac < av_count(av[1], &pipex))
		ft_error(ERR_INPT);
	get_in_out(ac, av, &pipex);
	pipex.cmd_nb = ac - 3 - pipex.here_doc;
	pipex.pipe_nb = 2 * (pipex.cmd_nb - 1);
	pipex.pipe = malloc(sizeof (int) * pipex.pipe_nb);
	if (!pipex.pipe)
		ft_error(ERR_PIPE);
	pipex.path = ft_split(find_path(env), ':');
	if (!pipex.path)
		free_pipe(&pipex);
	get_pipes(&pipex);
	pipex.idx = -1;
	while (++(pipex.idx) < pipex.cmd_nb)
		child(pipex, av, env);
	close_pipes(&pipex);
	waitpid(-1, NULL, 0);
	free_parent(&pipex);
}
