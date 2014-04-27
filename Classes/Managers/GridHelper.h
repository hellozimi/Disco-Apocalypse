//
//  GridHelper.h
//  distort-2dx
//
//  Created by Simon Andersson on 26/04/14.
//
//

#ifndef distort_2dx_GridHelper_h
#define distort_2dx_GridHelper_h

#include "cocos2d.h"
#define GRID_SIZE cocos2d::Size(16, 16)
#define GRID(x, y) cocos2d::Size(x*GRID_SIZE.width, y*GRID_SIZE.height)
#define GRID_POSITION(x, y) cocos2d::Point(x*GRID_SIZE.width, y*GRID_SIZE.height)

#endif
