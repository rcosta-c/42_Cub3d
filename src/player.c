/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 14:49:46 by cde-paiv          #+#    #+#             */
/*   Updated: 2025/02/14 11:29:54 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int check_collision(t_map *map, double new_x, double new_y)
{
    int map_x = (int)new_x;
    int map_y = (int)new_y;
    
    if (map->map[map_x][map_y] == '1')
        return 0;
    return 1;      // Movimento permitido
}
/* Atualiza o movimento linear do jogador (W, A, S, D) */
void update_linear_movement(t_cub *cub, int key, double *new_x, double *new_y)
{
    if (key == KEY_W)
    {
        *new_x += cub->game.dir_x * MOVE_SPEED;
        *new_y += cub->game.dir_y * MOVE_SPEED;
    }
    else if (key == KEY_S)
    {
        *new_x -= cub->game.dir_x * MOVE_SPEED;
        *new_y -= cub->game.dir_y * MOVE_SPEED;
    }
    else if (key == KEY_A)
    {
        *new_x -= cub->game.plane_x * MOVE_SPEED;
        *new_y -= cub->game.plane_y * MOVE_SPEED;
    }
    else if (key == KEY_D)
    {
        *new_x += cub->game.plane_x * MOVE_SPEED;
        *new_y += cub->game.plane_y * MOVE_SPEED;
    }
}

/* Atualiza a rotação do jogador (setas esquerda e direita) */
void update_rotation(t_cub *cub, int key)
{
    double rot;
    double old_dir_x;
    double old_plane_x;

    if (key == KEY_LEFT || key == KEY_RIGHT)
    {
        rot = (key == KEY_RIGHT) ? ROT_SPEED : -ROT_SPEED;
        old_dir_x = cub->game.dir_x;
        cub->game.dir_x = cub->game.dir_x * cos(rot) - cub->game.dir_y * sin(rot);
        cub->game.dir_y = old_dir_x * sin(rot) + cub->game.dir_y * cos(rot);
        old_plane_x = cub->game.plane_x;
        cub->game.plane_x = cub->game.plane_x * cos(rot) - cub->game.plane_y * sin(rot);
        cub->game.plane_y = old_plane_x * sin(rot) + cub->game.plane_y * cos(rot);
    }
}

/* Função principal para atualização do jogador */
void update_player(t_cub *cub, int key)
{
    double new_x;
    double new_y;

    new_x = cub->game.player_x;
    new_y = cub->game.player_y;
    update_linear_movement(cub, key, &new_x, &new_y);
    update_rotation(cub, key);
    if (check_collision(cub->map, new_x, new_y))
    {
        cub->game.player_x = new_x;
        cub->game.player_y = new_y;
    }
}

// Funcao para tratar os eventos de tecla
int handle_input(int key, t_cub *cub)
{
    if (key == KEY_ESC)
        clean_exit(cub);
    update_player(cub, key);
    
    // apos atualizar, re-renderiza a cena
    render_map(cub);
    mlx_put_image_to_window(cub->game.mlx, cub->game.win, cub->game.img, 0, 0);
    return (0);
}
