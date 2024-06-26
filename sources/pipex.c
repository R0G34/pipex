/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abausa-v <abausa-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:54:23 by abausa-v          #+#    #+#             */
/*   Updated: 2024/06/21 19:07:53 by abausa-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../includes/garbage_collector.h"

int	**open_pipes(t_fd *fds, int argc)
{
	int	**pipes;
	int	i;

	i = -1;
	pipes = (int **)malloc(sizeof(int *) * (argc - 1));
	if (!pipes)
		garbage_collector(fds, pipes, "ERROR: Malloc\n", 1);
	pipes[argc - 2] = NULL;
	while (++i < argc - 2)
	{
		pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) < 0)
			garbage_collector(fds, pipes, "ERROR: Opening Pipe\n", 1);
	}
	return (pipes);
}

char	**envp_parsing(char **envp)
{
	char	*envp_path;
	char	**paths;
	int		i;

	i = -1;
	while (envp[++i])
		if (ft_strnstr(envp[i], "PATH=", 5))
			break ;
	envp_path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
	if (!envp_path)
		return (NULL);
	paths = ft_split(envp_path, ':');
	if (!paths)
		return (NULL);
	free(envp_path);
	return (paths);
}

void	do_execve(int i, char **cmd, char **paths, char **envp)
{
	char	*binary;
	char	*operand;

	if (access(cmd[0], X_OK) == -1)
	{
		binary = ft_strjoin(paths[i], "/");
		if (!binary)
			error_message("ERROR: Binary Malloc\n", 1);
		operand = ft_strjoin(binary, cmd[0]);
		if (!operand)
			error_message("ERROR: Operand Malloc\n", 1);
		free(binary);
		if (access(operand, X_OK) == -1)
		{
			free(operand);
			return ;
		}
		free_exec(NULL, NULL, paths);
		execve(operand, cmd, envp);
		free_exec(operand, cmd, NULL);
		error_message("ERROR: Execve\n", 0);
	}
	free_exec(NULL, NULL, paths);
	execve(cmd[0], cmd, envp);
	error_message("ERROR: Execve\n", 0);
}

void	my_exec(char **cmd, char **envp)
{
	char	**paths;
	int		i;

	i = -1;
	paths = envp_parsing(envp);
	if (!paths || !cmd)
	{
		free_exec(NULL, cmd, paths);
		error_message("ERROR: Malloc\n", 1);
	}
	while (paths[++i])
		do_execve(i, cmd, paths, envp);
	free_exec(NULL, cmd, paths);
	error_message("ERROR: Acces", 0);
}

bool	pipex(int **pipes, int argc, char **argv, char **envp)
{
	pid_t	id;
	int		i;

	i = -1;
	while (++i < argc - 3)
	{
		id = fork();
		if (id < 0)
			return (false);
		if (id == 0)
		{
			if (dup2(pipes[i][0], 0) < 0 ||
					dup2(pipes[i + 1][1], 1) < 0)
				return (false);
			close_pipes(pipes, argc - 4);
			my_exec(ft_split(argv[i + 2], ' '), envp);
		}
	}
	return (true);
}
