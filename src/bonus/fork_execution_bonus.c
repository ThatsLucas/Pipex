/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_execution_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:33:55 by lle-duc           #+#    #+#             */
/*   Updated: 2025/01/16 11:45:34 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	manage_parent_side(int in, int out, int *exit_status, int pid)
{
	int	wstatus;

	wstatus = 0;
	close(out);
	if (dup2(in, 0) == -1)
		print_errors_exit("ERROR : dup2 failed!\n", EXIT_FAILURE);
	close(in);
	waitpid(pid, &wstatus, 0);
	*exit_status = WEXITSTATUS(wstatus);
}

void	manage_child_side(int *pipefd, int last, char *av, char **env)
{
	close(pipefd[0]);
	if (last < 0)
	{
		if (dup2(pipefd[1], 1) == -1)
			print_errors_exit("ERROR : dup2 failed!\n", EXIT_FAILURE);
	}
	else
	{
		if (dup2(last, 1) == -1)
			print_errors_exit("ERROR : dup2 failed!\n", EXIT_FAILURE);
		close(last);
	}
	close(pipefd[1]);
	prepare_exec_data(av, env);
}
