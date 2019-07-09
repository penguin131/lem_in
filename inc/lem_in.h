/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djeanna <djeanna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 11:54:10 by smight            #+#    #+#             */
/*   Updated: 2019/07/01 11:20:12 by djeanna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "../libft/libft.h"
# include "SDL2/SDL.h"

typedef struct		s_stack
{
	short			is_fake;
	int				nb;
	int				ant_number;
	struct s_stack	*next;
	struct s_stack	*prev;
}					t_stack;

typedef struct		s_solution
{
	int				ways;
	int				*len;
	int				*ants;
	t_stack			**array;
	t_stack			**end;
}					t_solution;

typedef struct		s_lis
{
	char			*name;
	short			is_hold;
	short			is_fake;
	unsigned		i;
	short			used;
	long long		x;
	long long		y;
	float			dx;
	float			dy;
	short			global_hold;
	int				lvl;
	struct s_lis	*next;
	struct s_lis	*reverse;
	struct s_lis	*root;
}					t_lis;

t_lis				*ft_lis_new(char *name, int i);
void				ft_lis_del(t_lis **beg);
t_lis				*ft_lis_copy(t_lis *src);
int					ft_lis_pushback(t_lis **beg, t_lis *new);

typedef struct		s_hasht
{
	t_lis			**arr;
	t_lis			**fakes;
	long long		size;
	long long		top;
	int				num_a;
	t_lis			start;
	t_lis			end;
	int				cnt;
	int				max_ways;
	t_lis			*ant;
	t_solution		*result;
}					t_hasht;

void				ft_hasht_new(t_hasht *new);
int					ft_hasht_add(t_hasht *h, t_lis *a);
void				ft_hash_del(t_hasht *h);
t_lis				*ft_hasht_search(t_hasht *h, char *str, char c);

char				*ft_read(t_hasht *h, int fd, int check);

int					ft_is_data_valid(t_hasht *h, char *str);
char				*skip_until_slashn(char *str);
char				*ft_skip_whitespaces(char *str);
char				*ft_skip_until_whitespaces(char *str);
char				*ft_skip_dig(char *str);
char				*ft_add_rooms2(t_hasht *h, char *str);
char				*ft_skip_until_tire(char *str);

char				*ft_strchr_line(const char *s, int c);
int					ft_strcmp_line(char *str1, char *str2);
char				*ft_help2(char *str, t_hasht *h);
char				*ft_help(char *str);
char				*ft_comments(char *str, int *num_a);

# define ROOT 1
# define LINKS 0
# define FAKES 2
# define ALL_ROOT 3
# define FAKE 1
# define REAL 0

void				push_stack(t_stack **start, t_stack *new);
t_stack				*new_item(int nb, int param);
void				free_stack(t_stack **start);
void				free_program(t_hasht *h);
t_solution			*general_bfs(t_hasht *h, int ways);
int					cycle_bfs(t_hasht *h);
void				zero_htable(t_hasht *h, int param);
void				reverse_links_upgrade(t_hasht *h);
void				get_ants_count(t_hasht *h, t_solution *s);
int					solver(t_hasht *h);
int					get_max_ways(t_hasht *h);
int					get_max(t_solution *s);
void				print_result(t_solution *s, t_hasht *h, int check);
int					get_max(t_solution *s);
char				*ft_find_start(t_hasht *h, char *str);
char				*ft_find_end(t_hasht *h, char *str);
char				*ft_get_ants(char *str, int *num_a);
char				*ft_add_rooms(t_hasht *h, char *str);
void				hold_link(t_hasht *h, int src, int dst);
void				hold_way(t_hasht *h);

typedef struct		s_sdl
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Surface		*bmp;
	SDL_Texture		*bg;
	SDL_Texture		*ant;
	SDL_Texture		*end;
	int				size_sqr;
	int				win_x;
	int				win_y;
	SDL_Texture		*sqr;
	SDL_Rect		srcr;
	SDL_Rect		destr;
}					t_sdl;

void				ft_visu(t_hasht h, t_sdl s, char *str);
int					ft_init(t_sdl *s);
void				ft_quit(t_sdl *s);
void				ft_paste_rooms(t_hasht *h, t_sdl s);
t_lis				*ft_init_ants(t_hasht h);
int					ft_init_rooms(t_hasht *h, t_sdl *s);
void				ft_paste_ants(t_hasht *h, t_lis *ants, t_sdl s);
char				*ft_read_sol();
int					ft_go(t_sdl s, t_hasht h, char **str, t_lis **ants);
int					ft_mv(t_sdl s, t_lis *room, t_hasht *h,
							t_lis *ants);
void				ft_win_size(int x, int y, t_sdl *s);
void				ft_init_l(SDL_Rect *srcr, SDL_Rect *destr, t_sdl s);
void				ft_paste_l(SDL_Rect srcr, SDL_Rect destr, t_sdl s, int i);
void				ft_fill(int x, int y, int lvl, t_lis **l);
void				fake_initialize(t_hasht *h, t_lis *tmp);
void				*free_solution(t_solution *sol);
void				zero(t_hasht *h, int param);
int					ft_strcmp_edge_line(char *str1, char *str2, char c);
int					ft_printf(char *arg, ...);
void				step_tmp_initialize(t_stack **tmp, t_solution *s, int i);

int					ft_shift(t_hasht *h, int x, int y, t_lis **ants);
char				*ft_skip_something(char *str);

#endif
