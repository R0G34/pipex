/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abausa-v <abausa-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:37:46 by abausa-v          #+#    #+#             */
/*   Updated: 2024/06/21 19:06:48 by abausa-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../includes/garbage_collector.h"

void	open_files(t_fd *fds, int argc, char **argv)
{
	fds->file_in = open(argv[1], O_RDONLY);
	if (fds->file_in < 0)
		perror(argv[1]);
	fds->file_out = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
}

int	main(int argc, char **argv, char **envp)
{
	int		**pipes;
	t_fd	fds;
	int		i;

	if (argc < 5)
		error_message("ERROR. Usage: ./pipex infile ""cmd1"" \
		""cmd2"" outfile\n", 1);
	open_files(&fds, argc, argv);
	pipes = open_pipes(&fds, argc);
	dup2(fds.file_in, pipes[0][0]);
	dup2(fds.file_out, pipes[argc - 3][1]);
	if (pipex(pipes, argc, argv, envp) == false)
		garbage_collector(&fds, pipes, "ERROR: Fork\n", 1);
	close_pipes(pipes, argc - 4);
	while (wait(NULL) != -1 || errno != ECHILD)
		;
	close_fd_pair(pipes[argc - 3][0], pipes[argc - 3][1]);
	close_fd_pair(fds.file_in, fds.file_out);
	i = -1;
	while (pipes[++i])
		free(pipes[i]);
	free(pipes);
	return (0);
}
