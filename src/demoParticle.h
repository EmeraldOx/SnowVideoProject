#pragma once
#include "ofMain.h"

enum particleMode{
	PARTICLE_MODE_NOISE
};

class demoParticle{

	public:
		demoParticle();

		void reset();
		void update();
		void draw();		
		
		ofPoint pos;
		ofPoint vel;
		ofPoint frc;
		
		float drag; 
		float uniqueVal;
		float scale;

		void move();
		void moveUp();
};