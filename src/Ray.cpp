//
//  Ray.cpp
//  RayTracer
//
//  Created by Thi Nguyen  on 9/28/20.
//

#include <stdio.h>
#include "Ray.h"

//construct Ray object with given point and direction
Ray::Ray (glm::vec3 p, glm::vec3 d){
    point = p;
    direction = d;
}

//gets point
glm::vec3 Ray::getPoint(){
    return point;
}

//gets direction
glm::vec3 Ray::getDirection(){
    return direction;
}

//find point on Ray, given a time and direction
glm::vec3 Ray::evalPoint(float time){
    return (point + time * direction);
}

//draw Ray with given time
void Ray::draw (float time){
    ofDrawLine (point, evalPoint(time)); //paremeteric equation: p + td
}
