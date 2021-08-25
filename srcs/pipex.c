/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 16:29:05 by ctirions          #+#    #+#             */
/*   Updated: 2021/08/25 18:21:39 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	arg_error(int argc)
{
	if (argc != 2)
	{
		write(1, "Wrong number of arguments !\n", 28);
		exit(0);
	}
}

char	*make_cmd(char **argv)
{
	char	*cmd;
	int		size_cmd;
	int		i;
	int		j;

	size_cmd = strlen(argv[1]) + strlen(argv[2]) + strlen(argv[3]) + strlen(argv[4]) + 5;
	cmd = malloc(sizeof(char) * size_cmd);
	if (!cmd)
		return (0);
	cmd[size_cmd - 1] = 0;
	i = 0;
	j = -1;
	cmd[0] = '<';
	while (argv[1][++j])
		cmd[++i] = argv[1][j];
	cmd[++i] = ' ';
	j = -1;
	while (argv[2][++j])
		cmd[++i] = argv[2][j];
	j = -1;
	cmd[++i] = '|';
	while (argv[3][++j])
		cmd[++i] = argv[3][j];
	j = -1;
	cmd[++i] = '>';
	while (argv[4][++j])
		cmd[++i] = argv[4][j];
	return (cmd);

}

int	main(int argc, char **argv)
{
	//char	*cmd;
	FILE	*fp;
	char	path[1035];

	fp = popen(argv[1], "r");
	if (!fp)
		return (0);
	while (fgets(path, sizeof(path), fp))
		;//printf("%s", path);
	pclose(fp);
	arg_error(argc);
	//cmd = make_cmd(argv);
	//system(cmd);
	return (0);
}