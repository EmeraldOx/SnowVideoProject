#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
	camWidth = 320;  // try to grab at this size.
	camHeight = 240;

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
	resetParticles();

	Instructions = "S to reset snow. Spacebar to reset background.";
}

void ofApp::resetParticles() {

	for (unsigned int i = 0; i < p.size(); i++) {
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
			p[i].update();
			scaledY = p[i].pos.y * (grayDiff.getHeight() / 768);
			scaledX = p[i].pos.x * (grayDiff.getWidth() / 1024);
			pixelLocation = ((scaledY * camWidth) + scaledX);
			if (grayDiffPixels[pixelLocation] < 255) {
				p[i].move();
			}
			else {
				while (grayDiffPixels[pixelLocation] == 255 && p[i].pos.y > 0) {
					p[i].moveUp();
					scaledY = p[i].pos.y * (grayDiff.getHeight() / 768);
					scaledX = p[i].pos.x * (grayDiff.getWidth() / 1024);
					pixelLocation = ((scaledY * camWidth) + scaledX);
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetHexColor(0xffffff);
	
	if (ofGetKeyPressed('d')) {
		grayDiff.draw(0, 0, 1024, 768);
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
	}
	else {
		vidGrabber.draw(0, 0, 1024, 768);
	}

	ofColor c(255, 255, 255);
	
	for (unsigned int i = 0; i < p.size(); i++) {
		p[i].draw();
	}

	ofSetColor(0);
	ofDrawBitmapString(Instructions, 50, 50, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	if (key == 's') {
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