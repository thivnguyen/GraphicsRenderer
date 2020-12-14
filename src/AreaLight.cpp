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
    height = 2.5;
    numRows = 5;
    numColumns = 5;
    
    //set default as horizontal
    setRotation(vec3 (90,0,0));
    
    normal = vec3 (getRotationMatrix() * vec4 (0,0,1,1));
    normal2 = vec3 (getRotationMatrix() * vec4 (0,0,-1,1));
    widthRange = glm::vec2(- width / 2,  width / 2);
    heightRange = glm::vec2(- height / 2,  height / 2);
    
}

AreaLight::AreaLight (glm::vec3 pos, float lightInt, bool horizontal):Light (pos, lightInt, "AreaLight"){
    
    width = 3;
    height = 2.5;
    numRows = 5;
    numColumns = 5;
    
    //if plane is supposed tobe horizontal, rotate plane
    if (horizontal){
        setRotation(vec3 (90,0,0));
    }
    
    normal = vec3 (getRotationMatrix() * vec4 (0,0,1,1));
    normal2 = vec3 (getRotationMatrix() * vec4 (0,0,-1,1));
    widthRange = glm::vec2(- width / 2,  width / 2);
    heightRange = glm::vec2(- height / 2,  height / 2);
}

AreaLight::AreaLight (glm::vec3 pos, float lightInt, glm::vec3 angle):Light (pos, lightInt, "AreaLight"){
    
    width = 3;
    height = 2.5;
    numRows = 5;
    numColumns = 5;
    
    setRotation(angle);
    
    normal = vec3 (getRotationMatrix() * vec4 (0,0,1,1));
    normal2 = vec3 (getRotationMatrix() * vec4 (0,0,-1,1));
    
    widthRange = glm::vec2(- width / 2,  width / 2);
    heightRange = glm::vec2(- height / 2,  height / 2);
}

//get number of rows of "cells" in area light
int AreaLight::getNumRows(){
    return numRows;
}

//get number of columns of "cells" in area light
int AreaLight::getNumCols(){
    return numColumns;
}

//get width of area light
float AreaLight::getWidth (){
    return width;
}

//get height of area light
float AreaLight::getHeight(){
    return height;
}

//set width of area light
void AreaLight::setWidth(float newWidth){
    width = newWidth;
    widthRange = glm::vec2(- width / 2,  width / 2);
}

//set height of area light
void AreaLight::setHeight(float newHeight){
    height = newHeight;
    heightRange = glm::vec2(- height / 2,  height / 2);
}

//set rotation angle for area light
void AreaLight::setRotation (glm::vec3 rotate){
    Light::setRotation(rotate);
    
    //update normals after rotating area lights
    normal = vec3 (getRotationMatrix() * vec4 (0,0,1,1));
    normal2 = vec3 (getRotationMatrix() * vec4 (0,0,-1,1));
}

//get light intensity of one "cell"
float AreaLight::getUnitIntensity(){
    return getIntensity() / (numRows * numColumns);
}

//starting cell (top-left)
//note that this cell is not transformed yet
glm::vec3 AreaLight::startingCell(){
    return glm::vec3 (widthRange[0] + (width/numRows) / 2, heightRange[1] - (height/numColumns) / 2, 0 );
}

//get cell pt in area light "grid" given row and column number
glm::vec3 AreaLight::getCellPt(int row, int column){
    
    //cell position in vertical area light positioned at origin
    vec3 cellOrig (startingCell().x + row * (width/numRows), startingCell().y - column * (height/numColumns), startingCell().z);
    
    //return cellOrig that is tranformed to postion of area light
    return getTransformationMatrix() * vec4 (cellOrig,1);
}

void AreaLight::draw(){
    ofSetColor(getDiffuseColor());
    
    lightArea.setWidth(width);
    lightArea.setHeight(height);
    lightArea.setResolution(numColumns, numRows); //set #columns and #rows
    
    //apply transformation
    glm::mat4 m = getTransformationMatrix();
    ofPushMatrix();
    ofMultMatrix(m);
    lightArea.drawWireframe();
    ofPopMatrix();
    
    //Drawing the outer edges (for debugging purposes)
    
    //bottom edge
    //    ofSetColor (ofColor::yellow);
    //    ofDrawLine (bottomRight(), bottomLeft());
    
    //left edge
    //    ofSetColor (ofColor::red);
    //    ofDrawLine (bottomLeft(), topLeft());
    
    //right edge
    //    ofSetColor (ofColor::green);
    //    ofDrawLine (bottomRight(), topRight());
    
    //top edge
    //    ofSetColor (ofColor::blue);
    //    ofDrawLine (topLeft(), topRight());
    
    //draw rays under area lights (debuggin purposes)
    for (Ray r: rays){
        r.draw(20);
    }
    
    //drawing line from center to starting cell (debugging purposes)
    //    ofSetColor (ofColor::yellow);
    //    ofDrawLine (getPosition(), vec3 (getTransformationMatrix() * vec4 (startingCell(),1)));
    
    //draw normal
    //ofDrawLine (getPosition(), normal);
    
    //draw line from center to each cell (debugging purposes)
    //    ofSetColor (ofColor::yellow);
    //    for (int row = 0; row <  numRows; row++){
    //        for (int col = 0; col <  numColumns; col++){
    //            ofDrawLine(getPosition(), getCellPt(row, col));
    //        }
    //    }
}

