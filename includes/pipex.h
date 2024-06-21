/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abausa-v <abausa-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:38:45 by abausa-v          #+#    #+#             */
/*   Updated: 2024/06/21 19:08:42 by abausa-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <stdbool.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_fd
{
	int	file_in;
	int	file_out;
}	t_fd;

int		**open_pipes(t_fd *fds, int argc);
char	**envp_parsing(char **envp);
void	do_execve(int i, char **cmd, char **paths, char **envp);
void	my_exec(char **cmd, char **envp);
bool	pipex(int **pipes, int argc, char **argv, char **envp);

#endif