#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup() {

	/// setup for kinect stuff 
    ofSetLogLevel(OF_LOG_VERBOSE);

	kinect.close();
    kinect2.close();
    kinect3.close();
    kinect4.close();
    kinect5.close();
    kinect6.close();

	kinect.init(false, false);
	kinect.setVerbose(true);
	kinect.open();

	kinect2.init(false, false);
    kinect2.open();

    kinect3.init(false, false);
    kinect3.open();

	kinect4.init(false, false);
    kinect4.open();
	
    kinect5.init(false, false);
    kinect5.open();

    kinect6.init(false, false);
    kinect6.open();
	


	ofSetFrameRate(30);

	stepNumber = 4;
	


	cameraWidth = 640;
	cameraSpace = ofGetWidth()/6;
	screenRatio = cameraSpace/cameraWidth;
	camera2Screen = screenRatio*cameraWidth;


	kup = 0;
	kup2 = 0;
	kup3 = 0;
	kup4 = 0;
	kup5 = 0;
	kup6 = 0;

	kleftAdd = 0;
	kleft2Add = 0;
	kleft3Add = 0;
	kleft4Add = 0;
	kleft5Add = 0;
	kleft6Add = 0;
	//THESE VALUES CALCULATED FROM TEST
	kleft = 493;
	kleft2 = 1351;
	kleft3 = 2249;
	kleft4 = 3148;
	kleft5 = 4211;
	kleft6 = 5096;

	multiplier1 = 20;

	tanTimes = tanf(57/2);

	calculateWidth = true;

}

//--------------------------------------------------------------
void testApp::update() {
	ofBackground(0,0,0);

// update for kinect system 
	cameraWidth = 640;
	cameraSpace = ofGetWidth()/6;
	screenRatio = cameraSpace/cameraWidth;
	camera2Screen = screenRatio*cameraWidth;

   
    kinect.update();

    kinect2.update();

	kinect3.update();

    kinect4.update();
	
	kinect5.update();

	kinect6.update();

	
}

//--------------------------------------------------------------
void testApp::draw() {


	// drawing the kinect system

	ofSetRectMode(OF_RECTMODE_CENTER);
	ofSetColor(255,255,255);
		ofPushMatrix();
			ofTranslate(kleft+kleftAdd, kup);
			drawPointCloud3(kleft+kleftAdd, kup);
		ofPopMatrix();

		ofPushMatrix();
			ofTranslate(kleft2+kleft2Add, kup2);
			drawPointCloud4(kleft2+kleft2Add, kup2);
		ofPopMatrix();
	
		ofPushMatrix();
			ofTranslate(kleft3+kleft3Add, kup3);
			drawPointCloud(kleft3+kleft3Add, kup3);
		ofPopMatrix();

		ofPushMatrix();
			ofTranslate(kleft4+kleft4Add, kup4);
			drawPointCloud5(kleft4+kleft4Add, kup4);
		ofPopMatrix();

		ofPushMatrix();
			ofTranslate(kleft5+kleft5Add, kup5);
			drawPointCloud2(kleft5+kleft5Add, kup5);
		ofPopMatrix();
		
		ofPushMatrix();
			ofTranslate(kleft6+kleft6Add, kup6);
			drawPointCloud6(kleft6+kleft6Add, kup6);
		ofPopMatrix();
	

	// draw instructions

	ofSetColor(255, 255, 255);
	stringstream reportStream;
	reportStream << "multiplier1 = " << multiplier1 << endl
				 << "screenRatio " << screenRatio << endl
				 << "kleft1 = " << kleft+kleftAdd << endl
				 << "kleft2 " << kleft2+kleft2Add << endl
				 << "kleft3 = " << kleft3+kleft3Add << endl
				 << "kleft4 " << kleft4+kleft4Add << endl
				 << "kleft5 = " << kleft5+kleft5Add << endl
				 << "kleft6 " << kleft6+kleft6Add << endl;
	ofDrawBitmapString(reportStream.str(),ofGetWidth()/2,200);


}

void testApp::drawPointCloud(int left,int  up) {
	int w = 640;
	int h = 480;
	int step = stepNumber;
	for(int y = 0; y < h; y += step) {
		for(int x = 0; x < w; x += step) {
			ofVec3f cur = kinect.getWorldCoordinateFor(x, y);
			ofColor color = kinect.getCalibratedColorAt(x,y);
			int z = cur.z*(ofGetHeight()/2);
			float xRatio=-screenRatio*2*((z+100)*tanTimes)/(camera2Screen/2);
			int newX = xRatio*((320-x));
			if ((cur.z*(ofGetHeight()/2)<1080)&&(cur.z*(ofGetHeight()/2)>50)){
				if (cur.y>0.10){
					ofCircle(newX,z,2);
				}
				ofRect(newX,z,1,1);
			}
		}
	}
}

void testApp::drawPointCloud2(int left,int  up) {
	int w = 640;
	int h = 480;
	int step = stepNumber;
	for(int y = 0; y < h; y += step) {
		for(int x = 0; x < w; x += step) {
			ofVec3f cur = kinect2.getWorldCoordinateFor(x, y);
			ofColor color = kinect2.getCalibratedColorAt(x,y);
			int z = cur.z*(ofGetHeight()/2);
			float xRatio=-screenRatio*2*((z+100)*tanTimes)/(camera2Screen/2);
			int newX = xRatio*((320-x));
			if ((cur.z*(ofGetHeight()/2)<1080)&&(cur.z*(ofGetHeight()/2)>50)){
				if (cur.y>0.10){
					ofCircle(newX,z,2);
				}
				ofRect(newX,z,1,1);
			}
		}
	}
}

