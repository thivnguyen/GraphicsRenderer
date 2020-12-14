//
//  AreaLight.h
//  GraphicsRenderer
//
//  Created by Thi Nguyen  on 11/25/20.
//

#ifndef AreaLight_h
#define AreaLight_h

#include "Light.h"
#include "Ray.h"

class AreaLight: public Light {
public:
    AreaLight(glm::vec3 pos, float lightInt);
    AreaLight (glm::vec3 pos, float lightInt, bool horizontal);
    AreaLight (glm::vec3 pos, float lightInt, glm::vec3 angle);
    
    int getNumRows();
    int getNumCols();
    
    float getWidth();
    float getHeight();
    void setWidth(float newWidth);
    void setHeight(float newHeight);
    
    void setRotation (glm::vec3 rotate);
    
    float getUnitIntensity();
    
    glm::vec3 startingCell();
    glm::vec3 getCellPt(int row, int column);
    
    void draw();
    void draw(ofColor color);
    
    bool withinLight(glm::vec3 point);
    glm::vec3 topLeft();
    glm::vec3 topRight();
    glm::vec3 bottomLeft();
    glm::vec3 bottomRight();
    
    bool intersect (Ray &ray, glm::vec3 &point, glm::vec3 &normal);
    
private:
    float width;
    float height;
    
    glm::vec2 widthRange;
    glm::vec2 heightRange;
    
    int numRows;
    int numColumns;
    
    ofPlanePrimitive lightArea;
    
    glm::vec3 normal; //normal on one side of plane
    glm::vec3 normal2; //normal on other side of plane
    
    vector <Ray> rays; //for debuggin purposes
};
#endif /* AreaLight_h */
