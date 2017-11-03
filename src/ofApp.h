#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "demoParticle.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void resetParticles();

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

		string Instructions;
		vector <demoParticle> p;

		ofVideoGrabber vidGrabber;

		int camWidth;
		int camHeight;

		//contourfinder stuff
		bool bLearnBackground;
		ofxCvColorImage colorImg;
		ofxCvGrayscaleImage grayImage, grayBg, grayDiff;
		ofxCvContourFinder contourFinder;

		ofPixels grayDiffPixels;
		int pixelLocation;
		int scaledY;
		int scaledX;
		
};
