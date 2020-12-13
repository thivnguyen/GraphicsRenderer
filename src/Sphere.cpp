//
//  Sphere.cpp
//  RayTracer
//
//  Created by Thi Nguyen  on 9/28/20.
//

#include <stdio.h>
#include "Sphere.h"
#include "Ray.h"

//Constructs a sphere
Sphere::Sphere():SceneObject("Sphere"){
    radius = 1.0;
}

//Constructs a sphere with given position, radius size, and diffuse color
Sphere::Sphere (glm::vec3 pos, float r, ofColor diffCol) : SceneObject(pos, diffCol, "Sphere"){
    radius = r;
}

//Get Sphere Radius
float Sphere::getRadius (){
    return radius;
}

void Sphere::setRadius (float r){
    radius = r;
}

//check for Sphere intersection
bool Sphere::intersect (Ray &ray, glm::vec3 &point, glm::vec3 &normal){
    return glm::intersectRaySphere(ray.getPoint(), ray.getDirection(), getPosition(), radius, point, normal);
}

//draw sphere
void Sphere::draw(){
    ofNoFill(); //don't fill in spheres
  //  ofSetColor (getDiffuseColor());
 //   ofDrawSphere (getPosition(), radius);
    ofSetColor (getDiffuseColor());
    glm::mat4 m = getTransformationMatrix();
    ofPushMatrix();
    ofMultMatrix(m);
    ofDrawSphere(radius);
    ofPopMatrix();
    drawAxis(m,1.5);
}

void Sphere::draw(ofColor color){
     ofNoFill();
    ofSetColor (color);
 //   ofDrawSphere(getPosition(), radius);
    
    //   push the current stack matrix and multiply by this object's
    //   matrix. now all vertices drawn will be transformed by this matrix
    //
    glm::mat4 m = getTransformationMatrix();
    ofPushMatrix();
    ofMultMatrix(m);
    ofDrawSphere(radius);
    ofPopMatrix();
    drawAxis(m,1.5);
}
