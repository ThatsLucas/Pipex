/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 13:54:16 by lle-duc           #+#    #+#             */
/*   Updated: 2025/01/16 12:35:31 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# define PROGRAMS_PATH "/usr/bin/"

void	print_errors_exit(char *str, int exit_status);
char	*find_path(char *program, char **env);
void	create_pipe(char *av, char **env, int *exit_status, int last);
void	check_files(char **av, int *tab, int ac, int here_doc);
void	execute(char *path, char *av, char **env);
void	here_doc_handle(char *limiter, int fd);
void	prepare_exec_data(char *av, char **env);
char	*try_access_program(char **paths, char *program);
void	manage_parent_side(int in, int out, int *exit_status, int pid);
void	manage_child_side(int *pipefd, int last, char *av, char **env);

#endif
