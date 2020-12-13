//
//  AreaLight.cpp
//  GraphicsRenderer
//
//  Created by Thi Nguyen  on 11/25/20.
//

#include <stdio.h>
#include "AreaLight.h"
#include <glm/gtx/string_cast.hpp>

using namespace glm;

AreaLight::AreaLight (glm::vec3 pos, float lightInt):Light (pos, lightInt, "AreaLight"){
    
    width = 3;
    height = 3;
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

AreaLight::AreaLight (glm::vec3 pos, float lightInt, glm::vec3 angle):Light (pos, lightInt, "AreaLight"){
    
    width = 2.5;
    height = 2.5;
    numRows = 25;
    numColumns = 25;
    
    setRotation(angle);
    normal = vec3 (getRotationMatrix() * vec4 (0,0,1,1));
    normal2 = vec3 (getRotationMatrix() * vec4 (0,0,-1,1));
    //normal = vec3 (0,0,1);
    //normal = vec3 (0,-1,0);
    //normal2 = vec3 (0,1,0);
    cout << "NORMAL: " << normal << endl;
    cout << "NORMAL2: " << normal2 << endl;
    widthRange = glm::vec2(- width / 2,  width / 2);
    heightRange = glm::vec2(- height / 2,  height / 2);
    //widthRange = vec2 (-width/2, width/2);
    //heightRange = vec2 (-height/2, height/2);
    
    //widthRange[0] = getTransformationMatrix * vec4 (widthRange[0],1);
    
    cout << "Position: "<< getPosition() << endl;
    
    
    cout << "startCell: "<< startingCell() << endl;
    
    vec3 start (getTransformationMatrix() * vec4 (startingCell(),1));
    cout << "startCell Transformed: " << start << endl;
    
    cout << "position = glm::vec3(" << getPosition().x << "," << getPosition().y << "," << getPosition().z << ");" << endl;
    cout << "rotation = glm::vec3(" << getRotation().x << "," << getRotation().y << "," << getRotation().z << ");" << endl;
    
    cout << "bottom left" << bottomLeft() << endl;
    cout << "bottom right" << bottomRight() << endl;
    std::cout << glm::to_string(getTransformationMatrix()) << std::endl;
    cout << "Starting Cell" << startingCell();
}

void AreaLight::draw(){
    ofSetColor(getDiffuseColor());
    //lightArea.setPosition(getPosition());
    lightArea.setWidth(width);
    lightArea.setHeight(height);
    lightArea.setResolution(numColumns, numRows); //set #columns and #rows
    // lightArea.drawWireframe();
    
    glm::mat4 m = getTransformationMatrix();
    ofPushMatrix();
    ofMultMatrix(m);
    lightArea.drawWireframe();
    ofPopMatrix();
    
    ofSetColor (ofColor::yellow);
    //    Ray r (getPosition(), normalize (normal));
    
    ofDrawLine (bottomRight(), bottomLeft());

    ofSetColor (ofColor::red);
    ofDrawLine (bottomLeft(), topLeft());

    ofSetColor (ofColor::green);
    ofDrawLine (bottomRight(), topRight());

    ofSetColor (ofColor::blue);
    ofDrawLine (topLeft(), topRight());

    ofSetColor (ofColor::white);
    
    for (Ray r: rays){
        r.draw(20);
    }
    ofSetColor (ofColor::yellow);
    ofDrawLine (getPosition(), vec3 (getTransformationMatrix() * vec4 (startingCell(),1)));
    
//    Ray r (getPosition(), normalize (normal));
//    r.draw(20);
    ofDrawSphere (getPosition(), 0.5);
    ofDrawLine (getPosition(), normal);
    
        ofSetColor (ofColor::yellow);
        for (int row = 0; row <  numRows; row++){
            for (int col = 0; col <  numColumns; col++){
                ofDrawLine(getPosition(), getCellPt(row, col));
            }
        }
}

void AreaLight::draw(ofColor color){
    ofSetColor(color);
    // lightArea.setPosition(getPosition());
    lightArea.setWidth(width);
    lightArea.setHeight(height);
    lightArea.setResolution(numColumns, numRows); //set #columns and #rows
    //lightArea.drawWireframe();
    
    glm::mat4 m = getTransformationMatrix();
    ofPushMatrix();
    ofMultMatrix(m);
    lightArea.drawWireframe();
    ofPopMatrix();
    
    ofDrawSphere (getPosition(), 0.5);
}

bool AreaLight::withinLight(glm::vec3 point){
    
    //    if (isHorizontal){
    //        if (point.x < widthRange[1] && point.x > widthRange[0] && point.z < heightRange[1] && point.z > heightRange[0]){
    //               return true;
    //           }
    //    }
    //    else{
    //        if (point.x < widthRange[1] && point.x > widthRange[0] && point.y < heightRange[1] && point.y > heightRange[0]){
    //            return true;
    //        }
    //    }
    //    return false;
    
    //vector from areaLight to intersection point
    //glm::vec3 lightToPt(point - getPosition());
    Ray ray (point, normalize (vec3 (0,1,0)));
    // rays.push_back (ray);
    vec3 intersectNormal;
    vec3 intersectPt;
    
    bool intersectPl = intersect (ray, intersectPt, intersectNormal);
//    if (intersectPl){
//        // cout << point << endl;
//        rays.push_back (ray);
//    }
    
    //    bool intersectPl = false;
    //    glm::vec3 vecToPt (point - getPosition());
    //    float angleToX = glm::angle (vec3 (1,0,0), vecToPt); //angle between x axis and vector to point
    //    float vecToPtLength = glm::distance (point, getPosition()); //distance from positin to intersectPt
    //    float posToEdge = (width/2) / cos (angleToX); //length from center to edge
    //
    //    if (vecToPtLength <= posToEdge)
    //    {
    //        intersectPl = true;
    //    }
    return intersectPl;
}

glm::vec3 AreaLight::startingCell(){
    
    //    if (isHorizontal){
    //         return glm::vec3 (widthRange[0] + (width/numRows) / 2, getPosition().y, heightRange[0] + (height/numColumns) / 2);
    //    }
    //    else{
    //        return glm::vec3 (widthRange[0] + (width/numRows) / 2, heightRange[0] + (height/numColumns) / 2, getPosition().z);
    //    }
    //vec3 startingCellOrig = glm::vec3 (widthRange[0] + (width/numRows) / 2, getPosition().y, heightRange[0] + (height/numColumns) / 2);
    //vec4 startingCellTransformed = vec4 (startingCellOrig , 1) * getTranslationMatrix();
    return glm::vec3 (widthRange[0] + (width/numRows) / 2, heightRange[1] - (height/numColumns) / 2, 0 );
    
}

bool AreaLight::intersect (Ray &ray, glm::vec3 &point, glm::vec3 &normal){
    float distance; //distance of intersection between ray and point
    bool insidePlane = false; //ray inside plane
    bool hit = glm::intersectRayPlane (ray.getPoint(), ray.getDirection(), getPosition(), this -> normal, distance);
    //cout << "Light Pos: " << getPosition() << endl;
    if (!hit){
        hit = glm::intersectRayPlane (ray.getPoint(), ray.getDirection(), getPosition(), this -> normal2, distance);
    }
    
    if (hit){
        point = ray.evalPoint (distance); //calculate point of intersection
        normal = this -> normal;
//                if (point.x < widthRange[1] && point.x > widthRange[0] && point.y < heightRange[1] && point.y > heightRange[0])
//                {
//                    insidePlane = true;
//                }
        glm::vec3 vecToPt (point - bottomLeft());
        vecToPt = normalize (vecToPt);
        float angle = glm::angle (normalize(bottomRight() - bottomLeft()), vecToPt);
        float angleDeg = glm::degrees (angle);
        
        float angle2 = glm::angle (normalize(topLeft() - bottomLeft()), vecToPt);
        float angleDeg2 = glm::degrees (angle2);
        //angle between x axis and vector to point
        
        //        if (angle > 45 && angle <= 135){
        //            //angle to pos Y
        //            angle = glm::angle (normalize (midTop()), vecToPt);
        //            if (degrees (angle) > 90){
        //                angle = glm::angle (normalize (midBottom()), vecToPt);
        //            }
        //
        //        }
        //        else if (angle > 135 && angle <= 225){
        //            //angle to neg X
        //            angle = glm::angle (midLeft(), vecToPt);
        //        }
        //        else if (angle > 225 && angle <= 335){
        //            //angle to neg y
        //             angle = glm::angle (midBottom(), vecToPt);
        //        }
        //        else{
        //            //angle to pos x
        //            angle = glm::angle (midRight(), vecToPt);
        //        }
        
//        while (angle > 90){
//            angle = 180 - angle;
//        }
       // angle = radians (angle);
        //if (angle <= 45){
            //angle = glm::angle (normalize(midRight() - getPosition()), vecToPt);
        if (angleDeg2 <=90 && angleDeg <= 90){
        float leftToEdge;
        if (angleDeg > 45 ){
             leftToEdge = glm::max(0.0f, height / sin (angle)); //le
        }
        else{
            leftToEdge = glm::max(0.0f, width / cos (angle));
        }
            float vecToPtLength = glm::distance (point, bottomLeft()); //distance from positin to intersectPt
//
//           //ngth from center to edge
//            // cout << "width/2 " << width / 2 << " degrees " << cos (angle) << endl;
            if (vecToPtLength <= leftToEdge)
            {
                insidePlane = true;
            }
        //}
        
    }
    }
    return insidePlane;
}

glm::vec3 AreaLight::getCellPt(int row, int column){
    //for (int i = 0; i < numRows; i++){
    // for (int j = 0; j < numColumns; j++){
    //glm::vec3 cell (topLeft().x + i * ((width/numRows) / 2), topLeft().y, topLeft().z + j * ((height/numColumns) / 2));
    //    return glm::vec3 (startingCell().x + row * (width/numRows), startingCell().y, startingCell().z + column * (height/numColumns));
    
    //cout << cell << endl;
    // ofDrawLine (cell, glm::vec3(getPosition().x, -5, getPosition().z));
    // }
    // }
    vec3 cellOrig (startingCell().x + row * (width/numRows), startingCell().y - column * (height/numColumns), startingCell().z);
//    vec3 r (getPosition() - (vec4 (cellOrig,1) * getTransformationMatrix()));
//    Ray cell (vec3 (0,0,0), normalize (r));
    //rays.push_back(cell);
    
    return getTransformationMatrix() * vec4 (cellOrig,1);
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
//    if (isHorizontal){
//        widthRange = glm::vec2(getPosition().x - width / 2, getPosition().x + width / 2);
//        heightRange = glm::vec2(getPosition().z - height / 2, getPosition().z + height / 2);
//    }
//    else{
//        widthRange = glm::vec2(getPosition().x - width / 2, getPosition().x + width / 2);
//        heightRange = glm::vec2(getPosition().y - height / 2, getPosition().y + height / 2);
//    }
}


glm::vec3 AreaLight::bottomLeft(){
    vec3 bottomLeft (widthRange[0], heightRange[0],0);
   // cout << vec4 (bottomLeft,1) << endl;
    return vec3 (getTransformationMatrix() * vec4 (bottomLeft, 1));
}

glm::vec3 AreaLight::bottomRight(){
    vec3 bottomRight (widthRange[1], heightRange[0],0);
    return vec3 (getTransformationMatrix() * vec4 (bottomRight, 1));
}

glm::vec3 AreaLight::topLeft(){
    vec3 topLeft (widthRange[0], heightRange[1],0);
    return vec3 (getTransformationMatrix() * vec4 (topLeft, 1));
}

glm::vec3 AreaLight::topRight(){
    vec3 topRight (widthRange[1], heightRange[1],0);
       return vec3 (getTransformationMatrix() * vec4 (topRight, 1));
}
