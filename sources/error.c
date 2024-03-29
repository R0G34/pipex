# include "../includes/pipex.h"

void	exit_error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

void	custom_error(char *header, char *msg)
{
	ft_putstr_fd(header, 2);
	ft_putstr_fd(":", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}