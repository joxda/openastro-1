/*****************************************************************************
 *
 * scharr.c -- scharr convolution routines
 *
 * Copyright 2015,2023
 *		James Fidell (james@openastroproject.org)
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

#include <oa_common.h>

#if	HAVE_MATH_H
#include <math.h>
#endif

#include "scharr.h"


unsigned long
scharr8 ( uint8_t* source, uint8_t* target, int xSize, int ySize )
{
  uint8_t*	upLeft, *up, *upRight, *left, *right;
  uint8_t*	downLeft, *down, *downRight;
  uint8_t*	t, *p;
  int		sum, x, y, gx, gy;
  unsigned long	score = 0;

  memset ( target, 0, xSize );
  memset ( target + ( ySize - 1 ) * xSize, 0, xSize );

  t = target + xSize;
  y = ySize - 2;
  p = source + xSize + 1;
  while ( y-- ) {
    upLeft = p - xSize - 1;
    up = p - xSize;
    upRight = p - xSize + 1;
    left = p - 1;
    right = p + 1;
    downLeft = p + xSize - 1;
    down = p + xSize;
    downRight = p + xSize + 1;
    x = xSize - 2;
    *t++ = 0;
    while ( x-- ) {
      gx = *upLeft * 3 + *left * 10 + *downLeft * 3 - *upRight * 3 -
          *right * 10 - *downRight * 3;
      gy = *upLeft * 3 + *up * 10 + *upRight * 3 - *downLeft * 3 -
          *down * 10 - *downRight * 3;
      score += gx * gx + gy * gy;
      sum = ( abs ( gx ) + abs ( gy ));
      if ( sum > 255 ) {
        sum = 255;
      }
      *t++ = sum;
      p++;
      upLeft = up; up = upRight; upRight++;
      left++; right++;
      downLeft = down; down = downRight; downRight++;
    }
    p += 2;
    *t++ = 0;
  }

  return score;
}
