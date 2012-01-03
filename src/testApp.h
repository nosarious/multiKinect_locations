#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "Particle.h"

// uncomment this to read from two kinects simultaneously
#define USE_TWO_KINECTS

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

		void activatePoint(int xValue, int yValue);

		/// start/stop recording and playback,
		/// make sure you don't record and playback simultaneously
		/// using the same file!!!
		void startRecording();
		void stopRecording();
		void startPlayback();
		void stopPlayback();


		ofxKinect 			kinect;
		ofxKinectRecorder 	kinectRecorder;
		ofxKinectPlayer 	kinectPlayer;

		/// used to switch between the live kinect and the recording player
		ofxBase3DVideo* 	kinectSource;

		ofxCvColorImage		colorImg;

		ofxCvGrayscaleImage grayImage;			// grayscale depth image
		ofxCvGrayscaleImage grayThreshNear;		// the near thresholded image
		ofxCvGrayscaleImage grayThreshFar;		// the far thresholded image

		ofxCvContourFinder 	contourFinder;

		bool				bThreshWithOpenCV;
		bool				bDrawPointCloud;

		int 				nearThreshold;
		int					farThreshold;

		int					angle;

		int 				pointCloudRotationY;

		bool 				bRecord;
		bool 				bPlayback;

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
		       
        ofImage image ;                 //image to load
        int sampling ;                  //pixels to skip
        vector<Particle> particles ;    //vector to store pixels
        int numParticles ;          //Number of particles 
       
        //Spring and Sink Factors
        bool springEnabled ;        //toggle whether particles return to their origin
        float forceRadius ;             //radius of repellent/attraction force
        float friction ;                //damping to slow the particles down
        float springFactor ;          //how much the particle "springs" back to origin
        int cursorMode ;            
    
		bool bDrawSquares;

		int delayedStart;
	int wRatio;
	int hRatio;
};
