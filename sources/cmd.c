#include "../includes/pipex.h"

void	cmd_path(char *cmd, char **envp)
{
	char	**envp_paths;
	char	*cmd_path;
	int		i;
	char	*only_path;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH=", 5))
		i++;
	envp_paths = ft_split(envp[i] + 5, ":");
	i = 0;
	while (envp_paths[i++])
	{
		only_path = ft_strjoin(envp_paths[i], "/");
		cmd_path = ft_strjoin(only_path, cmd);
		free (only_path);
		if (access(cmd_path, F_OK) == 0)
		{
			free_split(envp_paths);
			return (cmd_path);
		}
		free(cmd_path);
	}
	free_split(envp_path);
	custom_error(cmd, "Command not found");
	return (NULL);
}

void	run_cmd(char *cmd, char **envp)
{
	char	**cmd_flags;
	char	*path;

	cmd_flags = ft_split(cmd, ' ');
	path = cmd_path(cmd_flags[0], envp);
	if (!path)
	{
		free_split(cmd_flags);
		free(path);
		exit(127);
	}
	if (execve(path, cmd_flags, envp) == -1)
	{
		free_split(cmd_flags);
		free(path);
		exit_error();
	}
}