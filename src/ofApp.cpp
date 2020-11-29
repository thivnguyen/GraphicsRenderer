//
//  ofApp.h
//  RayTracer
//
//  Created by Thi Nguyen  on 9/28/20.
//

#include "ofApp.h"
#include "Sphere.h"
#include "Ray.h"
#include "Spotlight.h"
using namespace glm;


//--------------------------------------------------------------
void ofApp::setup(){
    
    
    theCam = &mainCam; //easyCam
    mainCam.setDistance (30.0);
    mainCam.lookAt (vec3 (0,0,-1));
    
    selectMultipleEnabled = false;
    dragModeEnabled = false;
    sphereCreationModeEnabled = false;
    
   scene.push_back (new Plane (vec3(0,-2,2), ofColor::white, 30, 70, true));
//
//    light1 = new Light (vec3(4,7,5), 50);
//    light2 = new Light (vec3(-7,4,0), 50);
//    spotlight = new Spotlight (vec3 (-1.5,10, 3), 20, 10, vec3 (1, -1.25, -3));
//    lights.push_back (light1);
 //   lights.push_back (light2);
//    lights.push_back (spotlight);
//
//    //push objects into scene
//    scene.push_back (new Sphere (vec3 (1.25, -0.25, -5), 1.5, ofColor::purple));
//
 //   lights.push_back (new Light (vec3(4,7,5), 23));
 //   lights.push_back (new Light (vec3(-7,4,0), 23));
    lights.push_back (new AreaLight (vec3(0, 8, -5), 75));
    ambient = Light (renderCam.getPosition(), 15, ofColor::black);
//
//    //set power value for Phong shading
    power = 70;
//
//    gui.setup();
//
//    gui.add (light1Intensity.setup("Light 1 Intensity", light1 -> getIntensity(), 0, 100));
//    gui.add (light2Intensity.setup("Light 2 Intensity", light2 -> getIntensity(), 0, 100));
//    gui.add (spotlightIntensity.setup("Spotlight Intensity", spotlight -> getIntensity(), 0, 100));
//    gui.add (spotlightAngle.setup("Spotlight Angle", 50, 0, 100));

    
    
    //horizontal plane
    //scene with 3 spheres and 2 lights
    //sceneSetup1();
    
    //scene with 3 spheres and 3 lights
    //sceneSetup2();
    
    //spotlight with one red sphere
    //sceneSetup3wS();
    
    //spotlight pointing at pink sphere, 3 spheres in scene
    //sceneSetup4wS();
    
    //spotlight pointing at blue and green sphere, no surrounding lights
    //sceneSetup5wS();
    
    //spotlight pointing at blue and green sphere
    //sceneSetup6wS();
    
    //spotlight on all three spheres
   // sceneSetup7wS();
    
    //2 spotlights in scene
    //sceneSetup8wS();
    
    //tabletop with spotlight only
    //sceneSetup9wS();
    
    //tabletop with 2 spotlights only
    //sceneSetup10wS();
    //load texture images
    textureDiffuseH.load ("woodDiff.jpg"); //load texture image
    textureSpectureH.load("woodSpec.jpg"); //load texture image

    textureWidthH = textureDiffuseH.getWidth();
    textureHeightH = textureDiffuseH.getHeight();


       //set num of "texture tiles" in both directions
       numTilesHorizontal = 12;
       numTilesVertical = 12;
    
    //wood background and floor with 4 spheres
    //sceneSetup11();
    
    //cobblestone ground with 4 spheres + 1 spotlight
    //sceneSetup12();
    
    //brick wall and floor with 6 rainbow colored spheres
    //sceneSetup13();
    
    
    //preview cam setup
    previewCam.setPosition (renderCam.getPosition()); //place where renderCam is
    previewCam.lookAt(renderCam.getAim());
    
    //side cam setup
    sideCam.setPosition (vec3 (20,0,0)); //place on the side looking at entire scene
    sideCam.lookAt(renderCam.getAim());
    
    //alocate pixels for image
    image.allocate(imageWidth, imageHeight, OF_IMAGE_COLOR);
    
}

