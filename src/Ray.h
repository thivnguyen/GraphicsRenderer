//
//  Ray.h
//  RayTracer
//
//  Created by Thi Nguyen  on 9/28/20.
//

#ifndef Ray_h
#define Ray_h

#include "ofApp.h"

class Ray{
public:
    Ray (glm::vec3 p, glm::vec3 d);
    glm::vec3 getPoint();
    glm::vec3 getDirection();
    glm::vec3 evalPoint(float time);
    void draw (float time);
    
private:
    glm::vec3 point, direction; //point and direction
};

#endif /* Ray_h */
