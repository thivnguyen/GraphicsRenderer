//
//  Spotlight.cpp
//  RayTracerWSpotlight
//
//  Created by Thi Nguyen  on 10/14/20.
//

#include <stdio.h>
#include "Spotlight.h"


//Construct a Spotlight with a given position, light intensity, cone angle, and point of aim
Spotlight::Spotlight(glm::vec3 pos, float lightInt, float angle, glm::vec3 aim):Light (pos, lightInt, "Spotlight"){
    coneAngle = angle;
    lightAim = aim;
}

//draw the spotlight
void Spotlight::draw(){
    ofSetColor (ofColor::white);
    ofDrawSphere(getPosition(), 0.2);
    ofDrawLine(getPosition(), lightAim);
}

//returns true if the point is within the spotlight
bool Spotlight::withinLight(glm::vec3 point){
    
    //vector from spotlight to where light is aiming
    glm::vec3 lightDir(lightAim - getPosition());
    
    //vector from spotlight to intersection point
    glm::vec3 lightToPt(point - getPosition());
    
    //find angle between the 2 vectors
    float angleBtwn = glm::degrees(angle (normalize(lightDir), normalize(lightToPt)));
    
    //check whether the angle * 2 is < the cone angle since the lightDir vector bisects the angle
    return angleBtwn * 2<= coneAngle;
    
}


void Spotlight::setAngle (float newAngle){
    coneAngle = newAngle;
}
