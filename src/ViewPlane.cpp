//
//  ViewPlane.cpp
//  RayTracer
//
//  Created by Thi Nguyen  on 9/29/20.
//

#include <stdio.h>
#include "ViewPlane.h"
using namespace glm;

//construct a View Plane given 2 points
ViewPlane::ViewPlane(glm::vec2 p0, glm::vec2 p1){
    min = p0;
    max = p1;
}

//Construct a View Plane on the Z-axis
ViewPlane::ViewPlane(){ //6 x 4 aspect
    min = glm::vec2(-3, -2);
    max = glm::vec2(3, 2);
    setPosition(glm::vec3(0, 0, 5));
}

//set new size for viewPlane
void ViewPlane::setSize(glm::vec2 min,glm::vec2 max){
    this -> min = min;
    this -> max = max;
}

float ViewPlane::getAspect(){
    return getWidth() / getHeight();
}

//Draw ViewPlane 
void ViewPlane::draw(){
    ofSetColor(ofColor::green);
    ofDrawRectangle(vec3 (min.x, min.y, getPosition().z), getWidth(), getHeight());
}

float ViewPlane::getWidth(){
    return (max.x - min.x);
}

float ViewPlane::getHeight(){
    return (max.y - min.y);
}

//convert u and v to x, y, z
vec3 ViewPlane::toWorld(float u, float v){
    return (vec3 (u * getWidth() + min.x, v * getHeight() + min.y, getPosition().z));
}

