/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslik <kslik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:35:07 by kslik             #+#    #+#             */
/*   Updated: 2023/05/21 20:02:19 by kslik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	*strcp_dl3bar(char *dec, char *dp)
{
	int	i;

	i = 0;
	while (dp[i] != '\0')
	{
		dec[i] = dp[i];
		i++;
	}
	dec[i] = '\0';
	return (dec);
}
void	inits(struct s_noopt *no, int c)
{
	if (c == 0)
	{
		no->i = 0;
		no->j = 0;
		no->fl = 0;
		no->l = 0;
		no->p = 0;
		no->q = 0;
	}
	else if (c == 1)
	{
		no->j = 0;
		no->fl = 0;
		no->p = 0;
		no->q = 0;
	}
}
// void casini(struct s_noopt *opt, char **env, char *dec, char ***new_env)
// {
//     inits(opt, 1);
//     opt->l = ft_strlen(env[opt->i]);
//     new_env[opt->i] = malloc((sizeof(char *) * opt->l) + 15);
//     while (opt->j < 11)
//     {
//         new_env[opt->i][opt->j] = dec[opt->j];
//         opt->j++;
//     }
//     while (env[opt->i][opt->q])
//     {
//         if (opt->q > 0 && env[opt->i][opt->q - 1] == '=' && opt->fl == 0)
//         {
//             opt->p++;
//             new_env[opt->i][opt->j++] = '"';
//             opt->fl = 1;
//         }
//         new_env[opt->i][opt->j] = env[opt->i][opt->q];
//         opt->j++;
//         opt->q++;
//     }
//     if (opt->p != 0 || (opt->q > 0 && env[opt->i][opt->q - 1] == '='))
//     {
//         new_env[opt->i][opt->j++] = '"';
//         if (opt->fl != 1)
//             new_env[opt->i][opt->j++] = '"';
//     }
//     new_env[opt->i][opt->j] = '\0';
// }
char	**exp_no_opt(char **env)
{
	struct s_noopt opt;
	char dec[20];
	char **new_env;
	inits(&opt, 0);
	strcp_dl3bar(dec, "declare -x ");
	while (env[opt.i])
		opt.i++;
	new_env = malloc(sizeof(char **) * opt.i + 1);
	opt.i = 0;
	while (env[opt.i])
	{
		inits(&opt, 1);
		opt.l = ft_strlen(env[opt.i]);
		new_env[opt.i] = malloc((sizeof(char *) * opt.l) + 15);
		while (opt.j < 11)
		{
			new_env[opt.i][opt.j] = dec[opt.j];
			opt.j++;
		}
		while (env[opt.i][opt.q])
		{
			if (opt.q > 0 && env[opt.i][opt.q - 1] == '=' && opt.fl == 0)
			{
				opt.p++;
				new_env[opt.i][opt.j++] = '"';
				opt.fl = 1;
			}
			new_env[opt.i][opt.j] = env[opt.i][opt.q];
			opt.j++;
			opt.q++;
		}
		if (opt.p != 0 || (opt.q > 0 && env[opt.i][opt.q - 1] == '='))
		{
			new_env[opt.i][opt.j++] = '"';
			if (opt.fl != 1)
				new_env[opt.i][opt.j++] = '"';
		}
		new_env[opt.i][opt.j] = '\0';
		opt.i++;
	}
	free(env);
	new_env[opt.i] = NULL;
	return (new_env);
}