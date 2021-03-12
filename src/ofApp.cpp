#include "ofApp.h"

ofFbo fbo;
ofShader shader;

ofVideoPlayer video1;
ofVideoPlayer video2;
//ofVideoGrabber camera;
//ofxFaceTracker2 tracker;
ofSoundStream micInput;

float soundLevel;
float elapsedTime;

//--------------------------------------------------------------
void ofApp::setup() {
    //tracker.setup();

    shader.load("fragShader");

    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    
    ofSetWindowTitle("Video thingies");
    ofSetWindowShape(1280, 720);
    ofSetFrameRate(30);
    ofBackground(ofColor::white);
    
    video1.load("een.mov");
    video2.load("twee.mov");
    video1.play();
    video2.play();
    video1.setPosition(0.5);
    
    //camera.setDeviceID(0);
    //camera.setDesiredFrameRate(30);
    //camera.initGrabber(1280, 720);
    
    soundLevel = 0.0;
    
    ofSoundStreamSettings settings;
    auto devices = micInput.getMatchingDevices("default");
    if (!devices.empty()) {
        settings.setInDevice(devices[0]);
    }
    settings.setInListener(this);
    settings.sampleRate = 44100;
    settings.numOutputChannels = 0;
    settings.numInputChannels = 1;
    settings.bufferSize = 44100;
    micInput.setup(settings);
}

//--------------------------------------------------------------
void ofApp::update() {
    video1.update();
    video2.update();
    //if (camera.isInitialized()) {
        //camera.update();
        
        //if (camera.isFrameNew()) {
        //    tracker.update(camera);
        //}
    //}
    
    elapsedTime = ofGetElapsedTimef();

    // std::printf("Elapsed %f\n", elapsedTime);
    // std::printf("Noise %f\n", ofNoise(elapsedTime));
    // std::printf("RMS %f\n", video1Alpha);
}

//--------------------------------------------------------------
void ofApp::draw() {
    //if (camera.isInitialized()) {
    shader.begin();
    fbo.begin();
    ofSetBackgroundAuto(false);
    ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofDisableSmoothing();
    
    shader.setUniformTexture("texture0", video1.getTexture(), 0);
    shader.setUniformTexture("texture1", video2.getTexture(), 1);
    
    float alphaLevel = soundLevel * 50.0;
    if (alphaLevel > 0.8) alphaLevel = 0.8;
    if (alphaLevel < 0.4) alphaLevel = 0.4;
    
    // std::printf("sound %f\n", alphaLevel);
    shader.setUniform1f("time", elapsedTime);
    shader.setUniform1f("alpahVal", soundLevel);
        
    //ofEnableAlphaBlending();
    video1.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    video2.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    //for(auto face : tracker.getInstances()) {
        // Apply the pose matrix
    //    ofPushView();
    //    face.loadPoseMatrix();
    //    video2.draw(0, 0, ofGetWidth(), ofGetHeight());
    //    ofPopView();
    //}
    
    //ofEnableAlphaBlending();
                
    ofEnableSmoothing();

    fbo.end();
    shader.end();
        
    fbo.draw(0, 0, ofGetWidth(), ofGetHeight());
    // tracker.drawDebug();
    // tracker.drawDebugPose();
    //}
}

void ofApp::audioIn(ofSoundBuffer & buffer) {
    // std::printf("RMS %f\n", buffer.getRMSAmplitude());
    soundLevel = buffer.getRMSAmplitude();
}

void ofApp::exit() {
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if ( key == ' ' ) {
     ofImage image;
     image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
     image.save("screen.png");
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
