#include "demoParticle.h"


//------------------------------------------------------------------
demoParticle::demoParticle(){
	
}

//------------------------------------------------------------------
void demoParticle::reset(){
	//the unique val allows us to set properties slightly differently for each particle
	uniqueVal = ofRandom(-10000, 10000);
	
	pos.x = ofRandomWidth();
	pos.y = ofRandom(0, 20);
	
	vel.x = ofRandom(-3.9, 3.9);
	vel.y = ofRandom(-3.9, 3.9);
	
	frc   = ofPoint(0,0,0);
	
	scale = ofRandom(0.5, 1.0);
	
	drag  = ofRandom(0.97, 0.99);
	vel.y = fabs(vel.y) * 3.0; //make the particles all be going down
}

//------------------------------------------------------------------
void demoParticle::update(){
	//lets simulate falling snow 
	//the fake wind is meant to add a shift to the particles based on where in x they are
	//we add pos.y as an arg so to prevent obvious vertical banding around x values - try removing the pos.y * 0.006 to see the banding
	float fakeWindX = ofSignedNoise(pos.x * 0.003, pos.y * 0.006, ofGetElapsedTimef() * 0.6);
	
	frc.x = fakeWindX * 0.25 + ofSignedNoise(uniqueVal, pos.y * 0.04) * 0.6;
	frc.y = ofSignedNoise(uniqueVal, pos.x * 0.006, ofGetElapsedTimef()*0.2) * 0.09 + 0.18;

	vel *= drag; 
	vel += frc * 0.4;
		
	//we do this so as to skip the bounds check for the bottom and make the particles go back to the top of the screen
	if( pos.y + vel.y > ofGetHeight() ){
		pos.y -= ofGetHeight();
	}
	
	//2 - UPDATE OUR POSITION
	//removed and put in ofApp
	
	//3 - (optional) LIMIT THE PARTICLES TO STAY ON SCREEN 
	//we could also pass in bounds to check - or alternatively do this at the ofApp level
	if( pos.x > ofGetWidth() ){
		pos.x = ofGetWidth();
		vel.x *= -1.0;
	}else if( pos.x < 0 ){
		pos.x = 0;
		vel.x *= -1.0;
	}
	if( pos.y > ofGetHeight() ){
		pos.y = ofGetHeight();
		vel.y *= -1.0;
	}
	else if( pos.y < 0 ){
		pos.y = 0;
		vel.y *= -1.0;
	}	
	
}

//------------------------------------------------------------------
void demoParticle::draw(){
	ofSetColor(255);
	ofFill();
	ofDrawCircle(pos.x, pos.y, scale * 4.0);
}

void demoParticle::move() {
	pos += vel;
}

void demoParticle::moveUp() {
	if(pos.y > 0){
		pos.y -= 1;
	}
}
