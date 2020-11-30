//
//  Light.h
//  RayTracer
//
//  Created by Thi Nguyen  on 10/9/20.
//

#ifndef Light_h
#define Light_h

#include "SceneObject.h"
class Ray;

class Light: public SceneObject{
public:
    Light();
    Light(glm::vec3 pos, float lightInt);
    Light(glm::vec3 pos, float lightInt, string name);
    Light(glm::vec3 pos, float lightInt, ofColor diffuse);
    float getIntensity();
    void setIntensity(float newIntensity);
    void draw();
    void draw(ofColor color);
    virtual bool withinLight(glm::vec3 point);
    bool intersect (Ray &ray, glm::vec3 &point, glm::vec3 &normal); //overload intersection function
    
private:
    float intensity;
};

#endif /* Light_h */
