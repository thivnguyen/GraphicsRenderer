//
//  AreaLightTest.h
//  GraphicsRenderer
//
//  Created by Thi Nguyen  on 12/11/20.
//

#ifndef AreaLightTest_h
#define AreaLightTest_h

#include "Light.h"
#include "Ray.h"

class AreaLightTest: public Light {
public:
    //AreaLight(glm::vec3 pos, float lightInt, float w, float h, int col, int rows, float angle);
    AreaLightTest(glm::vec3 pos, float lightInt);
    AreaLightTest (glm::vec3 pos, float lightInt, bool horizontal);
    AreaLightTest (glm::vec3 pos, float lightInt, float angle);
    void draw();
    void draw(ofColor color);
    float getWidth();
    float getHeight();
    bool withinLight(glm::vec3 point);
    bool intersect (Ray &ray, glm::vec3 &point, glm::vec3 &normal);
    float getUnitIntensity();
    glm::vec3 getCellPt(int row, int column);
    glm::vec2 getWidthRange();
    glm::vec2 getHeightRange();
    glm::vec3 startingCell();
    int getNumRows();
    int getNumCols();
    void setPosition (glm::vec3 pos);
    
private:
    vector <Ray> rays;
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
    bool isHorizontal;
};

#endif /* AreaLightTest_h */
