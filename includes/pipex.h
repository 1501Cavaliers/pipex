/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:17:41 by fserpe            #+#    #+#             */
/*   Updated: 2023/10/20 16:23:47 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

# define ERR_ARG "Invalid number of arguments"
# define ERR_INFILE "Infile"
# define ERR_OUTFILE "Outfile"
# define ERR_PIPE "Pipe"
# define ERR_FORK "Fork"
# define ERR_CMD "Cannot find command"

typedef struct pipex_s
{
	int		fd_in;
	int		fd_out;
	char	*cmd_path;
	char	**cmd_opt;
	char	**arg;
	char	**path;
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
}			t_pip;

int		ft_error(char *str);

char	*find_path(char **envp);

void	free_tab(char **tab);

int		ft_end(t_pip *pipex);

void	close_pipe(t_pip *pipex);

int		free_parent(t_pip *pipex);

int		free_child(t_pip *pipex);

int		msg(char *str);

void	child_one(t_pip pipex, char **av, char **env);

void	child_two(t_pip pipex, char **av, char **env);

#endif