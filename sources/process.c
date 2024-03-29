#include "../includes/pipex.h"

void	sub_process(int *fd, char **argv, char **envp)
{
	int	fd_in;

	fd_in = open(argv[1], O_RDONLY, 0777);
	if (fd_in == -1)
		exit_error();
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd_in, STDIN_FILENO);
	close(fd[0]);
	run_cmd(argv[2], envp);
}

void	main_process(int *fd, char **argv, char **envp)
{
	int	fd_out;

	fd_out = open(argv[4], o_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_out == -1)
		exit_error();
	dup2(fd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd[1]);
	run_cmd(argv[3], envp);
}