/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_built_ins_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaoud <aessaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:56:57 by kslik             #+#    #+#             */
/*   Updated: 2023/05/23 22:12:57 by aessaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	excpo_case_1(struct s_export *info, t_my_env *tmp, char *ljadid, int fl)
{
	if (fl == 0)
	{
		info->fl = 0;
		while (tmp->val[info->fl] != '=' && info->si == 0 && tmp->val[info->fl])
		{
			if (tmp->val[info->fl] != ljadid[info->fl])
				info->si = 10;
			info->fl++;
		}
		if (info->si != 10)
			info->retu = 1;
	}
	else if (fl == 1)
	{
		info->fl = 0;
		while (ljadid[info->fl] != '=' && ljadid[info->fl])
		{
			if (tmp->val[info->fl] != ljadid[info->fl])
				info->ps = 10;
			info->fl++;
		}
		if (tmp->val[info->fl] != '=')
			info->ps = 10;
	}
}

void	initialize_dt_2(struct s_export *info, int fl)
{
	if (fl == 1)
	{
		info->i = -1;
		info->ps = 0;
		info->si = 0;
		info->retu = 0;
		info->brak = 0;
	}
	if (fl == 0)
	{
		info->ps = 0;
		info->si = 0;
		info->retu = 0;
		info->brak = 0;
	}
}

void	new_node(t_my_env **my_env, char *ljadid)
{
	t_my_env	*new_node;
	t_my_env	*head;

	head = *my_env;
	new_node = malloc(sizeof(t_my_env));
	if (!new_node)
		exit(1);
	new_node->val = ft_strdup(ljadid);
	new_node->next = NULL;
	if (head == NULL)
		*my_env = new_node;
	else
	{
		while (head->next != NULL)
			head = head->next;
		head->next = new_node;
	}
}

void	tmp_val(t_my_env *tmp, char *ljadid, struct s_export *info, int n)
{
	if (n == 0)
	{
		if (info->ps != 10)
		{
			info->k = 200;
			free(tmp->val);
			tmp->val = ft_strdup(ljadid);
		}
	}
	else if (n == 1)
	{
		info->k = 200;
		tmp->val = ft_strdup(ljadid);
		info->brak = 1;
	}
}

void	update_node(t_my_env *t, char *ljadid, struct s_export *in)
{
	while (t != NULL)
	{
		initialize_dt_2(in, 1);
		while (t->val[++in->i])
		{
			initialize_dt_2(in, 0);
			if (t->val[in->i + 1] == '\0' && t->val[in->i] == ljadid[in->i])
				tmp_val(t, ljadid, in, 1);
			if (in->brak == 1)
				break ;
			if (t->val[in->i + 1] == '\0' && t->val[in->i] == ljadid[in->i])
			{
				excpo_case_1(in, t, ljadid, 0);
				if (in->retu == 1)
					return ;
			}
			else if (t->val[in->i] == '=')
			{
				excpo_case_1(in, t, ljadid, 1);
				tmp_val(t, ljadid, in, 0);
				break ;
			}
		}
		t = t->next;
	}
}
