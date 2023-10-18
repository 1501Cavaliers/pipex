/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:28:27 by fserpe            #+#    #+#             */
/*   Updated: 2023/10/18 16:36:36 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

void	child_two(t_pip *pipex, char **av, char **env)
{
	dup2(pipex->fd_out, 1);
	close(pipex->fd_out);
	close(pipex->fd[1]);
	dup2(pipex->fd[0], 0);
	pipex->cmd_opt = ft_split(av[3], ' ');
	pipex->cmd_path = get_cmd(pipex->path, pipex->cmd_opt[0]);
	if (!pipex->cmd_path)
	{
		free_child(pipex);
		msg(ERR_CMD);
		exit (1);
	}
	execve(pipex->cmd_path, pipex->cmd_opt, env);
}

void	child_one(t_pip *pipex, char **av, char **env)
{
	dup2(pipex->fd_in, 0);
	close(pipex->fd_in);
	close(pipex->fd[0]);
	dup2(pipex->fd[1], 1);
	pipex->cmd_opt = ft_split(av[2], ' ');
	pipex->cmd_path = get_cmd(pipex->path, pipex->cmd_opt[0]);
	if (!pipex->cmd_path)
	{
		free_child(pipex);
		msg(ERR_CMD);
		exit(1);
	}
	execve(pipex->cmd_path, pipex->cmd_opt, env);
}

int	pip_hub(t_pip *pipex, char **av, char **env)
{
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipex->fd) < 0)
		ft_error(ERR_PIPE);
	pid1 = fork();
	if (pid1 < 0)
		ft_error(ERR_FORK);
	if (!pid1)
		child_one(pipex, av, env);
	pid2 = fork();
	if (pid2 < 0)
		ft_error(ERR_FORK);
	if (!pid2)
		child_two(pipex, av, env);
	close_pipe(pipex);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	free_parent(pipex);
	return (1);
}