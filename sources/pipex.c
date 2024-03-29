#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	check_envp(envp);
	if (argc == 5)
	{
		if (pipe(fd) == -1)
			exit_error();
		pid = fork();
		if (pid == -1)
			exit_error();
		if (pid == 0)
			sub_process(fd, argv, envp);
		waitpid(pid, NULL, 0);
		main_process(fd, argv, envp);
	}
	else
	{
		
	}
}