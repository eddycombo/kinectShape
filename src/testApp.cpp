#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

  ofBackground(0);
  ofSetFrameRate(60);

  kinect.init(false, false);
  kinect.open();
  kinect.setDepthClipping(500, 3000);
  kAngle = 30;
	kinect.setCameraTiltAngle(kAngle);

  grayImage.allocate(kinect.width, kinect.height);

  warpedImage.allocate(kinect.width, kinect.height);

  frontPanelGradient.allocate(kinect.width, kinect.height);
  backPanelGradient.allocate(kinect.width, kinect.height);

  loadedFrontPanel.loadImage("/home/ekko/Desktop/front.png");
  loadedBackPanel.loadImage("/home/ekko/Desktop/back.png");

  frontPanelGradient.setFromPixels(loadedFrontPanel.getPixels(), kinect.width, kinect.height);
  backPanelGradient.setFromPixels(loadedBackPanel.getPixels(), kinect.width, kinect.height);

  kinectFbo.allocate(kinect.width, kinect.height, GL_RGBA);
  doFbo = true;
  erodeNtimes = 2;

  if( XML.loadFile("/home/ekko/Desktop/corners.xml") ){
              cout<<"XML loaded"<<endl;
      }else{
              cout<<"unable to load XML"<<endl;
    }


  //warpStuff
  srcPositions  = new ofPoint[4];
    srcPositions[0].set(XML.getValue("SRC:X1", 0), XML.getValue("SRC:Y1", 0), 0);
    srcPositions[1].set(XML.getValue("SRC:X2", kinect.width), XML.getValue("SRC:Y2", 0), 0);
    srcPositions[2].set(XML.getValue("SRC:X3", kinect.width), XML.getValue("SRC:Y3", kinect.height), 0);
    srcPositions[3].set(XML.getValue("SRC:X4", 0), XML.getValue("SRC:Y4", kinect.height), 0);

    dstPositions  = new ofPoint[4];
    dstPositions[0].set(0, 0, 0);
    dstPositions[1].set(kinect.width, 0, 0);
    dstPositions[2].set(kinect.width, kinect.height, 0);
    dstPositions[3].set(0, kinect.height, 0);

}

void testApp::isPixelBetweenPanels(ofxCvGrayscaleImage & gray, ofxCvGrayscaleImage & frontGradient, ofxCvGrayscaleImage & backGradient){

      unsigned char * pix = gray.getPixels();

			unsigned char * pan1Pix = frontGradient.getPixels();
			unsigned char * pan2Pix = backGradient.getPixels();

			int numPixels = gray.getWidth() * gray.getHeight();
			for(int i = 0; i < numPixels; i++) {
				if(pix[i] <  pan1Pix[i]  && pix[i] > pan2Pix[i]) {
					pix[i] = pix[i];
				} else {
					pix[i] = 0;
				}
			}
			gray.flagImageChanged();
}
//--------------------------------------------------------------
void testApp::update(){

  kinect.update();


    if(kinect.isFrameNew()) {

        grayImage.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);

        grayImage.blur();

        isPixelBetweenPanels(grayImage, frontPanelGradient, backPanelGradient);

        grayImage.threshold(100);

        for(int i = 0; i<erodeNtimes; i++){
          grayImage.erode_3x3();
        }

        warpedImage.warpIntoMe(grayImage, srcPositions, dstPositions);

        kinectFbo.begin();
          warpedImage.draw(0, 0);
          //shapeFinder.draw(0, 0);
        kinectFbo.end();
      }

      //then take the texture out of the fbo and pass it to syphon;
}

//--------------------------------------------------------------
void testApp::draw(){

  if(doFbo){

    kinectFbo.draw(0, 0);
  }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){



}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
