/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abausa-v <abausa-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 15:28:05 by abausa-v          #+#    #+#             */
/*   Updated: 2024/03/30 16:28:07 by abausa-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>

void	sub_process(int *fd, char **argv, char **envp);
void	main_process(int *fd, char **argv, char **envp);
void	exit_error(void);
void	custom_error(char *header, char *msg);
void	free_split(char **str);
char	*get_cmd_path(char *cmd, char **envp);
void	run_cmd(char *cmd, char **envp);

#endif
