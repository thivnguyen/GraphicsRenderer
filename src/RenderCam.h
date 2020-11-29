//
//  RenderCam.h
//  RayTracer
//
//  Created by Thi Nguyen  on 9/29/20.
//

#ifndef RenderCam_h
#define RenderCam_h

#include "SceneObject.h"
#include "ViewPlane.h"

class RenderCam: public SceneObject{
    
public:
    RenderCam();
    Ray getRay (float u, float v);
    glm::vec3 getAim();
    void draw();
    void drawFrustum();
    void drawGrid();
    void addRay(Ray &r);
    void drawRays();
    void demoRays();
    void draw(ofColor color);
    
private:
    glm::vec3 aim; //point where renderCam is focusing on
    ViewPlane view; //camera viewplane, this is view that it will render
    std::vector<Ray> rays; //stores rays to be drawn (for debugging purposes)
};

#endif /* RenderCam_h */