void AreaLight::draw(ofColor color){
    ofSetColor(color);
    lightArea.setWidth(width);
    lightArea.setHeight(height);
    lightArea.setResolution(numColumns, numRows); //set #columns and #rows
    
    //apply transformation
    glm::mat4 m = getTransformationMatrix();
    ofPushMatrix();
    ofMultMatrix(m);
    lightArea.drawWireframe(); //draw plane
    ofPopMatrix();
}

//checks whether point is within the area light
bool AreaLight::withinLight(glm::vec3 point){
    
    //vector from point pointing straight up
    Ray ray (point, normalize (vec3 (0,1,0)));
    
    vec3 intersectNormal;
    vec3 intersectPt;
    
    //check if ray intersects plane
    bool intersectPl = intersect (ray, intersectPt, intersectNormal);
    
    //adds ray to rays if it intersects the plane (debugging purposes)
    //    if (intersectPl){
    //        rays.push_back (ray);
    //    }
    
    return intersectPl;
}

//retrieve coordinates of top left "cell" in area light
glm::vec3 AreaLight::topLeft(){
    vec3 topLeft (widthRange[0], heightRange[1],0);
    return vec3 (getTransformationMatrix() * vec4 (topLeft, 1));
}

//retrieve coordinates of top right "cell" in area light
glm::vec3 AreaLight::topRight(){
    vec3 topRight (widthRange[1], heightRange[1],0);
    return vec3 (getTransformationMatrix() * vec4 (topRight, 1));
}

//retrieve coordinates of bottom left "cell" in area light
glm::vec3 AreaLight::bottomLeft(){
    vec3 bottomLeft (widthRange[0], heightRange[0],0);
    return vec3 (getTransformationMatrix() * vec4 (bottomLeft, 1));
}

//retrieve coordinates of botton right "cell" in area light
glm::vec3 AreaLight::bottomRight(){
    vec3 bottomRight (widthRange[1], heightRange[0],0);
    return vec3 (getTransformationMatrix() * vec4 (bottomRight, 1));
}

//check if ray intersects the area light
bool AreaLight::intersect (Ray &ray, glm::vec3 &point, glm::vec3 &normal){
    float distance; //distance of intersection between ray and point
    bool insidePlane = false; //ray inside plane
    
    //checks if ray intersects the area light
    bool hit = glm::intersectRayPlane (ray.getPoint(), ray.getDirection(), getPosition(), this -> normal, distance);
    
    //check with other side of plane
    if (!hit){
        hit = glm::intersectRayPlane (ray.getPoint(), ray.getDirection(), getPosition(), this -> normal2, distance);
        if (hit){
            normal = this -> normal2;
        }
    }
    else{
        normal = this -> normal;
    }
    
    //if ray intersects plane from at least one side
    if (hit){
        point = ray.evalPoint (distance); //calculate point of intersection
        
        //vector from bottom left point to intersectPt
        glm::vec3 botLeftToPt (point - bottomLeft());
        botLeftToPt = normalize (botLeftToPt);
        
        //angle botLeftToPt makes with bottom edge
        float angleBotEdge = glm::angle (normalize(bottomRight() - bottomLeft()), botLeftToPt);
        float angleBotEdgeDeg = glm::degrees (angleBotEdge);
        
        //angle botLeftToPt makes with left edge
        float angleLeftEdge = glm::angle (normalize(topLeft() - bottomLeft()), botLeftToPt);
        float angleLeftEdgeDeg = glm::degrees (angleLeftEdge);
        
        //vecetor from top right point to intersectPt
        glm::vec3 topRightToPt (point - topRight());
        topRightToPt = normalize (topRightToPt);
        
        //angle topRightToPt makes with right edge
        float angleRightEdge = glm::angle (normalize(bottomRight() - topRight()), topRightToPt);
        float angleRightEdgeDeg = degrees (angleRightEdge);
        
        //angle topRightToPt makes with top edge
        float angleTopEdge = glm::angle (normalize(topLeft() - topRight()), topRightToPt);
        float angleTopEdgeDeg = degrees (angleTopEdge);
        
        if (angleBotEdgeDeg <=90 && angleLeftEdgeDeg <= 90 && angleRightEdgeDeg <= 90 && angleTopEdgeDeg <= 90){
            
            //length from left point to edge with given degree
            float leftToEdge;
            
            if (angleBotEdgeDeg > 45 ){
                leftToEdge = glm::max(0.0f, height / sin (angleBotEdge)); //le
            }
            else{
                leftToEdge = glm::max(0.0f, width / cos (angleBotEdge));
            }
            
            //length from bottom left to pt
            float botLeftToPtLength = glm::distance (point, bottomLeft());
            
            //if length to pt is <= length to edge, then point is within the plane
            if (botLeftToPtLength <= leftToEdge)
            {
                insidePlane = true;
            }
        }
    }
    return insidePlane;
}
