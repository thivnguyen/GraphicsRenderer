//
//  ofApp.h
//  RayTracer
//
//  Edited by Thi Nguyen on 10/5/20.
//

#pragma once

#include "ofMain.h"
#include <vector>
#include "RenderCam.h"
#include "Ray.h"
#include "Light.h"
#include "AreaLight.h"
#include "ofxGui.h"

class Spotlight;

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void drawObjects();
    void rayTrace();
    void demoRayTrace();
    void drawLights();
    void drawSpotlights();
    bool addShadows(Ray rayCamPix, glm::vec3 point);
    bool obstructed (const glm::vec3 &point, const glm::vec3 &norm, Light &light);
    bool mouseToDragPlane(int x, int y, glm::vec3 &point);
    
    void sceneSetup1();
    void sceneSetup2();
    void sceneSetup3wS();
    void sceneSetup4wS();
    void sceneSetup5wS();
    void sceneSetup6wS();
    void sceneSetup7wS();
    void sceneSetup8wS();
    void sceneSetup9wS();
    void sceneSetup10wS();
    void sceneSetup11();
    void sceneSetup12();
    void sceneSetup13();
    
    ofColor lambert(const glm::vec3 &point, const glm::vec3 &norm, const ofColor diffuse);
    ofColor phong(const glm::vec3 &point, const glm::vec3 &norm, const ofColor diffuse, const ofColor specular, float power);
    ofColor shader(const glm::vec3 &point, const glm::vec3 &norm, const ofColor diffuse, const ofColor specular, float power);
    
    ofColor textureDiff(glm::vec3 intersectPt, Plane* p);
    ofColor textureSpec(glm::vec3 intersectPt, Plane* plane);
    int calcPixelI(glm::vec3 intersectPt, Plane* plane);
    int calcPixelJ(glm::vec3 intersectPt, Plane* plane);
    
    bool objSelected(SceneObject* objPtr);
    bool atLeastOneSelected();
    int findIndex (SceneObject* objPtr);
    
private:
    std::vector<SceneObject *> scene; //stores objects on scene
    std::vector<Light *> lights;
    std::vector<Spotlight *> spotlights;
    Light ambient;
    
    ofEasyCam mainCam;
    ofCamera sideCam;
    ofCamera previewCam;
    ofCamera *theCam;
    
    RenderCam renderCam; //image will be rendered through here
    ofImage image; //rendered image
    ofImage textureDiffuseH; //texture for horizontal plane
    ofImage textureSpectureH; //spec for vertical plane
    
    ofImage textureDiffuseV; //texture
    ofImage textureSpectureV; //spec
    
//    ofPixels textureDiffuse;
//    ofPixels textureSpecture;
    int imageWidth = 300;
    int imageHeight = 200;
    
    //for debugging
//    int imageWidth = 6;
//    int imageHeight = 4;
    
    int textureHeightH;
    int textureWidthH;
    
    int textureHeightV;
    int textureWidthV;
    
    int numTilesHorizontal;
    int numTilesVertical;
    
    ViewPlane view;
    
    bool loadImage = false;
    
    float u;
    float v;
    
    float power;
    
    bool sphereCreationModeEnabled;
    bool selectMultipleEnabled;
    vector <SceneObject *> selected;
    glm::vec3 lastPtSelected;
    bool dragModeEnabled;
    
    SceneObject* lastSelected;
    
    ofxFloatSlider light1Intensity;
    ofxFloatSlider light2Intensity;
    ofxFloatSlider spotlightIntensity;
    ofxFloatSlider spotlightAngle;
    
    ofxPanel gui;
    
    Light* light1;
    Light* light2;
    Spotlight* spotlight;

    
};
