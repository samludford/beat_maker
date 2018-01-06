#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxGui.h"
#include "maxiGrains.h"
#include <sys/time.h>

typedef hannWinFunctor grainPlayerWin;

#define SOUNDS 6

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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    // Audio output and input methods
    
        void audioOut(float * output, int bufferSize, int nChannels);
        void audioIn(float * input, int bufferSize, int nChannels);
     
     
    
    int		bufferSize; /* buffer size */
    int		sampleRate;
    
    
    
    maxiOsc timer;
    
    int currentCount, lastCount, playHead;
    
    double wave;
    

    maxiSample samples[SOUNDS];
    int triggers[SOUNDS];
    
    int div_defaults[6] = {5, 6, 3, 7, 11, 8};
    
    
    ofxPanel gui;
    ofParameterGroup params;
    ofParameter<int> divisions[SOUNDS];
    ofParameter<int> offsets[SOUNDS];
    ofParameter<double> speeds[SOUNDS];
    
    
    void draw_at(int index);

    
    const float RAD = 30.0;
    const float SIZE = 20;
    
};
