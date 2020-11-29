//
//  Plane.h
//  RayTracer
//
//  Created by Thi Nguyen  on 9/28/20.
//

#ifndef Plane_h
#define Plane_h
#include "SceneObject.h"
class Ray;

class Plane : public SceneObject{
public:
    Plane ();
    Plane (glm::vec3 pos, ofColor diffuseCol, float w, float h, bool horiz);
    float getWidth();
    float getHeight();
    bool intersect (Ray &ray, glm::vec3 &point, glm::vec3 &normal);
    bool isHorizontal();
    void draw();
    glm::vec2 getWidthRange();
    glm::vec2 getHeightRange();
    void draw(ofColor color);
    
private:
    ofPlanePrimitive plane;
    glm::vec3 normal;
    glm::vec2 widthRange;
    glm::vec2 heightRange;
    float width;
    float height;
    bool horizontal;
};

#endif /* Plane_h */
