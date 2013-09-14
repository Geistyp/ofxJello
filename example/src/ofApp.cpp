#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	//ofSetFrameRate(60);

	dragBody = NULL;
	dragPoint = -1;

	/*
	这个值对碰撞影响很大
	World.mPenetrationThreshold = 3.f; 
	*/
	mWorld = new World();
	mWorld->SetGravity(Vector2(0, 9.8f*2));
	mWorld->setWorldLimits(Vector2(0, 0), Vector2(1024, 768));

	// OF 要注意顺序方向 逆时针
	//  + <- +
	//  V    A
	//  + -> +
	ClosedShape *shape1 = new ClosedShape();
	shape1->begin();
    shape1->addVertex(Vector2(0, 0));
	shape1->addVertex(Vector2(0, 20));
	shape1->addVertex(Vector2(800, 20));
    shape1->addVertex(Vector2(800, 0));
    
    
    shape1->finish();

	bod = new Body(shape1,0,Vector2(512, 600),0,Vector2::One,false);
	mWorld->addBody(bod);

	ball = new ClosedShape();
	ball->begin();
	for (int i = 0; i < 360; i += 20)
    {
		ball->addVertex(Vector2(cos(VectorTools::ToRadians((float)-i)), sin(VectorTools::ToRadians((float)-i))) * Vector2(30, 30));
    }
	ball->finish();

	//pressure body
	pb = new PressureBody(ball, 1.0f, 50.0f, 10.0f, 1.0f, 300.0f, 20.0f, Vector2(512, 400), 0, Vector2(1.f,1.f),false);

	mWorld->addBody(pb);
	pressureBodies.push_back(pb);

	//I shape
	springI = new ClosedShape();
    springI->begin();
    springI->addVertex(Vector2(0, 0));
	springI->addVertex(Vector2(0, 40));
	springI->addVertex(Vector2(40, 40));
	springI->addVertex(Vector2(40, 0));

    springI->finish();

	leftB = new SpringBody(springI, 1.0f, 150.0f, 5.0f, 300.0f, 15.0f, Vector2(512, 200), 0.0f, Vector2::One,false);
	leftB->addInternalSpring(0, 1, 300.0f, 10.0f);
    leftB->addInternalSpring(1, 2, 300.0f, 10.0f);
    leftB->addInternalSpring(2, 3, 300.0f, 10.0f);
    leftB->addInternalSpring(3, 0, 300.0f, 10.0f);
	leftB->addInternalSpring(0, 2, 300.0f, 10.0f);
	//leftB->addInternalSpring(1, 3, 300.0f, 10.0f);

	// polygons!
    leftB->addTriangle(0, 1, 2);
    leftB->addTriangle(0, 2, 3);
    leftB->finalizeTriangles();

	mWorld->addBody(leftB);
	springBodies.push_back(leftB);
}

//--------------------------------------------------------------
void ofApp::update(){
	float t = ofClamp(ofGetLastFrameTime(), 0, 0.1 );
	//float t = 1.0/120.0f;		// Is this better than realtime?
	mWorld->update(ofGetLastFrameTime());
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackgroundGradient(ofColor(30, 30, 50), ofColor(100, 120, 100),  OF_GRADIENT_LINEAR );

	Renderer::RenderGlobalShapeLine(bod->mPointMasses, 1, 1, 1);

	for(unsigned int i = 0;i < pressureBodies.size();i++)
	{
		Renderer::RenderGlobalShapeLine(pressureBodies[i]->mPointMasses, 0.8, 0, 0.5);
		Renderer::RenderShapeNormal(pressureBodies[i]->mPointMasses, 0.5, 0.5, 0.5);
	}

	for(unsigned int i = 0;i < springBodies.size();i++)
	{
		Renderer::RenderGlobalShapeLine(springBodies[i]->mPointMasses, 0, 0.7, 0);
		Renderer::RenderShapeNormal(springBodies[i]->mPointMasses, 0.5, 0.5, 0.5);
	}

	//draw line from body to cursor
	if(dragBody != NULL)
	{
		Renderer::RenderLine(dragBody->getPointMass(dragPoint)->Position,Vector2(dragX,dragY),0,0,1);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if ( key == 'p' )
	{
		PressureBody * pressureBody = new PressureBody(ball, 1.0f, 50.0f, 10.0f, 1.0f, 300.0f, 20.0f, Vector2(512, 400), 0, Vector2(1.f,1.f),false);

		mWorld->addBody(pressureBody);
		pressureBodies.push_back(pressureBody);
	}

	if ( key == 's' )
	{
		SpringBody *leftB = new SpringBody(springI, 1.0f, 150.0f, 5.0f, 300.0f, 15.0f, Vector2(512, 200), 0.0f, Vector2::One,false);
		leftB->addInternalSpring(0, 1, 300.0f, 10.0f);
		leftB->addInternalSpring(1, 2, 300.0f, 10.0f);
		leftB->addInternalSpring(2, 3, 300.0f, 10.0f);
		leftB->addInternalSpring(3, 0, 300.0f, 10.0f);
		leftB->addInternalSpring(0, 2, 300.0f, 10.0f);
		//leftB->addInternalSpring(1, 3, 300.0f, 10.0f);

		// polygons!
		leftB->addTriangle(0, 1, 2);
		leftB->addTriangle(0, 2, 3);
		leftB->finalizeTriangles();

		mWorld->addBody(leftB);
		springBodies.push_back(leftB);

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
	dragX = x;
	dragY = y;
	if (dragBody != NULL)
    {
        PointMass *pm = dragBody->getPointMass(dragPoint);
		dragBody->setDragForce(VectorTools::calculateSpringForce(pm->Position, pm->Velocity, Vector2(dragX,dragY), Vector2::ZERO, 0.0f, 100.0f, 10.0f), dragPoint);
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	dragX = x;
	dragY = y;
	if(dragBody == NULL)
	{
		int body;
        mWorld->getClosestPointMass(Vector2(dragX,dragY), body, dragPoint);
		if(mWorld->getBody(body)->Type == 2)
			dragBody = (SpringBody*)mWorld->getBody(body);
	}
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	 dragBody = NULL;
     dragPoint = -1;
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
