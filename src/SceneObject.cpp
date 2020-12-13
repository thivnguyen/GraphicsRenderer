//
//  SceneObject.cpp
//  RayTracer
//
//  Created by Thi Nguyen  on 9/28/20.
//

#include <stdio.h>
#include "SceneObject.h"

using namespace glm;

//Constructs a SceneObject with a given name
SceneObject::SceneObject(string n){
    parent = NULL;
    position = glm::vec3 (0,0,0);
    rotation = glm::vec3 (0,0,0);
    //default position of a SceneObject
    diffuseColor = ofColor:: white; //default color
    specularColor = ofColor:: lightGray;
    name = n;
    setLocalPosition(position);
    selectable = true;
}

//Constructs a SceneObject with a given position, diffuseColor, and name
SceneObject::SceneObject (glm::vec3 pos, ofColor diffuseCol, string n){
    parent = NULL;
    diffuseColor = diffuseCol;
    specularColor = ofColor:: lightGray;
    position = pos;
    rotation = glm::vec3 (0,0,0);
    name = n;
    setLocalPosition(position);
    selectable = true;
}

//Constructs a SceneObject with a given position, diffuseColor, and name
SceneObject::SceneObject (glm::vec3 pos, ofColor diffuseCol, ofColor specularCol, string n){
    parent = NULL;
    diffuseColor = diffuseCol;
    specularColor = ofColor:: lightGray;
    position = pos;
    name = n;
    setLocalPosition(position);
    selectable = true;
    rotation = glm::vec3 (0,0,0);
}

//get name of SceneObject
string SceneObject::getName() {
    return name;
}

//get position of object
glm::vec3 SceneObject::getPosition (){
    //    return position;
    return (getTransformationMatrix() * glm::vec4(0.0, 0.0, 0.0, 1.0));
}

//set new position for SceneObject
void SceneObject::setPosition(glm::vec3 pos){
    position = pos;
}

//get diffuse color of SceneObject
ofColor SceneObject::getDiffuseColor(){
    return diffuseColor;
}

ofColor SceneObject::getSpecularColor(){
    return specularColor;
}

//Sets parentObj as this obj's parent and sets this obj as the parent's children
void SceneObject::setParent(SceneObject* parentObj){
    parent = parentObj;
    if (parent!= NULL){
        //add this to parent's children list
        parent-> children.push_back(this);
        
        //set this local's position calculated from parent's position
        setLocalPosition(position);
    }
}

// set local space position, pos = world space position
void SceneObject::setLocalPosition(glm::vec3 pos){
    //use inverse of parent matrix to set obj's local space position
    if (parent!=NULL){
        localPos = glm::inverse(parent -> getTransformationMatrix()) * glm::vec4(pos, 1.0);
    }
    else{
        localPos = pos;
    }
}

glm::mat4 SceneObject::getTranslationMatrix(){
    return translate(glm::mat4(1.0), glm::vec3(localPos.x, localPos.y, localPos.z));
}

glm::mat4 SceneObject::getRotationMatrix(){
    //euler, rotate (x deg, y deg, z deg)
    return eulerAngleXYZ(glm::radians(rotation.x), radians(rotation.y), radians(rotation.z));
}

//Gets the object's local transformation matrix
glm::mat4 SceneObject::getLocalMatrix(){
    
    // get the local transformations of matrix
    mat4 rotate = getRotationMatrix();
    mat4 trans = getTranslationMatrix();

    return trans * rotate;
}


//gets the objects transformation matrix
glm::mat4 SceneObject::getTransformationMatrix(){
    // if we have a parent (we are not the root),
    // recursively concatenate parent's transformation matrices
    
    //if not root
    if (parent != NULL) {
        return  parent->getTransformationMatrix() * getLocalMatrix() ;
    }
    return getLocalMatrix();
}

//remove sceneobject from parent, return parent
SceneObject* SceneObject::detachParent(){
    SceneObject* temp = parent;
 
    position = getPosition();
    localPos = position;
    
    int i = 0;
    int toDelete = -1;
    if (parent != NULL){
        while (i < (parent -> children).size()){
            SceneObject* child = parent -> children[i];
            if (child == this){
                toDelete = i;
                break;
            }
            i++;
        }

        if (toDelete >=0){
            //remove from children list
            (parent -> children).erase ((parent -> children).begin() + toDelete);
        }
    }
    parent = NULL;
    return temp;
}

// Draw an XYZ axis in RGB at transformed object
void SceneObject::drawAxis(glm::mat4 m, float len) {
    
    ofSetLineWidth(1.0);
    
    // X Axis
    ofSetColor(ofColor(255, 0, 0));
    ofDrawLine(glm::vec3(m*glm::vec4(0, 0, 0, 1)), glm::vec3(m*glm::vec4(len, 0, 0, 1)));
    
    // Y Axis
    ofSetColor(ofColor(0, 255, 0));
    ofDrawLine(glm::vec3(m*glm::vec4(0, 0, 0, 1)), glm::vec3(m*glm::vec4(0, len, 0, 1)));
    
    // Z Axis
    ofSetColor(ofColor(0, 0, 255));
    ofDrawLine(glm::vec3(m*glm::vec4(0, 0, 0, 1)), glm::vec3(m*glm::vec4(0, 0, len, 1)));
}

void SceneObject::setDiffuseColor (ofColor color){
    diffuseColor = color;
}

void SceneObject::setSelectable (bool select){
    selectable = select;
}

bool SceneObject::isSelectable(){
    return selectable;
}

void SceneObject::setRotation (glm::vec3 rotate){
    rotation = rotate;
}

glm::vec3 SceneObject::getRotation(){
    return rotation;
}
