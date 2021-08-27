/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 16:29:05 by ctirions          #+#    #+#             */
/*   Updated: 2021/08/27 20:38:47 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_error(void)
{
	perror("Error !\n");
	exit(EXIT_FAILURE);
}

void	exec(char *cmd, char **env)
{
	int i;

	i = -1;
	cmd = NULL;
	while (env[++i])
		printf("%s\n", env[i]);
}

void	begin_pipe(char **argv, char **env, int *fd)
{
	int inputfd;

	inputfd = open(argv[1], O_RDONLY);
	if (!inputfd)
		ft_error();
	dup2(fd[1], STDOUT_FILENO);
	dup2(inputfd, STDIN_FILENO);
	close(fd[0]);
	exec(argv[2], env);
}

void	end_pipe(char **argv, char **env, int *fd)
{
	int	outputfile;

	outputfile = open(argv[5], O_WRONLY | O_CREAT);
	if (!outputfile)
		ft_error();
	dup2(fd[0], STDIN_FILENO);
	dup2(outputfile, STDOUT_FILENO);
	close(fd[1]);
	exec(argv[3], env);
}

int main(int argc, char **argv, char **env)
{
	int	fd[2];
	int	pid;

	argc = 0;
	if (pipe(fd) == -1)
		ft_error();
	pid = fork();
	if (pid == -1)
		ft_error();
	if (!pid)
		begin_pipe(argv, env, fd);
	waitpid(pid, 0, 0);
	end_pipe(argv, env, fd);
	close(fd[0]);
	close(fd[1]);
	return (0);
}