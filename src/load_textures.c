/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-paiv <cde-paiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 14:47:30 by cde-paiv          #+#    #+#             */
/*   Updated: 2025/02/09 17:01:02 by cde-paiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void load_textures(t_game *game, t_map *map)
{
    int i;

    // Aloca espaço para 4 texturas
    game->texture = malloc(sizeof(t_tex) * 4);
    if (!game->texture)
        exit(EXIT_FAILURE);
    // Associa cada textura ao respectivo arquivo
    game->texture[0].path = map->no_file;
    game->texture[1].path = map->so_file;
    game->texture[2].path = map->we_file;
    game->texture[3].path = map->ea_file;
    
    for (i = 0; i < 4; i++)
    {
        game->texture[i].img = mlx_xpm_file_to_image(game->mlx, 
                                                       game->texture[i].path, 
                                                       &game->texture[i].width, 
                                                       &game->texture[i].height);
        if (!game->texture[i].img)
            exit(EXIT_FAILURE);
        game->texture[i].addr = (int *)mlx_get_data_addr(game->texture[i].img, 
                                                         &game->texture[i].bpp, 
                                                         &game->texture[i].line_len, 
                                                         &game->texture[i].endian);
    }
}
