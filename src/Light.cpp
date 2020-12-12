//
//  Light.cpp
//  RayTracer
//
//  Created by Thi Nguyen  on 10/9/20.
//

#include <stdio.h>
#include "Light.h"
#include "Ray.h"

Light::Light():SceneObject ("Light"){
    intensity = 1;
}

//Create a Light object with a given position
Light::Light(glm::vec3 pos, float lightInt):SceneObject (pos,ofColor::white,"Light"){
    intensity = lightInt;
}

//Create a Light object with a given position
Light::Light(glm::vec3 pos, float lightInt, string name):SceneObject (pos,ofColor::white,name){
    intensity = lightInt;
}

Light::Light(glm::vec3 pos, float lightInt, ofColor diffuse): SceneObject(pos, diffuse,"Light"){
    intensity = 1;
}

//Get light intensity
float Light::getIntensity(){
    return intensity;
}

void Light::setIntensity(float newIntensity){
    intensity = newIntensity;
}

//draw light as a sphere
void Light::draw(){
    ofSetColor(getDiffuseColor());
    ofDrawSphere(getPosition(), 0.2);
}

void Light::draw(ofColor color){
    ofSetColor(color);
    ofDrawSphere(getPosition(), 0.2);
}

bool Light::withinLight(glm::vec3 point){
    return true;
}

//check for Sphere intersection
bool Light::intersect (Ray &ray, glm::vec3 &point, glm::vec3 &normal){
    return glm::intersectRaySphere(ray.getPoint(), ray.getDirection(), getPosition(), 0.2, point, normal);
}
