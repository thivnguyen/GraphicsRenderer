//
//  Plane.cpp
//  RayTracer
//
//  Created by Thi Nguyen  on 9/28/20.
//

#include <stdio.h>
#include "Plane.h"
#include "Ray.h"

//Construct Plane (horizontal by default)
Plane::Plane () : SceneObject("Plane"){
    width = 40;
    height = 60;
    normal = glm::vec3(0,1,0);
    plane.rotateDeg(90, 1, 0, 0); //plane initally stands vertical, rotate around x-axis 90 degrees
    widthRange = glm::vec2(getPosition().x - width / 2, getPosition().x + width / 2);
    heightRange = glm::vec2(getPosition().z - height / 2, getPosition().z + height / 2);
    horizontal = true;
    setSelectable (false);
}

//Construct Plane with given position, diffuse color, width, height
Plane:: Plane (glm::vec3 pos, ofColor diffuseCol, float w, float h, bool horiz): SceneObject (pos, diffuseCol, "Plane"){
    width = w;
    height = h;
    horizontal = horiz;
    
    //if plane is horizontal
    if (horizontal == true){
        widthRange = glm::vec2(getPosition().x - width / 2, getPosition().x + width / 2);
        heightRange = glm::vec2(getPosition().z - height / 2, getPosition().z + height / 2);
        plane.rotateDeg(90, 1, 0, 0); //plane initally stands vertical, rotate around x-axis 90 degrees
        normal = glm::vec3(0,1,0); //y-axis
    }
    
    //if plane is vertical
    else{
        widthRange = glm::vec2(getPosition().x - width / 2, getPosition().x + width / 2);
        heightRange = glm::vec2(getPosition().y - height / 2, getPosition().y + height / 2);
        normal = glm::vec3(0,0,1); //z-axis
    }
    setSelectable (false);
    
}

//check if ray intersects plane
bool Plane::intersect (Ray &ray, glm::vec3 &point, glm::vec3 &normal){
    float distance; //distance of intersection between ray and point
    bool insidePlane = false; //ray inside plane
    bool hit = glm::intersectRayPlane (ray.getPoint(), ray.getDirection(), getPosition(), this -> normal, distance);
    if (hit){
        point = ray.evalPoint (distance); //caclulate point of intersection
        normal = this -> normal;
        if (point.x < widthRange[1] && point.x > widthRange[0] && point.z < heightRange[1] && point.z > heightRange[0])
        {
            insidePlane = true;
        }
    }
    return insidePlane;
}

//draw plane
void Plane::draw(){
    ofSetColor(getDiffuseColor());
    plane.setPosition(getPosition());
    plane.setWidth(width);
    plane.setHeight(height);
    plane.setResolution(4, 4); //set #columns and #rows
    plane.drawWireframe();
}

//draw plane
void Plane::draw(ofColor color){
    ofSetColor(color);
    plane.setPosition(getPosition());
    plane.setWidth(width);
    plane.setHeight(height);
    plane.setResolution(4, 4); //set #columns and #rows
    plane.drawWireframe();
}

float Plane::getWidth(){
    return width;
}

float Plane::getHeight(){
    return height;
}

//get width range of plane
glm::vec2 Plane::getWidthRange(){
    return widthRange;
}

//get height range of plane
glm::vec2 Plane::getHeightRange(){
    return heightRange;
}

//returns true if plane is horizontal
bool Plane::isHorizontal(){
    return horizontal;
}


