//
//  RenderCam.cpp
//  RayTracer
//
//  Created by Thi Nguyen  on 9/29/20.
//

#include "RenderCam.h"
#include "Ray.h"

//aligned on z-axis
RenderCam::RenderCam():SceneObject(glm::vec3 (0,0,10), ofColor::green, "RenderCam"){
    aim = glm::vec3 (0,0,-1);
}

//get ray given u and v
Ray RenderCam::getRay (float u, float v){
    glm::vec3 pointOnPlane = view.toWorld(u,v);
    return (Ray (getPosition(), glm::normalize(pointOnPlane - getPosition())));
}

glm::vec3 RenderCam::getAim(){
    return aim;
}

//draw RenderCam as box
void RenderCam::draw(){
    ofSetColor (getDiffuseColor());
    ofNoFill();
    ofDrawBox (getPosition(), 1.0);
    ofSetColor (ofColor::white);
}

//draw RenderCam as box with given color
void RenderCam::draw(ofColor color){
    ofSetColor (color);
    ofNoFill();
    ofDrawBox (getPosition(), 1.0);
    ofSetColor (ofColor::white);
}

//draw frustum from rendercam to viewplane (for debugging purposes)
void RenderCam::drawFrustum(){
    ofSetColor (getDiffuseColor());
    float dist = length((view.toWorld(0,0) - getPosition()));
    getRay(0,0).draw(dist);
    getRay(0,1).draw(dist);
    getRay(1,1).draw(dist);
    getRay(1,0).draw(dist);
    ofSetColor (ofColor::white);
}

//draw 6 x 4 grid on viewplane (for debugging purposes)
void RenderCam::drawGrid(){
    for (int i = -3; i <=3; i++){
        ofDrawLine (glm::vec3 (i, 2, 5), glm::vec3 (i, -2, 5));
    }
    
    for (int i = -2; i<=2; i++){
        ofDrawLine (glm::vec3 (-3, i, 5), glm::vec3 (3, i, 5));
    }
}

//add ray
void RenderCam::addRay(Ray &r){
    rays.push_back (r);
}

//drawRays from renderCam
void RenderCam::drawRays(){
    
    //loop thorugh and draw rays in green color
    for (Ray r: rays){
        ofSetColor(ofColor::green);
        r.draw(50);
    }
}
