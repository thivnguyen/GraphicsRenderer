//
//  AreaLight.cpp
//  GraphicsRenderer
//
//  Created by Thi Nguyen  on 11/25/20.
//

#include <stdio.h>
#include "AreaLight.h"

AreaLight::AreaLight (glm::vec3 pos, float lightInt):Light (pos, lightInt, "AreaLight"){
    width = 2.5;
    height = 2.5;
    numRows = 5;
    numColumns = 5;
    lightArea.rotateDeg(90, 1, 0, 0); //plane initally stands vertical, rotate around x-axis 90 degrees
    widthRange = glm::vec2(getPosition().x - width / 2, getPosition().x + width / 2);
    heightRange = glm::vec2(getPosition().z - height / 2, getPosition().z + height / 2);
    normal = glm::vec3 (0, 1, 0);
    isHorizontal = true;
    
    cout << widthRange << endl;
    cout << heightRange << endl;
    cout << getPosition() << endl;
}

AreaLight::AreaLight (glm::vec3 pos, float lightInt, bool horizontal){
    width = 2.5;
    height = 2.5;
    numRows = 5;
    numColumns = 5;
    isHorizontal = horizontal;
    
    if (isHorizontal){
        lightArea.rotateDeg(90, 1, 0, 0); //plane initally stands vertical, rotate around x-axis 90 degrees
        widthRange = glm::vec2(getPosition().x - width / 2, getPosition().x + width / 2);
        heightRange = glm::vec2(getPosition().z - height / 2, getPosition().z + height / 2);
        normal = glm::vec3 (0, 1, 0);
    }
    else{
        widthRange = glm::vec2(getPosition().x - width / 2, getPosition().x + width / 2);
        heightRange = glm::vec2(getPosition().y - height / 2, getPosition().y + height / 2);
        normal = glm::vec3(0,0,1); //z-axis
    }
}

void AreaLight::draw(){
    ofSetColor(getDiffuseColor());
    lightArea.setPosition(getPosition());
    lightArea.setWidth(width);
    lightArea.setHeight(height);
    lightArea.setResolution(numColumns, numRows); //set #columns and #rows
    lightArea.drawWireframe();
    
    //    glm::mat4 m = getTransformationMatrix();
    //    ofPushMatrix();
    //    ofMultMatrix(m);
    //    lightArea.drawWireframe();
    //    ofPopMatrix();
    
    //    ofSetColor (ofColor::yellow);
    //    ofDrawLine (startingCell(), getPosition());
}

void AreaLight::draw(ofColor color){
    ofSetColor(color);
    lightArea.setPosition(getPosition());
    lightArea.setWidth(width);
    lightArea.setHeight(height);
    lightArea.setResolution(numColumns, numRows); //set #columns and #rows
    lightArea.drawWireframe();
    
    //    glm::mat4 m = getTransformationMatrix();
    //    ofPushMatrix();
    //    ofMultMatrix(m);
    //    lightArea.drawWireframe();
    //    ofPopMatrix();
}

bool AreaLight::withinLight(glm::vec3 point){
    if (isHorizontal){
        if (point.x < widthRange[1] && point.x > widthRange[0] && point.z < heightRange[1] && point.z > heightRange[0]){
               return true;
           }
    }
    else{
        if (point.x < widthRange[1] && point.x > widthRange[0] && point.y < heightRange[1] && point.y > heightRange[0]){
            return true;
        }
    }
    return false;
    
       
       //vector from spotlight to intersection point
//    glm::vec3 lightToPt(point - getPosition());
//     Ray ray (point, normalize (lightToPt));
//    bool intersectPl = intersect (ray, point, normal);
//    if (intersectPl == false){
//        cout << "false" << endl;
//    }
//    return intersectPl;
}

glm::vec3 AreaLight::startingCell(){
    if (isHorizontal){
         return glm::vec3 (widthRange[0] + (width/numRows) / 2, getPosition().y, heightRange[0] + (height/numColumns) / 2);
    }
    else{
        return glm::vec3 (widthRange[0] + (width/numRows) / 2, heightRange[0] + (height/numColumns) / 2, getPosition().z);
    }
}

bool AreaLight::intersect (Ray &ray, glm::vec3 &point, glm::vec3 &normal){
    float distance; //distance of intersection between ray and point
    bool insidePlane = false; //ray inside plane
    bool hit = glm::intersectRayPlane (ray.getPoint(), ray.getDirection(), getPosition(), this -> normal, distance);
    if (hit){
        point = ray.evalPoint (distance); //caclulate point of intersection
        normal = this -> normal;
        if (point.x < widthRange[1] && point.x > widthRange[0] && point.z < heightRange[1] && point.z > heightRange[0])
        {
            insidePlane = true;
        }
    }
    return insidePlane;
}

glm::vec3 AreaLight::getCellPt(int row, int column){
    //for (int i = 0; i < numRows; i++){
    // for (int j = 0; j < numColumns; j++){
    //glm::vec3 cell (topLeft().x + i * ((width/numRows) / 2), topLeft().y, topLeft().z + j * ((height/numColumns) / 2));
    return glm::vec3 (startingCell().x + row * (width/numRows), startingCell().y, startingCell().z + column * (height/numColumns));
    //cout << cell << endl;
    // ofDrawLine (cell, glm::vec3(getPosition().x, -5, getPosition().z));
    // }
    // }
}

int AreaLight::getNumRows(){
    return numRows;
}

int AreaLight::getNumCols(){
    return numColumns;
}

float AreaLight::getUnitIntensity(){
    return getIntensity() / (numRows * numColumns);
}

void AreaLight::setPosition (glm::vec3 pos){
    Light::setPosition(pos);
    if (isHorizontal){
        widthRange = glm::vec2(getPosition().x - width / 2, getPosition().x + width / 2);
        heightRange = glm::vec2(getPosition().z - height / 2, getPosition().z + height / 2);
    }
    else{
        widthRange = glm::vec2(getPosition().x - width / 2, getPosition().x + width / 2);
        heightRange = glm::vec2(getPosition().y - height / 2, getPosition().y + height / 2);
    }
}
