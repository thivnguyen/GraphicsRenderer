//
//  AreaLight.cpp
//  GraphicsRenderer
//
//  Created by Thi Nguyen  on 11/25/20.
//

#include <stdio.h>
#include "AreaLight.h"

//AreaLight::AreaLight(glm::vec3 pos, float lightInt, float w, float h, int col, int rows, float angle): Light (pos, lightInt){
//    lightArea = ofPlanePrimitive(w, h);
//    lightArea.setPosition(pos);
//    lightArea.setColumns(col);
//    lightArea.setRows(rows);
//    lightArea.setWidth(w);
//    lightArea.setHeight(h);
//    lightArea.rotateDeg (angle, 1, 0, 0);
//}

AreaLight::AreaLight (glm::vec3 pos, float lightInt):Light (pos, lightInt, "AreaLight"){
    width = 5;
    height = 5;
    numRows = 10;
    numColumns = 10;
    lightArea.rotateDeg(90, 1, 0, 0); //plane initally stands vertical, rotate around x-axis 90 degrees
    widthRange = glm::vec2(getPosition().x - width / 2, getPosition().x + width / 2);
    heightRange = glm::vec2(getPosition().z - height / 2, getPosition().z + height / 2);
    normal = glm::vec3 (0, 1, 0);
    cout << widthRange << endl;
    cout << heightRange << endl;
    cout << getPosition() << endl;
    
}

void AreaLight::draw(){
    ofSetColor(getDiffuseColor());
    lightArea.setPosition(getPosition());
    lightArea.setWidth(width);
   lightArea.setHeight(height);
   lightArea.setResolution(numColumns, numRows); //set #columns and #rows
    lightArea.drawWireframe();
    ofSetColor (ofColor::yellow);
    ofDrawLine (startingCell(), getPosition());
    //ofDrawLine (glm::vec3 (widthRange.y, getPosition().y, heightRange.y), getPosition());
    
//    for (int i = 0; i < numRows; i++){
//        for (int j = 0; j < numColumns; j++){
//            //glm::vec3 cell (topLeft().x + i * ((width/numRows) / 2), topLeft().y, topLeft().z + j * ((height/numColumns) / 2));
//            glm::vec3 cell (topLeft().x + i * (width/numRows), topLeft().y, topLeft().z + j * (height/numColumns));
//            //cout << cell << endl;
//            ofDrawLine (cell, glm::vec3(getPosition().x, -5, getPosition().z));
//        }
//    }
}


bool AreaLight::withinLightGrid(glm::vec3 point, int row, int column){
    
       //vector from intersection point to light
       glm::vec3 lightToPt(point - getPosition());
       
//    Plane p (
//
//       //find angle between the 2 vectors
//       float angleBtwn = glm::degrees(angle (normalize(lightDir), normalize(lightToPt)));
//
//       //check whether the angle * 2 is < the cone angle since the lightDir vector bisects the angle
//       return angleBtwn * 2<= coneAngle;
//
//             float distance; //distance of intersection between ray and point
//                bool insidePlane = false; //ray inside plane
//                bool hit = glm::intersectRayPlane (ray.6getPoint(), ray.getDirection(), getPosition(), this -> normal, distance);
//                if (hit){
//                    point = ray.evalPoint (distance); //caclulate point of intersection
//                    normal = this -> normal;
//                    if (point.x < widthRange[1] && point.x > widthRange[0] && point.z < heightRange[1] && point.z > heightRange[0])
//                    {
//                        insidePlane = true;
//                    }
//                }
//                return insidePlane;
}

glm::vec3 AreaLight::startingCell(){
    return glm::vec3 (widthRange.x + (width/numRows) / 2, getPosition().y, heightRange.x + (height/numColumns) / 2);
}
             
float AreaLight::bottomLeft(){
        
}
             
float AreaLight::topRight(){
        
}
             
float AreaLight::bottomRight(){
        
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
    return totalIntensity / (numRows * numColumns);
}
