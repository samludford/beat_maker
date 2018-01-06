#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofBackground(0);
    
    // audio setup
    sampleRate 	= 44100;
    bufferSize	= 512;
    
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4); /* this has to happen at the end of setup - it switches on the DAC */
    
    for(int i=0 ; i < SOUNDS ; i++) {
        samples[i].load(ofToDataPath("t_" + ofToString(i+1) + ".wav"));
        params.add(divisions[i].set("divisions " + ofToString(i+1), div_defaults[i], 1, 16));
        params.add(offsets[i].set("offset " + ofToString(i+1), 0, 0, 15));
        params.add(speeds[i].set("speed " + ofToString(i+1), 1, 1, 10));
    }
    
    gui.setup(params);
    
    ofSetCircleResolution(100);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2.0, ofGetHeight()/2.0);
    
    for(int i=0 ; i<SOUNDS ; i++) {
        draw_at(i);
    }
    
    ofPopMatrix();
    
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
    for (int i = 0; i < bufferSize; i++){
        
        currentCount = (int) timer.phasor(8);

        if(lastCount != currentCount) {
        
            for(int i = 0 ; i< SOUNDS ; i++) {
                triggers[i] = ((playHead - offsets[i]) % divisions[i] == 0);
            }
            
            lastCount = 0;
            playHead++;

        }
        
        for(int i=0 ; i < SOUNDS ; i++) {
            if(triggers[i] == 1) {
                samples[i].trigger();
            }
        }
        
        wave = 0.0;
        for(int i=0 ; i< SOUNDS ; i++) {
            wave += samples[i].playOnce(speeds[i]);
        }

        output[i*nChannels    ] = wave;
        output[i*nChannels + 1] = wave;
        
        for(int i=0 ; i < SOUNDS ; i++) {
            triggers[i] = 0;
        }

    }
    
    
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    for(int i = 0; i < bufferSize; i++){
        
    }
    
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
    
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
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

// utilities

void ofApp::draw_at(int index) {
    
    ofNoFill();
    ofSetColor(20);
    ofDrawEllipse(0,0, RAD*((index+1)*2), RAD*((index+1)*2));
    ofSetColor(255);
    
    int s = divisions[index];
    float sf = (float) s;
    float angle = 360.0 / sf;
    
    int pos = playHead % s;
    
    for(int i = 0 ; i < s ; i++) {
        ofPushMatrix();
        
        ofRotate(angle * i);
        
        float size = SIZE;
        
        if(i==(offsets[index] % s)) {
            ofSetColor(220);
            size *= 2;
//            ofDrawLine(0, 0, RAD * (index+1) - SIZE/2.0, 0);
        } else {
            ofSetColor(40);
        }
        
        ofTranslate(RAD * (index+1), 0);
        
        if(i == pos) {
            ofFill();
            ofDrawEllipse(0, 0, size, size);
        } else {
            ofNoFill();
        }
        
//        ofDrawEllipse(0, 0, SIZE, SIZE);
        ofPopMatrix();
    }
    
}

