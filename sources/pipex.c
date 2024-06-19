/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abausa-v <abausa-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 16:27:39 by abausa-v          #+#    #+#             */
/*   Updated: 2024/06/19 11:09:51 by abausa-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	handle_error(const char *msg, int fd1, int fd2)
{
	perror(msg);
	if (fd1 >= 0)
		close(fd1);
	if (fd2 >= 0)
		close(fd2);
	exit(EXIT_FAILURE);
}

void	initialize_pipex(t_pipex *pipex, char **argv)
{
	if (pipe(pipex->pipefd) == -1)
		handle_error("pipe", -1, -1);
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile < 0)
		handle_error("open infile", -1, -1);
	pipex->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile < 0)
		handle_error("open outfile", pipex->infile, -1);
	pipex->cmd1 = argv[2];
	pipex->cmd2 = argv[3];
}

void	create_child_processes(t_pipex *pipex, char **envp)
{
	pipex->child1 = fork();
	if (pipex->child1 == -1)
		handle_error("fork", pipex->infile, pipex->outfile);
	if (pipex->child1 == 0)
		child_process1(*pipex, envp);
	pipex->child2 = fork();
	if (pipex->child2 == -1)
	{
		waitpid(pipex->child1, NULL, 0);
		handle_error("fork", pipex->infile, pipex->outfile);
	}
	if (pipex->child2 == 0)
		child_process2(*pipex, envp);
}

void	close_pipes_and_wait(t_pipex *pipex)
{
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
	close(pipex->infile);
	close(pipex->outfile);
	waitpid(pipex->child1, NULL, 0);
	waitpid(pipex->child2, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
	{
		ft_printf("Usage: ./pipex file1 cmd1 cmd2 file2\n");
		return (1);
	}
	initialize_pipex(&pipex, argv);
	create_child_processes(&pipex, envp);
	close_pipes_and_wait(&pipex);
	return (0);
}
