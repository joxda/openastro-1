/*****************************************************************************
 *
 * alpha.h -- convert RGB+alpha formats to RGB888 header
 *
 * Copyright 2021
 *   James Fidell (james@openastroproject.org)
 *
 * License:
 *
 * This file is part of the Open Astro Project.
 *
 * The Open Astro Project is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The Open Astro Project is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the Open Astro Project.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 *****************************************************************************/

#ifndef OPENASTRO_VIDEO_ALPHA_H
#define OPENASTRO_VIDEO_ALPHA_H

extern void	oaRGBAtoRGB888 ( void*, void*, unsigned int, unsigned int );
extern void	oaARGBtoRGB888 ( void*, void*, unsigned int, unsigned int );
extern void	oaBGRAtoRGB888 ( void*, void*, unsigned int, unsigned int );
extern void	oaABGRtoRGB888 ( void*, void*, unsigned int, unsigned int );

#endif	/* OPENASTRO_VIDEO_ALPHA_H */