//--------------------------------------------------------------
void ofApp::update(){
//    light1 -> setIntensity (light1Intensity);
//    light2 -> setIntensity (light2Intensity);
//    spotlight -> setIntensity(spotlightIntensity);
//    spotlight -> setAngle (spotlightAngle);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    theCam -> begin();
    
    renderCam.draw(); //draw renderCam
    drawObjects(); //draw objects in scene
    renderCam.drawFrustum(); //draw frustum from renderCam to viewPlane
    view.draw(); //draw viewPlane
    drawLights();
    drawSpotlights();
    //renderCam.drawGrid(); //draw 6 x 4 grid on plane (for debugging purposes)
    renderCam.drawRays(); //draw rays from renderCam (for debugging purposes)
    theCam -> end();
    
    //draw rendered image on screen
    if (loadImage){
        ofSetColor (ofColor::white);
        image.draw(0,0);
    }
    
   // gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    int toErase;
        if (key == 'd' && atLeastOneSelected()){
            for (SceneObject* sObj: selected){
                toErase = findIndex (selected[0]);
                scene.erase(scene.begin() + toErase);
            }
        }
    
    switch (key){
        case '1':
            for (SceneObject* sObj: selected){
                sObj -> setDiffuseColor(ofColor::red);
            }
            break;
        case '2':
        for (SceneObject* sObj: selected){
            sObj -> setDiffuseColor(ofColor::green);
        }
        break;
            case '3':
            for (SceneObject* sObj: selected){
                sObj -> setDiffuseColor(ofColor::blue);
            }
            break;
        case 'a': //add a sphere
            sphereCreationModeEnabled = true;
            break;
            //toggle on/off camera view
        case 'c':
            mainCam.getMouseInputEnabled() ? mainCam.disableMouseInput(): mainCam.enableMouseInput();
            break;
        case 'm': //switch to main Camera (easyCam) view
            theCam = &mainCam;
            break;
        case 'p': //switch to preview Camera view
            theCam = &previewCam;
            break;
        case 's': //switch to side Camera (sideCam) view
            theCam = &sideCam;
            break;
        case 'r': //render image and save
            rayTrace();
            break;
        case 'l': //load rendered image
            loadImage = true;
            image.load ("renderedImg.png");
            break;
        case 'h': //hide rendered image
            loadImage = false;
            break;
            //shift key
        case OF_KEY_SHIFT:
            if (selectMultipleEnabled){
                for (SceneObject* sObj: selected){
                    sObj -> detachParent();
                }
                selectMultipleEnabled = false;
            }
            else{
                selectMultipleEnabled = true;
            }
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    switch (key){
            //create sphere
        case 'a':
            sphereCreationModeEnabled = false;
            break;
            //        case OF_KEY_SHIFT:
            //            selectMultipleEnabled = false;
            //            break;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    vec3 newPoint;
    mouseToDragPlane(x, y, newPoint);
    lastPtSelected = newPoint;
    if (atLeastOneSelected() && dragModeEnabled){
// if (selectMultipleEnabled){
//        //            // SceneObject* lastSelected = selected[selected.size() - 1];
//                    for (SceneObject* sObj: selected){
//                        if (sObj!= lastSelected){
//                            sObj -> setParent(lastSelected);
//                        }
//                    }
//                    //set selected obj's position to new position
//                    //move
//                    lastSelected -> setPosition(newPoint);
//                    lastSelected -> setLocalPosition(newPoint);
//
//                            for (SceneObject* sObj: selected){
//                                if (sObj!= lastSelected){
//                                    //sObj -> setPosition (sObj -> getPosition());
//                                    //sObj -> setLocalPosition (sObj -> getPosition());
//                                    sObj -> detachParent();
//                                }
//                            }
//                }
//                else {
                    lastSelected -> setPosition(newPoint);
                    lastSelected -> setLocalPosition(newPoint);
       // }
    }
}


//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    //if mouse is clicked to move easy cam around
    if (mainCam.getMouseInputEnabled()){
        return;
    }
    
    if (!selectMultipleEnabled){
        selected.clear();
    }
    
    //test if something is selected
    vector<SceneObject *> objIntersected;
    
    //generate ray from mouse pt. to camera
    vec3 screen3DPt = mainCam.screenToWorld(vec3(x, y, 0));
    vec3 rayOrigin = mainCam.getPosition();
    vec3 rayDir = normalize (screen3DPt - rayOrigin);
    Ray r (rayOrigin, rayDir);
    
    
    float closestDist = INFINITY; //stores shortest distance
    SceneObject* closestObj = NULL; //points to closest obj to renderCam
    vec3 intersectPtClosest;
    vec3 intersectNormClosest;
    
    //loop through each object and check for intersection
    for (SceneObject* sObj: scene){
        vec3 intersectNormal;
        vec3 intersectPt;
        
        bool hit = sObj -> intersect(r, intersectPt, intersectNormal); //indicates if ray hits object
        
        if (hit){ //if hit, check if object is closer than previous object(s)
            float dist = distance2 (renderCam.getPosition(), intersectPt);
            if (dist < closestDist){
                closestObj = sObj;
                closestDist = dist;
                intersectPtClosest = intersectPt;
                intersectNormClosest = intersectNormal;
            }
        }
    }
    
    for (Light* light: lights){
        vec3 intersectNormal;
        vec3 intersectPt;
        
        bool hit = light -> intersect(r, intersectPt, intersectNormal); //indicates if ray hits object
        
        if (hit){ //if hit, check if object is closer than previous object(s)
            float dist = distance2 (renderCam.getPosition(), intersectPt);
            if (dist < closestDist){
                closestObj = light;
                closestDist = dist;
                intersectPtClosest = intersectPt;
                intersectNormClosest = intersectNormal;
            }
        }
    }
    
    //if object hit is sphere, set as chosenObj
    if (closestObj != NULL){
        
        //if object is a sphere
        if ((closestObj -> isSelectable())){
            //if object has not been selected yet
            if (!objSelected(closestObj)){
                selected.push_back(closestObj);
            }
            lastSelected = closestObj;
            dragModeEnabled = true;
            mouseToDragPlane(x, y, lastPtSelected);
            
            cout << closestObj -> getName() << " selected" << endl;
           
            if (selectMultipleEnabled){
                closestObj -> detachParent();
                
                for (SceneObject* sObj: selected){
                    if (sObj != closestObj){
                        cout << "Before detach " << sObj -> getPosition () << endl;
                        sObj -> detachParent();
                        sObj -> setParent(closestObj);
                        cout << "After set parent " << sObj -> getPosition () << endl;

                    }
                }
            }
//            else{
 //               mouseToDragPlane(x, y, lastPtSelected);
//            }
            
        }
        else{
            mouseToDragPlane(x, y, lastPtSelected);
        }
        
    }
        else{
            mouseToDragPlane(x, y, lastPtSelected);
        }
        
        //add sphere if sphereCreationMode is enabled
        if (sphereCreationModeEnabled){
            scene.push_back(new Sphere(lastPtSelected, 1, ofColor::white));
        }
        cout << lastPtSelected << endl;
        //    if (selectMultipleEnabled){
        //        lastSelected -> detachParent();
        //        for (SceneObject* sObj: selected){
        //            if (sObj!= lastSelected){
        //                sObj -> setParent(lastSelected);
        //            }
        //        }
        //    }
   // }
   // cout << lastPtSelected << endl;
    }


//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    dragModeEnabled = false;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
//projects mouse pt on scene space (x,y) to 3D point on plane normal
//to view axis of camera passing thorugh pt of selected object
//If no object selected, pass through world orgin is used
bool ofApp::mouseToDragPlane(int x, int y, vec3 &point){
    
    //generate ray from mouse pt. to camera
    vec3 screen3DPt = mainCam.screenToWorld(vec3(x, y, 0));
    vec3 rayOrigin = mainCam.getPosition();
    vec3 rayDir = normalize (screen3DPt - rayOrigin);
    
    float dist;
    vec3 pos;
    if (atLeastOneSelected()){
        pos = lastSelected -> getPosition();
    }
    else{
        pos = vec3(0,0,0);
    }
    
    if (intersectRayPlane(screen3DPt, rayDir, pos, normalize(mainCam.getZAxis()), dist)){
        point = screen3DPt + rayDir * dist;
        return true;
    }
    return false;
}
//--------------------------------------------------------------
//Drawing Objects in scene


//draw all objects in the scene
void ofApp::drawObjects(){
    for (SceneObject* sObj: scene){
        //if object was chosen
        if (objSelected(sObj)){
            sObj -> draw(ofColor::yellow);
        }
        else{
            sObj -> draw();
        }
    }
}

//Draw all lights in scnee
void ofApp::drawLights(){
    for (Light* light: lights){
        //if object was chosen
               if (objSelected(light)){
                   light -> draw(ofColor::yellow);
               }
               else{
                   light -> draw();
               }
        
    }
}

//Draw all spotlights in scnee
void ofApp::drawSpotlights(){
    for (Spotlight* spotlight: spotlights){
        spotlight -> draw();
    }
}
//--------------------------------------------------------------
//Rendering


//render the image and save it
void ofApp::rayTrace(){
    cout << "Rendering ..." << endl;
    
    //loop through pixels
    for (int j = 0; j < imageHeight; j++){
        for (int i = 0; i < imageWidth; i++){
            
            //convert i, j to u, v
            float u = (i + 0.5) / imageWidth;
            float v = (j + 0.5) / imageHeight;
            
            //get ray that goes through u, v
            Ray r = renderCam.getRay (u, v);
            //renderCam.addRay(r); //add ray to be drawn later (for debugging purposes)
            
            float closestDist = INFINITY; //stores shortest distance
            SceneObject* closestObj = NULL; //points to closest obj to renderCam
            vec3 intersectPtClosest;
            vec3 intersectNormClosest;
            
            //loop through each object and check for intersection if ray is within cone
            for (SceneObject* sObj: scene){
                vec3 intersectNormal;
                vec3 intersectPt;
                
                bool hit = sObj -> intersect(r, intersectPt, intersectNormal); //indicates if ray hits object
                
                if (hit){ //if hit, check if object is closer than previous object(s)
                    float dist = distance2 (renderCam.getPosition(), intersectPt);
                    if (dist < closestDist){
                        closestObj = sObj;
                        closestDist = dist;
                        intersectPtClosest = intersectPt;
                        intersectNormClosest = intersectNormal;
                    }
                }
            }
            
            //if at least one object was hit, paint that pixel color of closest object
            if (closestObj != NULL){
                
                //if object is a plane
                if (closestObj -> getName() == "Plane"){
                    
                    //grab textures from texture maps
                    ofColor dif = textureDiff(intersectPtClosest, ((Plane*) closestObj));
                    ofColor spec = textureSpec(intersectPtClosest, ((Plane*) closestObj));
                    image.setColor(i, imageHeight - 1 - j, shader (intersectPtClosest, intersectNormClosest, dif, spec, power));
                }
                
                //if object is not a plane
                else{
                    //get object's default color
                    image.setColor(i, imageHeight - 1 - j, shader (intersectPtClosest, intersectNormClosest, closestObj -> getDiffuseColor(), closestObj -> getSpecularColor(), power));
                }
                
            }
            //if miss, paint pixel background color
            else{
                image.setColor(i, imageHeight - 1 - j, ofColor::black);
            }
        }
    }
    
    //save image
    image.save("renderedImg.png", OF_IMAGE_QUALITY_BEST);
    
    cout << "Done rendering" << endl;
}
//--------------------------------------------------------------
//Shading

//shade image
ofColor ofApp::shader(const glm::vec3 &point, const glm::vec3 &norm, const ofColor diffuse, const ofColor specular, float power){
    ofColor ls = lambert (point, norm, diffuse);
    ofColor ld = phong (point, norm, diffuse, specular, power);
    ofColor la = ambient.getDiffuseColor() * 0.25;
    
    return ls + ld + la;
}

//shades image using Lambert shading
ofColor ofApp::lambert(const glm::vec3 &point, const glm::vec3 &norm, const ofColor diffuse){
    ofColor ld = 0;
    for (Light* light: lights){
        if (light -> withinLight(point)){
            
            if (light -> getName() == "AreaLight"){
                AreaLight* areaLight = (AreaLight *) light;
                //loop through grid to determine ld
                for (int row = 0; row <  areaLight -> getNumRows(); row++){
                    for (int col = 0; col <  areaLight -> getNumCols(); col++){
                        vec3 cellPt (areaLight -> getCellPt(row, col));
                        if (!obstructed(point, norm, *light)){
                            
                            //distance from point to light
                            float r2 = distance2 (point, light -> getPosition());
                            
                            //vector from point to light
                            vec3 l (light -> getPosition() - point);
                            
                            ld += diffuse * (areaLight -> getUnitIntensity()/r2) * glm::max(0.0f, glm::dot(normalize(norm), normalize(l)));
                        }
                    }
                }
            }
            else{
                //only add to ld if point is not in the shadows
                if (!obstructed(point, norm, *light)){
                    
                    //distance from point to light
                    float r2 = distance2 (point, light -> getPosition());
                    
                    //vector from point to light
                    vec3 l (light -> getPosition() - point);
                    
                    ld += diffuse * (light -> getIntensity()/r2) * glm::max(0.0f, glm::dot(normalize(norm), normalize(l)));
                }
            }
        }
    }
    
//    for (Spotlight* spotlight: spotlights){
//
//        //only add color if point of intersection is in the spotlight
//        if (spotlight -> withinLight(point)){
//            //only add to ld if point is not in the shadows
//            if (!obstructed(point, norm, *spotlight)){
//
//                //distance from point to light
//                float r2 = distance2 (point, spotlight -> getPosition());
//
//                //vector from point to light
//                vec3 l (spotlight -> getPosition() - point);
//
//                ld += diffuse * (spotlight -> getIntensity()/r2) * glm::max(0.0f, glm::dot(normalize(norm), normalize(l)));
//            }
//        }
//    }

    return ld;
}

//shades image using phong shading
ofColor ofApp::phong(const glm::vec3 &point, const glm::vec3 &norm, const ofColor diffuse, const ofColor specular, float power){
    ofColor ls = 0;
    
    //vector from point of direction to camera
    vec3 v (renderCam.getPosition() - point);
    
    for (Light* light: lights){
        
        if (light -> withinLight(point)){
        //only add to ls if point is not in the shadows
        if (!obstructed(point, norm, *light)){
            //distance from point to light
            float r2 = distance2 (point, light -> getPosition());
            
            //vector from point to light
            vec3 l (light -> getPosition() - point);
            
            //find bisector
            vec3 h = normalize (v + l);
            
            ls += specular * (light -> getIntensity()/r2)  * glm::pow(glm::max(0.0f, glm::dot(normalize(norm), h)), power);
        }
    }
}
    
    //only add color if point of intersection is in the spotlight
//    for (Spotlight* spotlight: spotlights){
//        if (spotlight -> withinLight(point)){
//            //only add to ld if point is not in the shadows
//            if (!obstructed(point, norm, *spotlight)){
//
//                //distance from point to light
//                float r2 = distance2 (point, spotlight -> getPosition());
//
//                //vector from point to light
//                vec3 l (spotlight -> getPosition() - point);
//
//                //find bisector
//                vec3 h = normalize (v + l);
//
//                ls += specular * (spotlight -> getIntensity()/r2)  * glm::pow(glm::max(0.0f, glm::dot(normalize(norm), h)), power);
//            }
//        }
//    }
    return ls;
}

//checks whether a ray from point going to light is obstructed by any objects
bool ofApp::obstructed (const glm::vec3 &point, const glm::vec3 &norm, Light &light){
    
    vec3 newPoint (point + norm * 0.0001);
    Ray shadowRay (newPoint, normalize (light.getPosition() - newPoint)); //ray from point to light
    
    //check if intersect with any object
    for (SceneObject* sObj: scene){
        vec3 intersectNormal;
        vec3 intersectPt;
        bool hit = sObj -> intersect(shadowRay, intersectPt, intersectNormal); //indicates if ray hits object
        
        //if hits an object on the way
        if (hit){
            return true;
        }
    }
    
    return false;
}

//--------------------------------------------------------------
//Texture Mapping

//returns color of pixel on diffuse texture map
ofColor ofApp::textureDiff(vec3 intersectPt, Plane* plane){
    //calculate i and j pixel to graph from texture map
    int i = calcPixelI(intersectPt, plane);
    int j = calcPixelJ(intersectPt, plane);
    
    if (plane -> isHorizontal()){
        return textureDiffuseH.getPixels().getColor(i, j);
    }
    else{
        return textureDiffuseV.getPixels().getColor(i, j);
    }
    
}

//returns color of pixel on specture texture map
ofColor ofApp::textureSpec(vec3 intersectPt, Plane* plane){
    //calculate i and j pixel to graph from texture map
    int i = calcPixelI(intersectPt, plane);
    int j = calcPixelJ(intersectPt, plane);
    
    if (plane -> isHorizontal()){
        return textureSpectureH.getPixels().getColor(i, j);
    }
    else{
        return textureSpectureV.getPixels().getColor(i, j);
    }
}

//calculate i value of pixel on texture map
int ofApp::calcPixelI(vec3 intersectPt, Plane* plane){
    
    //calc u given pt on plane
    float u = ofMap(intersectPt.x, plane -> getWidthRange().x, plane -> getWidthRange().y, 0, numTilesHorizontal);
    
    if (plane -> isHorizontal()){
        int i = u * textureWidthH - 0.5;
        return fmod (i, textureWidthH);
    }
    else{
        int i = u * textureWidthV - 0.5;
        return fmod (i, textureWidthV);
    }
}

//calculate j value of pixel on texture map
int ofApp::calcPixelJ(vec3 intersectPt, Plane* plane){
    
    //calc v given pt on plane
    float v;
    if (plane -> isHorizontal() == true){
        v = ofMap(intersectPt.z, plane -> getHeightRange().x, plane -> getHeightRange().y, 0, numTilesVertical);
        int j = v * textureHeightH - 0.5;
        return fmod (j, textureHeightH);
    }
    else{
        v = ofMap(intersectPt.y, plane -> getHeightRange().x, plane -> getHeightRange().y, 0, numTilesVertical);
        int j = v * textureHeightV - 0.5;
        return fmod (j, textureHeightV);
    }
    
}

//--------------------------------------------------------------
//Scene Setups


//scene with 3 spheres and 2 lights
void ofApp::sceneSetup1(){
    //set background color to black
    ofSetBackgroundColor (ofColor::black);
    
    //push objects into scene
    scene.push_back (new Sphere (vec3 (1.25, -0.25, -5), 1.5, ofColor::purple));
    scene.push_back (new Sphere (vec3 (-1.5,0, -3), 2, ofColor::cyan));
    scene.push_back (new Sphere (vec3 (0,-0.75, 0), 1.25, ofColor::lawnGreen));
    scene.push_back (new Sphere (vec3 (1, -1.25, 2), 0.75, ofColor::hotPink));
    scene.push_back (new Plane (vec3(0,-2,2), ofColor::white, 20, 30, true));
    
    lights.push_back (new Light (vec3(4,7,5), 50));
    lights.push_back (new Light (vec3(-7,4,0), 50));
    ambient = Light (renderCam.getPosition(), 15, ofColor::black);
    
    //set power value for Phong shading
    power = 70;
}

//scene with 3 spheres and 3 lights
void ofApp::sceneSetup2(){
    //set background color to black
    ofSetBackgroundColor (ofColor::black);
    
    //push objects into scene
    scene.push_back (new Sphere (vec3 (1.25, -0.25, -5), 1.5, ofColor::purple));
    scene.push_back (new Sphere (vec3 (-1.5,0, -3), 2, ofColor::cyan));
    scene.push_back (new Sphere (vec3 (0,-0.75, 0), 1.25, ofColor::lawnGreen));
    scene.push_back (new Sphere (vec3 (1, -1.25, 2), 0.75, ofColor::hotPink));
    scene.push_back (new Plane (vec3(0,-2,2), ofColor::white, 20, 30, true));
    
    lights.push_back (new Light (vec3(4,7,5), 35));
    lights.push_back (new Light (vec3(-7,4,0), 15));
    lights.push_back (new Light (vec3(0,3,3), 15));
    ambient = Light (renderCam.getPosition(), 15, ofColor::black);
    
    //set power value for Phong shading
    power = 65;
    
}

//spotlight with one red sphere
void ofApp::sceneSetup3wS(){
    //set background color to black
    ofSetBackgroundColor (ofColor::black);
    
    //push objects into scene
    scene.push_back (new Sphere (vec3 (1, -1.25, 2), 0.75, ofColor::red));
    scene.push_back (new Plane (vec3(0,-2,2), ofColor::white, 20, 30, true));
    
    lights.push_back (new Light (vec3(4,5,-5), 40));
    ambient = Light (renderCam.getPosition(), 25, 5);
    
    //spotlights.push_back(new Spotlight (vec3 (-1.5,10, -3), 75, 35, vec3 (-1.5,0, -3)));
    spotlights.push_back(new Spotlight (vec3 (-1.5,10, 3), 100, 25, vec3 (1, -1.25, 2)));
    
    
    //set power value for Phong shading
    power = 50;
}

//spotlight pointing at pink sphere, 3 spheres in scene
void ofApp::sceneSetup4wS(){
    //set background color to black
    ofSetBackgroundColor (ofColor::black);
    
    //push objects into scene
    scene.push_back (new Sphere (vec3 (-1.5,0, -3), 2, ofColor::cyan));
    scene.push_back (new Sphere (vec3 (0,-0.75, 0), 1.25, ofColor::lawnGreen));
    scene.push_back (new Sphere (vec3 (1, -1.25, 2), 0.75, ofColor::hotPink));
    scene.push_back (new Plane (vec3(0,-2,2), ofColor::white, 20, 30, true));
    
    lights.push_back (new Light (vec3(4,7,5), 40));
    ambient = Light (renderCam.getPosition(), 25, 5);
    
    spotlights.push_back(new Spotlight (vec3 (-1.5,10, 3), 80, 10, vec3 (1, -1.25, 2)));
    
    //set power value for Phong shading
    power = 50;
    
}

//spotlight pointing at blue and green sphere
void ofApp::sceneSetup6wS(){
    //set background color to black
    ofSetBackgroundColor (ofColor::black);
    
    //push objects into scene
    scene.push_back (new Sphere (vec3 (-1.5,0, -3), 2, ofColor::cyan));
    scene.push_back (new Sphere (vec3 (0,-0.75, 0), 1.25, ofColor::lawnGreen));
    scene.push_back (new Plane (vec3(0,-2,2), ofColor::white, 20, 30, true));
    
    lights.push_back (new Light (vec3(4,7,5), 40));
    ambient = Light (renderCam.getPosition(), 25, 5);
    
    //spotlights.push_back(new Spotlight (vec3 (-1.5,10, -3), 75, 35, vec3 (-1.5,0, -3)));
    spotlights.push_back(new Spotlight (vec3 (-1.5,10, 0), 90, 40, vec3 (-1,0, -1)));
    
    //set power value for Phong shading
    power = 50;
}

//spotlight pointing at blue and green sphere, no surrounding lights
void ofApp::sceneSetup5wS(){
    //set background color to black
    ofSetBackgroundColor (ofColor::black);
    
    //push objects into scene
    scene.push_back (new Sphere (vec3 (-1.5,0, -3), 2, ofColor::cyan));
    scene.push_back (new Sphere (vec3 (0,-0.75, 0), 1.25, ofColor::lawnGreen));
    scene.push_back (new Plane (vec3(0,-2,2), ofColor::white, 20, 30, true));
    
    ambient = Light (renderCam.getPosition(), 25, 5);
    
    lights.push_back(new Spotlight (vec3 (-1.5,10, 0), 70, 40, vec3 (-1,0, -1)));
    
    //set power value for Phong shading
    power = 75;
    
}

//spotlight on all three spheres
void ofApp::sceneSetup7wS(){
    
    //set background color to black
    ofSetBackgroundColor (ofColor::black);
    
    //push objects into scene
    scene.push_back (new Sphere (vec3 (-1.5,0, -3), 2, ofColor::cyan));
    scene.push_back (new Sphere (vec3 (0,-0.75, 0), 1.25, ofColor::lawnGreen));
    scene.push_back (new Sphere (vec3 (1, -1.25, 2), 0.75, ofColor::hotPink));
    scene.push_back (new Plane (vec3(0,-2,2), ofColor::white, 20, 30, true));
    
    lights.push_back (new Light (vec3(4,7,5), 40));
    ambient = Light (renderCam.getPosition(), 25, 5);
    
    spotlights.push_back(new Spotlight (vec3 (-1.5,10, 3), 80, 45, vec3 (0,-3, -1)));
    
    //set power value for Phong shading
    power = 50;
}

//2 spotlights in scene
void ofApp::sceneSetup8wS(){
    
    //set background color to black
    ofSetBackgroundColor (ofColor::black);
    
    //push objects into scene
    scene.push_back (new Sphere (vec3 (-1.5,0, -3), 2, ofColor::purple));
    scene.push_back (new Sphere (vec3 (1, -1.25, 2), 0.75, ofColor::hotPink));
    scene.push_back (new Plane (vec3(0,-2,2), ofColor::white, 20, 30, true));
    
    lights.push_back (new Light (vec3(4,7,-5), 30));
    lights.push_back (new Light (vec3(-7,7,0), 30));
    ambient = Light (renderCam.getPosition(), 25, 5);
    
    spotlights.push_back(new Spotlight (vec3 (-5,10, 0), 75, 35, vec3 (-1.5,0, -3)));
    spotlights.push_back(new Spotlight (vec3 (-1.5,10, 3), 100, 15, vec3 (1, -1.25, 2)));
    
    //set power value for Phong shading
    power = 50;
}

//tabletop with spotlight only
void ofApp::sceneSetup9wS(){
    
    //set background color to black
    ofSetBackgroundColor (ofColor::black);
    
    scene.push_back (new Plane (vec3(0,-2,2), ofColor::white, 20, 30, true));
    
    lights.push_back (new Light (vec3(-7,7,0), 75));
    lights.push_back(new Light (vec3 (-1.5,10, -5), 100));
    lights.push_back (new Light (vec3(7,7,0), 75));
    ambient = Light (renderCam.getPosition(), 20, 5);
    
    spotlights.push_back(new Spotlight (vec3 (-1.5,10, 3), 100, 15, vec3 (1, -1.25, 2)));
    
    //set power value for Phong shading
    power = 50;
}

//tabletop with spotlight only
void ofApp::sceneSetup10wS(){
    //set background color to black
    ofSetBackgroundColor (ofColor::black);
    
    //push objects into scene
    scene.push_back (new Plane (vec3(0,-2,2), ofColor::white, 20, 30, true));
    
    lights.push_back (new Light (vec3(4,7,-5), 30));
    lights.push_back (new Light (vec3(-7,7,0), 30));
    ambient = Light (renderCam.getPosition(), 20, 5);
    
    spotlights.push_back(new Spotlight (vec3 (-5,10, 0), 75, 35, vec3 (-1.5,0, -3)));
    spotlights.push_back(new Spotlight (vec3 (-1.5,10, 3), 100, 15, vec3 (1, -1.25, 2)));
    
    //set power value for Phong shading
    power = 50;
}

//wood background and floor with 4 spheres + spotlight
void ofApp::sceneSetup11(){
    //set background color to black
    ofSetBackgroundColor (ofColor::black);
    
    //push objects into scene
    
    //add spheres
    scene.push_back (new Sphere (vec3 (1.5, -0.25, -5), 1.5, ofColor::purple));
    scene.push_back (new Sphere (vec3 (-1.25,0, -3), 2, ofColor::cyan));
    scene.push_back (new Sphere (vec3 (0,-0.75, 0), 1.25, ofColor::lawnGreen));
    scene.push_back (new Sphere (vec3 (1, -1.25, 2), 0.75, ofColor::hotPink));
    ambient = Light (renderCam.getPosition(), 20, 5);
    
    //add planes
    scene.push_back (new Plane (vec3(0,-2,2), ofColor::white, 30, 70, true)); //horizontal plane
    scene.push_back (new Plane (vec3(0,10,-7), ofColor::white, 30, 50, false)); //vertical plane
    
    //add lights
    lights.push_back (new Light (vec3(-7,8, 1), 55)); //4,7,5
    spotlights.push_back(new Spotlight (vec3 (4,9,5), 80, 40, vec3 (0,-3, -2)));
    
    //set power value for Phong shading
    power = 50;
    
    //load texture images
    textureDiffuseH.load ("woodDiff.jpg"); //load texture image
    textureSpectureH.load("woodSpec.jpg"); //load texture image
    
    textureDiffuseV.load ("wood2Diff.jpg"); //load texture image
    textureSpectureV.load("wood2Spec.jpg"); //load texture image
    
    textureWidthH = textureDiffuseH.getWidth();
    textureHeightH = textureDiffuseH.getHeight();
    
    textureWidthV = textureDiffuseV.getWidth();
    textureHeightV = textureDiffuseV.getHeight();
    
    //set num of "texture tiles" in both directions
    numTilesHorizontal = 10;
    numTilesVertical = 10;
    
}

//cobblestone ground with 4 spheres + 1 spotlight
void ofApp::sceneSetup12(){
    //set background color to black
    ofSetBackgroundColor (ofColor::black);
    
    //push objects into scene
    scene.push_back (new Plane (vec3(0,-2,2), ofColor::white, 30, 70, true));
    
    //push spheres into scene
    scene.push_back (new Sphere (vec3 (3, 0, -5), 1.5, ofColor::red));
    scene.push_back (new Sphere (vec3 (-1.25,1, -3), 2, ofColor::white));
    scene.push_back (new Sphere (vec3 (1,0.5, 0), 0.75, ofColor::black));
    scene.push_back (new Sphere (vec3 (-3.25,0, 0), 1, ofColor::green));
    
    ambient = Light (renderCam.getPosition(), 15, ofColor::black);
    
    //add lights
    lights.push_back (new Light (vec3(-7,8, 1), 55)); //4,7,5
    spotlights.push_back(new Spotlight (vec3 (2,8,5), 60, 50, vec3 (-0.4,-2, -3)));
    
    //set power value for Phong shading
    power = 50;
    
    //load texture images
    textureDiffuseH.load ("cobblestoneDiff.jpg"); //load texture image
    textureSpectureH.load("cobblestoneSpec.jpg"); //load texture image
    
    textureWidthH = textureDiffuseH.getWidth();
    textureHeightH = textureDiffuseH.getHeight();
    
    //set num of "texture tiles" in both directions
    numTilesHorizontal = 12;
    numTilesVertical = 10;
}

//brick wall and floor with 6 rainbow colored spheres
void ofApp::sceneSetup13(){
    //set background color to black
    ofSetBackgroundColor (ofColor::black);
    
    //push objects into scene
    //push planes into scene
    scene.push_back (new Plane (vec3(0,-2,2), ofColor::white, 30, 70, true));
    scene.push_back (new Plane (vec3(0,-2,-7), ofColor::white, 30, 70, false));
    
    //push spheres into scene
    scene.push_back (new Sphere (vec3 (3.75, -0.5, -5), 1.5, ofColor::green));
    scene.push_back (new Sphere (vec3 (-1,1, -3), 1.75, ofColor::purple));
    scene.push_back (new Sphere (vec3 (1.25,0.5, 0), 0.75, ofColor::blue));
    scene.push_back (new Sphere (vec3 (-2.5,0.75, 3), 0.5, ofColor::red));
    scene.push_back (new Sphere (vec3 (-2.75,-0.75, 0), 1, ofColor::orange));
    scene.push_back (new Sphere (vec3 (0.25,-1, 2), 0.5, ofColor::yellow));
    
    
    ambient = Light (renderCam.getPosition(), 15, ofColor::black);
    
    
    lights.push_back (new Light (vec3(-7,8, 1), 55)); //4,7,5
    lights.push_back (new Light (vec3(0,8, 3), 60)); //4,7,5
    
    
    //set power value for Phong shading
    power = 50;
    
    //load texture images
    textureDiffuseH.load ("grayWallDiff.jpg"); //load texture image
    textureSpectureH.load("grayWallSpec.jpg"); //load texture image
    
    textureDiffuseV.load ("redWallDiff.jpg"); //load texture image
    textureSpectureV.load("redWallSpec.jpg"); //load texture image
    
    
    textureWidthH = textureDiffuseH.getWidth();
    textureHeightH = textureDiffuseH.getHeight();
    
    textureWidthV = textureDiffuseV.getWidth();
    textureHeightV = textureDiffuseV.getHeight();
    
    //set num of "texture tiles" in both directions
    numTilesHorizontal = 12;
    numTilesVertical = 12;
}

bool ofApp::objSelected(SceneObject* objPtr){
    //return (selected.size() ? true : false );
    int i = 0;
    while (i < selected.size()){
        if (selected[i] == objPtr){
            return true;
        }
        i++;
    }
    return false;
}

//find index of obj in scene vector
int ofApp::findIndex (SceneObject* objPtr){
    int i = 0;
    while (i < scene.size()){
        if (scene[i] == objPtr){
            return i;
        }
        i++;
    }
    return -1;
}

//if (selectMultipleEnabled){
//
//    if (selected.size() != 0){
//        SceneObject* parent = selected[0];
//        closestObj -> setParent(parent);
//    }
//}

bool ofApp::atLeastOneSelected(){
   // cout << selected.size() << endl;
    return (selected.size() > 0 ? true : false );
}
