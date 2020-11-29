//
//  ViewPlane.h
//  RayTracer
//
//  Created by Thi Nguyen  on 9/29/20.
//

#ifndef ViewPlane_h
#define ViewPlane_h
#include "Plane.h"
//class Plane;

class ViewPlane: public Plane {
public:
    ViewPlane(glm::vec2 p0, glm::vec2 p1);
    ViewPlane();
    
    void setSize(glm::vec2 min,glm::vec2 max);
    float getAspect();
    
    void draw();
    float getWidth();
    float getHeight();
    
    glm::vec3 toWorld(float u, float v);
    
private:
    glm::vec2 min, max;
};

#endif /* ViewPlane_h */
