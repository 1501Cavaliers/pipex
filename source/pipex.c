/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:28:27 by fserpe            #+#    #+#             */
/*   Updated: 2023/11/13 17:24:30 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*get_cmd(char **paths, char *cmd, char **env)
{
	char	*tmp;
	char	*command;
	char	**mt;

	mt = malloc(sizeof(char *) * 1);
	mt[0] = "";
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (access(cmd, 0) == 0)
		{
			execve(cmd, mt, env);
		}
	}
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

void	child_two(t_pip pipex, char **av, char **env)
{
	dup2(pipex.fd_out, 1);
	close(pipex.fd_out);
	close(pipex.fd[1]);
	dup2(pipex.fd[0], 0);
	pipex.cmd_opt = ft_split(av[3], ' ');
	pipex.cmd_path = get_cmd(pipex.path, pipex.cmd_opt[0], env);
	if (!pipex.cmd_path)
	{
		msg(ERR_CMD);
		free_child(&pipex);
		exit (1);
	}
	execve(pipex.cmd_path, pipex.cmd_opt, env);
}

void	child_one(t_pip pipex, char **av, char **env)
{
	dup2(pipex.fd_in, 0);
	close(pipex.fd_in);
	close(pipex.fd[0]);
	dup2(pipex.fd[1], 1);
	pipex.cmd_opt = ft_split(av[2], ' ');
	pipex.cmd_path = get_cmd(pipex.path, pipex.cmd_opt[0], env);
	if (!pipex.cmd_path)
	{
		msg(ERR_CMD);
		free_child(&pipex);
		exit(1);
	}
	execve(pipex.cmd_path, pipex.cmd_opt, env);
}
