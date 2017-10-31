#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
	//will change size later
	camWidth = 640;  // try to grab at this size.
	camHeight = 480;

	vidGrabber.setDeviceID(0);
	vidGrabber.setDesiredFrameRate(60);
	vidGrabber.initGrabber(camWidth, camHeight);

	colorImg.allocate(camWidth, camHeight);
	grayImage.allocate(camWidth, camHeight);
	grayBg.allocate(camWidth, camHeight);
	grayDiff.allocate(camWidth, camHeight);
	bLearnBackground = false;
	
	ofSetVerticalSync(true);

	int num = 1500;
	p.assign(num, demoParticle());
	currentMode = PARTICLE_MODE_NOISE;
	resetParticles();
}

void ofApp::resetParticles() {

	for (unsigned int i = 0; i < p.size(); i++) {
		p[i].setMode(currentMode);
		p[i].reset();
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	ofBackground(100, 100, 100);
	vidGrabber.update();

	if (vidGrabber.isFrameNew()) {
		ofPixels & pixels = vidGrabber.getPixels();

		//contourfinder stuff
		colorImg.setFromPixels(pixels);
		grayImage = colorImg;
		if (bLearnBackground == true) {
			grayBg = grayImage;
			bLearnBackground = false;
		}
		grayDiff.absDiff(grayBg, grayImage);
		grayDiff.threshold(30);
		contourFinder.findContours(grayDiff, 20, (camWidth*camHeight), 10, true);

		grayDiffPixels = grayDiff.getPixels();



		for (unsigned int i = 0; i < p.size(); i++) {
			p[i].setMode(currentMode);
			p[i].update();
			pixelLocation = ((p[i].pos.y * camWidth) + p[i].pos.x);
			ofLogNotice() << pixelLocation;
			if (grayDiffPixels[pixelLocation] < 255) {
				p[i].move();
			}
			else {
				//p[i].moveUp();
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetHexColor(0xffffff);
	
	if (ofGetKeyPressed('d')) {
		grayDiff.draw(0, 0, camWidth, camHeight);
	}
	else {
		vidGrabber.draw(0, 0);
	}
	ofColor c(255, 255, 255);
	for (int i = 0; i < contourFinder.nBlobs; i++) {
		contourFinder.blobs[i].draw(0, 0);

		// draw over the centroid if the blob is a hole
		ofSetColor(255);
		if (contourFinder.blobs[i].hole) {
			ofDrawBitmapString("hole",
				contourFinder.blobs[i].boundingRect.getCenter().x,
				contourFinder.blobs[i].boundingRect.getCenter().y);
		}
	}
	
	for (unsigned int i = 0; i < p.size(); i++) {
		p[i].draw();
	}

	ofSetColor(190);

	ofSetColor(230);
	ofDrawBitmapString(currentModeStr + "\n\nSpacebar to reset. \nKeys 1-4 to change mode.", 10, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	if (key == '4') {
		currentMode = PARTICLE_MODE_NOISE;
		currentModeStr = "4 - PARTICLE_MODE_NOISE: snow particle simulation";
		resetParticles();
	}

	if (key == ' ') {
		resetParticles();
	}
	if (key == ' ') {
		bLearnBackground = true;
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

void ofApp::collideCheck() {
	//what are the inputs?
	//output: translate moved object
}