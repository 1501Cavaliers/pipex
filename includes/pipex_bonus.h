/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:33:36 by fserpe            #+#    #+#             */
/*   Updated: 2023/10/19 15:30:55 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

# define ERR_INPT "input"
# define ERR_INFILE "infile"
# define ERR_OUTFILE "outfile"
# define ERR_HEREDOC "here_doc"
# define ERR_GNL "get_next_line"
# define ERR_PIPE "pipe"
# define ERR_ENV "env"
# define ERR_CMD "Command"

typedef struct pipex_s
{
	int		fd_in;
	int		fd_out;
	char	*cmd_path;
	char	**cmd_opt;
	char	**path;
	int		*pipe;
	int		here_doc;
	int		idx;
	int		cmd_nb;
	int		pipe_nb;
	pid_t	pid;
}			t_pip;

int		msg(char *str);

int		ft_error(char *str);

void	crash_here_doc(void);

char	*find_path(char **envp);

void	free_pipe(t_pip *pipex);

void	free_tab(char **tab);

void	free_parent(t_pip *pipex);

void	close_pipes(t_pip *pipex);

void	free_child(t_pip *pipex);

void	child(t_pip pi, char **av, char **env);

#endif