/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abausa-v <abausa-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:44:03 by abausa-v          #+#    #+#             */
/*   Updated: 2024/06/21 19:08:53 by abausa-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include "pipex.h"

void	error_message(char *text, int mode);
void	close_fd_pair(int fd1, int fd2);
void	close_pipes(int **pipes, int i);
void	garbage_collector(t_fd *fds, int **pipes, char *text, int mode);
void	free_exec(char *operand, char **cmd, char **paths);

#endif