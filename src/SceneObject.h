//
//  SceneObject.h
//  RayTracer
//
//  Created by Thi Nguyen  on 9/28/20.
//

#ifndef SceneObject_h
#define SceneObject_h

#include "ofMain.h"
#include <glm/gtx/intersect.hpp>


class Ray;
class SceneObject {
    
public:
    SceneObject(string n);
    SceneObject(glm::vec3 pos, ofColor diffuseCol, string n);
    SceneObject (glm::vec3 pos, ofColor diffuseCol, ofColor specularCol, string n);
    string getName();
    glm::vec3 getPosition ();
    void setPosition (glm::vec3 pos);
    ofColor getDiffuseColor();
    ofColor getSpecularColor();
    virtual void draw() = 0; //virtual function, needs to overload
    virtual void draw(ofColor color) = 0;
    virtual bool intersect (Ray &ray, glm::vec3 &point, glm::vec3 &normal){return false;};
    void setParent(SceneObject* parentObj);
    void setLocalPosition(glm::vec3 pos);
    glm::mat4 getTranslationMatrix();
    glm::mat4 getTransformationMatrix();
    SceneObject* detachParent();
    void drawAxis(glm::mat4 m, float len);
    void setDiffuseColor (ofColor color);
    void setSelectable (bool select);
    bool isSelectable();
    
private:
    glm::vec3 position;
    ofColor diffuseColor;
    ofColor specularColor;
    string name;
    SceneObject* parent;
    vector <SceneObject *> children;
    glm::vec3 localPos;
    bool selectable;
};

#endif /* SceneObject_h */
