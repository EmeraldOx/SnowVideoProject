#pragma once
#include "ofMain.h"

enum particleMode{
	PARTICLE_MODE_NOISE
};

class demoParticle{

	public:
		demoParticle();
		
		void setMode(particleMode newMode);	

		void reset();
		void update();
		void draw();		
		
		ofPoint pos;
		ofPoint vel;
		ofPoint frc;
		
		float drag; 
		float uniqueVal;
		float scale;
		
		particleMode mode;

		void move();
		void moveUp();
};