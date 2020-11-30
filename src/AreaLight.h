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
    //AreaLight(glm::vec3 pos, float lightInt, float w, float h, int col, int rows, float angle);
    AreaLight(glm::vec3 pos, float lightInt);
    void draw();
    void draw(ofColor color);
    float getWidth();
    float getHeight();
    bool withinLight(glm::vec3 point);
    bool withinLightGrid(glm::vec3 point, int row, int column);
    bool intersect (Ray &ray, glm::vec3 &point, glm::vec3 &normal);
    float getTotalIntensity();
    float getUnitIntensity();
    glm::vec3 getCellPt(int row, int column);
    glm::vec2 getWidthRange();
    glm::vec2 getHeightRange();
    glm::vec3 startingCell();
    float bottomLeft();
    float topRight();
    float bottomRight();
    int getNumRows();
    int getNumCols();
    
private:
    vector <Ray> rays;
    float totalIntensity;
    float width;
    float height;
    int numRows;
    int numColumns;
    glm::vec2 widthRange;
    glm::vec2 heightRange;
    float unitWidth;
    float unitHeight;
    ofPlanePrimitive lightArea;
    glm::vec3 normal;
    
};
#endif /* AreaLight_h */
