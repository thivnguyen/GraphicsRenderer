//
//  Sphere.h
//  RayTracer
//
//  Created by Thi Nguyen  on 9/28/20.
//

#ifndef Sphere_h
#define Sphere_h

#include "SceneObject.h"

class Sphere: public SceneObject {
public:
    Sphere();
    Sphere (glm::vec3 pos, float r, ofColor diffCol);
    float getRadius();
    bool intersect (Ray &ray, glm::vec3 &point, glm::vec3 &normal); //overload intersection function
    void draw();
    void draw(ofColor color);
    
private:
    float radius;
};

#endif /* Sphere_h */
