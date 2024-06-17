/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abausa-v <abausa-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 16:26:35 by abausa-v          #+#    #+#             */
/*   Updated: 2024/03/30 16:26:56 by abausa-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

extern char	**environ;

void	child_process1(t_pipex pipex)
{
	char	**args;
	char	*cmd_path;

	args = ft_split(pipex.cmd1, ' ');
	cmd_path = get_cmd_path(args[0], environ);
	if (!cmd_path)
	{
		perror("Command not found");
		free_split(args);
		exit(EXIT_FAILURE);
	}
	dup2(pipex.infile, 0);
	dup2(pipex.pipefd[1], 1);
	close(pipex.pipefd[0]);
	close(pipex.infile);
	close(pipex.pipefd[1]);
	execve(cmd_path, args, environ);
	perror("execve");
	free(cmd_path);
	free_split(args);
	exit(EXIT_FAILURE);
}

void	child_process2(t_pipex pipex)
{
	char	**args;
	char	*cmd_path;

	args = ft_split(pipex.cmd2, ' ');
	cmd_path = get_cmd_path(args[0], environ);
	if (!cmd_path)
	{
		perror("Command not found");
		free_split(args);
		exit(EXIT_FAILURE);
	}
	dup2(pipex.pipefd[0], 0);
	dup2(pipex.outfile, 1);
	close(pipex.pipefd[1]);
	close(pipex.outfile);
	close(pipex.pipefd[0]);
	execve(cmd_path, args, environ);
	perror("execve");
	free(cmd_path);
	free_split(args);
	exit(EXIT_FAILURE);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	*path_var;
	char	**paths;
	char	*cmd_path;
	int		i;

	path_var = getenv("PATH");
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var, ':');
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin_free(cmd_path, cmd, 1);
		if (access(cmd_path, X_OK) == 0)
		{
			free_split(paths);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free_split(paths);
	return (NULL);
}
