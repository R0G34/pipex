#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>

/*ERROR*/

void	exit_error(void);
void	custom_error(char *header, char *msg);

/*CHECKER*/

void	check_envp(char **envp);

/*PROCESS*/

void	sub_process(int	*fd, char **argv, char **envp);
void	main_process(int	*fd, char **argv, char **envp);

/*cmd*/

char	*cmd_path(char *cmd, char **envp);
void	run_cmd(char *cmd, char **envp);

/*FREE*/

void	free_split(char **str);

#endif