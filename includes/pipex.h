/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:17:41 by fserpe            #+#    #+#             */
/*   Updated: 2023/10/18 16:19:41 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

# define ERR_ARG "arg"
# define ERR_OPEN "Cannot open file"
# define ERR_PIPE "Pipe"
# define ERR_FORK "Fork"
# define ERR_CMD "Cannot find command"


typedef struct	pipex_s
{
	int	fd_in;
	int	fd_out;
	char	*cmd_path;
	char	**cmd_opt;
	char	**arg;
	char	**path;
	int		fd[2];
}			t_pip;

int		ft_error(char *str);

char	*find_path(char **envp);

void	free_tab(char **tab);

int		ft_end(t_pip *pipex);

void	close_pipe(t_pip *pipex);

int		free_parent(t_pip *pipex);

int		free_child(t_pip *pipex);

int		pip_hub(t_pip *pipex, char **av, char **env);

int		msg(char *str);


#endif