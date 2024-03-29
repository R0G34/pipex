#include "../includes/pipex.h"

void	check_envp(char **envp)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (envp[i++])
		if (ft_strnstr(envp[i], "PATH=", 5) && envp[i][6])
			check = 1;
	if (!check)
	{
		custom_error("Error", "NO VALUES on the environment PATH.");
		exit(1);
	}
}