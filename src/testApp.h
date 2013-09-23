#pragma once

#include "ofMain.h"
#include "ofxKinect.h"
#include "ofxOpenCv.h"
#include "ofxXmlSettings.h"


class testApp : public ofBaseApp{

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

		ofxKinect kinect;
		float kAngle;
		bool doFbo;
		int erodeNtimes;

    ofxCvGrayscaleImage grayImage, frontPanelGradient, backPanelGradient, warpedImage;

		ofImage loadedFrontPanel, loadedBackPanel;

		void isPixelBetweenPanels(ofxCvGrayscaleImage & gray, ofxCvGrayscaleImage & frontGradient, ofxCvGrayscaleImage & backGradient);

    ofFbo kinectFbo;

    //warp stuff
    ofPoint *				srcPositions;
    ofPoint *				dstPositions;

    ofxXmlSettings XML;
};
