#include <bits/stdc++.h>
#include "../include/physics.h"
float speed(float x, float y)
{
    return sqrt(x*x + y*y);
}
float distance(float x1, float y1, float x2, float y2)
{
    return sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) );
}