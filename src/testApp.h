#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"

class testApp : public ofBaseApp {
	public:

		void setup();
		void update();
		void draw();
		void exit();

		void drawPointCloud(int left,int  up);
		void drawPointCloud2(int left,int  up);
		void drawPointCloud3(int left,int  up);
		void drawPointCloud4(int left,int  up);
		void drawPointCloud5(int left,int  up);
		void drawPointCloud6(int left,int  up);

		
		void keyPressed  (int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);



		ofxKinect 			kinect;
		ofxKinectRecorder 	kinectRecorder;
		ofxKinectPlayer 	kinectPlayer;


		int					angle;


        // second kinect for testing
        ofxKinect 			kinect2;

		
        // third kinect for testing
        ofxKinect 			kinect3;

        // second kinect for testing
        ofxKinect 			kinect4;

		
        // third kinect for testing
        ofxKinect 			kinect5;
		
        // third kinect for testing
        ofxKinect 			kinect6;

		int kleft,kleft2,kleft3,kleft4,kleft5,kleft6;
		int kleftAdd,kleft2Add,kleft3Add,kleft4Add,kleft5Add,kleft6Add;
		int kup,kup1,kup2,kup3,kup4,kup5,kup6;

		int cameraWidth;
		float cameraSpace,screenRatio,kinectRatio,multiplier1,camera2Screen;
		
		float tanTimes;

		bool calculateWidth;

/* variables for particle system */
		       
            
    
	int wRatio;
	int hRatio;
	int stepNumber;
};