void testApp::drawPointCloud3(int left,int  up) {
	int w = 640;
	int h = 480;
	int step = stepNumber;
	for(int y = 0; y < h; y += step) {
		for(int x = 0; x < w; x += step) {
			ofVec3f cur = kinect3.getWorldCoordinateFor(x, y);
			ofColor color = kinect3.getCalibratedColorAt(x,y);
			int z = cur.z*(ofGetHeight()/2);
			float xRatio=-screenRatio*2*((z+100)*tanTimes)/(camera2Screen/2);
			int newX = xRatio*((320-x));
			if ((cur.z*(ofGetHeight()/2)<1080)&&(cur.z*(ofGetHeight()/2)>50)){
				if (cur.y>0.10){
					ofCircle(newX,z,2);
				}
				ofRect(newX,z,1,1);
			}
		}
	}
}

void testApp::drawPointCloud4(int left,int  up) {
	int w = 640;
	int h = 480;
	int step = stepNumber;
	for(int y = 0; y < h; y += step) {
		for(int x = 0; x < w; x += step) {
			ofVec3f cur = kinect4.getWorldCoordinateFor(x, y);
			ofColor color = kinect4.getCalibratedColorAt(x,y);
			int z = cur.z*(ofGetHeight()/2);
			ofSetColor(ofColor::fromHsb(sinf(cur.z)*128+128,255,255));
			float xRatio=-screenRatio*2*((z+100)*tanTimes)/(camera2Screen/2);
			int newX = xRatio*((320-x));
			if ((cur.z*(ofGetHeight()/2)<1080)&&(cur.z*(ofGetHeight()/2)>50)){
				if (cur.y>0.10){
					ofCircle(newX,z,2);
				}
				ofRect(newX,z,1,1);
			}
		}
	}
}

void testApp::drawPointCloud5(int left,int  up) {
	int w = 640;
	int h = 480;
	int step = stepNumber;
	for(int y = 0; y < h; y += step) {
		for(int x = 0; x < w; x += step) {
			ofVec3f cur = kinect5.getWorldCoordinateFor(x, y);
			ofColor color = kinect5.getCalibratedColorAt(x,y);
			int z = cur.z*(ofGetHeight()/2);
			float xRatio=-screenRatio*2*((z+100)*tanTimes)/(camera2Screen/2);
			int newX = xRatio*((320-x));
			if ((cur.z*(ofGetHeight()/2)<1080)&&(cur.z*(ofGetHeight()/2)>50)){
				if (cur.y>0.10){
					ofCircle(newX,z,2);
				}
				ofRect(newX,z,1,1);
			}
		}
	}
}

void testApp::drawPointCloud6(int left,int  up) {
	int w = 640;
	int h = 480;
	int step = stepNumber;
	for(int y = 0; y < h; y += step) {
		for(int x = 0; x < w; x += step) {
			ofVec3f cur = kinect6.getWorldCoordinateFor(x, y);
			ofColor color = kinect6.getCalibratedColorAt(x,y);
			int z = cur.z*(ofGetHeight()/2);
			float xRatio=-screenRatio*2*((z+100)*tanTimes)/(camera2Screen/2);
			int newX = xRatio*((320-x));
			if ((cur.z*(ofGetHeight()/2)<1080)&&(cur.z*(ofGetHeight()/2)>50)){
				if (cur.y>0.10){
					ofCircle(newX,z,2);
				}
				ofRect(newX,z,1,1);
			}
		}
	}
}

//--------------------------------------------------------------
void testApp::exit() {
	kinect.close();
    kinect2.close();
    kinect3.close();
    kinect4.close();
    kinect5.close();
    kinect6.close();
}

//--------------------------------------------------------------
void testApp::keyPressed (int key) {
	switch (key) {
		
		case '>':
			multiplier1= multiplier1 +.05;
		//	if (farThreshold > 255) farThreshold = 255;
			break;

		case '<':
			multiplier1= multiplier1 -0.05;
		//	if (farThreshold < 0) farThreshold = 0;
			break;

		case '+':
			screenRatio= screenRatio +0.05;
			
			break;

		case '-':
			screenRatio= screenRatio -0.05;
			
			break;


		case 'o':
			kinect.open();
			break;

		case 'c':
			kinect.close();
			break;

		case '1':
			kleftAdd= kleftAdd +1;
			break;
		case '!':
			kleftAdd= kleftAdd -1;
			break;

		case '2':
			kleft2Add= kleft2Add +1;
			break;
		case '@':
			kleft2Add= kleft2Add -1;

		case '3':
			kleft3Add= kleft3Add +1;
			break;
		case '#':
			kleft3Add= kleft3Add -1;
			break;

		case '4':
			kleft4Add= kleft4Add +1;
			break;
		case '$':
			kleft4Add= kleft4Add -1;
			break;

		case '5':
			kleft5Add= kleft5Add +1;
			break;
		case '%':
			kleft5Add= kleft5Add -1;
			break;

		case '6':
			kleft6Add= kleft6Add +1;
			break;
		case '^':
			kleft6Add= kleft6Add -1;
			break;

		case 'q':
			kup= kup +1;
			break;
		case 'Q':
			kup= kup -1;
			break;

		case 'w':
			kup2= kup2 +1;
			break;
		case 'W':
			kup2= kup2 -1;

		case 'e':
			kup3= kup3 +1;
			break;
		case 'E':
			kup3= kup3 -1;
			break;

		case 'r':
			kup4= kup4 +1;
			break;
		case 'R':
			kup4= kup4 -1;
			break;

		case 't':
			kup5= kup5 +1;
			break;
		case 'T':
			kup5= kup5 -1;
			break;

		case 'y':
			kup6= kup6 +1;
			break;
		case 'Y':
			kup6= kup6 -1;
			break;
	}
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y) {
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{}


