#include "ofApp.h"

ofFbo fbo;
ofShader shader;

ofVideoPlayer video1;
ofVideoPlayer video2;
ofSoundPlayer audio;

float elapsedTime;

//--------------------------------------------------------------
void ofApp::setup() {
    shader.load("fragShader");

    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    
    ofSetWindowTitle("Video thingies");
    ofSetWindowShape(3840, 2160);
    ofSetFrameRate(25);
    ofBackground(ofColor::white);
    
    video1.load("een.mov");
    video2.load("twee.mov");
    video1.setVolume(0.0);
    video1.play();
    video2.play();
    video1.setSpeed(1.5);
    video2.setSpeed(4.0);
    video1.setPosition(0.13);
    
    audio.load("drie.wav");
    audio.play();
}

//--------------------------------------------------------------
void ofApp::update() {
    video1.update();
    video2.update();
    
    elapsedTime = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::draw() {
    shader.begin();
    fbo.begin();
    ofSetBackgroundAuto(false);
    ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofDisableSmoothing();
    
    shader.setUniformTexture("texture0", video1.getTexture(), 0);
    shader.setUniformTexture("texture1", video2.getTexture(), 1);
    
    shader.setUniform1f("time", elapsedTime);
        
    //ofEnableAlphaBlending();
    video1.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    video2.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    //ofEnableAlphaBlending();
                
    ofEnableSmoothing();

    fbo.end();
    shader.end();
        
    fbo.draw(0, 0, ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer & buffer) {

}
 
//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    
}

void ofApp::exit() {
    
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
