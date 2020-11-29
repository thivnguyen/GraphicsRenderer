//
//  Spotlight.h
//  RayTracerWSpotlight
//
//  Created by Thi Nguyen  on 10/14/20.
//

#ifndef Spotlight_h
#define Spotlight_h
#include "ofMain.h"
#include "Light.h"

class Spotlight: public Light {

public:
    Spotlight(glm::vec3 pos, float lightInt, float angle, glm::vec3 aim);
    void draw();
    bool withinLight(glm::vec3 point);
    void setAngle (float newAngle);
    
private:
    float coneAngle;
    glm::vec3 lightAim;
};

#endif /* Spotlight_h */
