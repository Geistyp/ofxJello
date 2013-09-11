#pragma once

#include "ofMain.h"

#include "Vector2.h"
#include "Vector3.h"
#include "VectorTools.h"
#include "AABB.h"
#include "Bitmask.h"
#include "PointMass.h"
#include "InternalSpring.h"
#include "ClosedShape.h"
#include "Body.h"
#include "SpringBody.h"
#include "PressureBody.h"
#include "World.h"

#include "Renderer.h"

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

		World *mWorld;
		Body *bod;

		std::vector<SpringBody*> springBodies;
		std::vector<PressureBody*> pressureBodies;
		std::vector<FallingBody*> fallingBodies;

		ClosedShape *ball,*springI,*box;
		ClosedShape *shape;

		PressureBody *pb;

		SpringBody *leftB,*rightB,*dragBody;

		float dragX,dragY;
		int dragPoint;
		
};
