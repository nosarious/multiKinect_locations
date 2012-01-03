#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup() {

	/* setup for the particle system */
    //load our image inside bin/data
    image.loadImage ( "Stairwell2.jpg" ) ; 
    //if the app performs slowly raise this number
    sampling = 60 ; 
	bDrawSquares = true;
    
    //Retrieve the pixels from the loaded image
    unsigned char * pixels = image.getPixels() ;
    //store width and height for optimization and clarity
 /*   int w = image.width ; 
    int h = image.height ; 
	*/
	int w = 5760;
	int h = 1080;

	delayedStart = 0; //add a jitter every ten updates or so
	wRatio = ofGetWidth()/w;
	hRatio = ofGetHeight()/h;
    
    //offsets to center the particles on screen
/*    int xOffset = (ofGetWidth() - w ) /2 ; 
    int yOffset = (ofGetHeight() - h ) /2 ;
    */
	int xOffset = 0;
	int yOffset = 0;
    //Loop through all the rows
    for ( int x = 0 ; x < w ; x+=sampling ) 
    {
        //Loop through all the columns
        for ( int y = 0 ; y < h ; y+=sampling ) 
        {
            //Pixels are stored as unsigned char ( 0 <-> 255 ) as RGB
            //If our image had transparency it would be 4 for RGBA
            int index = ( y * w + x ) * 3 ; 
            ofColor color ; 
            color.r = pixels[index] ;       //red pixel
            color.g = pixels[index+1] ;     //blue pixel
            color.b = pixels[index+2] ;     //green pixel
            particles.push_back( Particle ( ofPoint ( x + xOffset , y + yOffset ) , color, ofPoint(0,0,0) ) ) ;  
        }
    }
    
    ofSetFrameRate( 10 ) ; 
    numParticles = ( image.width * image.height ) / sampling ; 
    
    //Set spring and sink values
    cursorMode = 0 ; 
    forceRadius = sampling*4 ; 
    friction = 0.015 ; 
    springFactor = 0.12 ; 
    springEnabled = true ; 


	/* setup for kinect stuff */
    ofSetLogLevel(OF_LOG_VERBOSE);

	
	kinect.close();
    kinect2.close();
    kinect3.close();
    kinect4.close();
    kinect5.close();
    kinect6.close();

	kinect.init(false, false);
	//kinect.init(true);  // shows infrared instead of RGB video image
	//kinect.init(false, false);  // disable video image (faster fps)
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
	
	// start with the live kinect source
	kinectSource = &kinect;

	colorImg.allocate(kinect.width, kinect.height);
	grayImage.allocate(kinect.width, kinect.height);
	grayThreshNear.allocate(kinect.width, kinect.height);
	grayThreshFar.allocate(kinect.width, kinect.height);

	nearThreshold = 230;
	farThreshold  = 70;
	bThreshWithOpenCV = true;

	ofSetFrameRate(30);

	bRecord = false;
	bPlayback = false;

	// zero the tilt on startup
	angle = 0;
//	kinect.setCameraTiltAngle(angle);

	// start from the front
	pointCloudRotationY = 180;
	bDrawPointCloud = true;

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
	
	activatePoint(mouseX , mouseY);

	delayedStart = delayedStart + 1;
	if (delayedStart >10){
		delayedStart = 0;
		activatePoint(ofRandom(ofGetWidth()),ofRandom(ofGetHeight()));
	}

	ofPoint diff ;          //Difference between particle and mouse
    float dist ;            //distance from particle to mouse ( as the crow flies ) 
    float ratio ;           //Ratio of how strong the effect is = 1 + (-dist/maxDistance) ;
   
    //Create an iterator to cycle through the vector
    std::vector<Particle>::iterator p ; 
    for ( p = particles.begin() ; p != particles.end() ; p++ ) 
    {
        ratio = 1.0f ; 
        p->velocity *= friction ; 
        //reset acceleration every frame
        p->acceleration = ofPoint() ; 
        
        if ( springEnabled ) 
        {
            //Move back to the original position
            p->acceleration.x += springFactor * (p->spawnPoint.x - p->position.x);
            p->acceleration.y += springFactor * (p->spawnPoint.y - p->position.y) ;
        }
        
        p->velocity += p->acceleration * ratio ; 
        p->position += p->velocity ; 
		p->angle.z += p->velocity.y;
		p->angle.x += p->velocity.x;
		p->angle.y += p->velocity.y;
    }

/* update for kinect system */
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
	
	image.draw(ofGetWidth()/2,ofGetHeight()/2,ofGetWidth(),ofGetHeight());
/* drawing the particle system */
if (bDrawSquares){
	ofSetRectMode(OF_RECTMODE_CENTER);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,ofGetWidth(),ofGetHeight(),0,-200,200);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0,200,1200,0,0,0,0,1,0);
		// enable blending
	glEnable(GL_BLEND);
	ofTexture tex = image.getTextureReference();
	tex.bind();
	std::vector<Particle>::iterator p;
	for (p = particles.begin(); p!=particles.end(); p++)
	{
	//	glColor3ub((unsigned char)p->color.r,(unsigned char)p->color.g,(unsigned char)p->color.b);
		ofSetColor(255,255,255,25);
		ofPushMatrix();
		glLoadIdentity();
		ofPushStyle();
		
		if (bDrawSquares){
		//	ofTranslate(p->position.x,p->position.y);
		//	ofRotateX(p->angles.x);
		//	ofRotateY(p->angles.y);
			glTranslatef(p->position.x,p->position.y,0);
			ofRotateZ(p->angle.z);
			ofRotateY(p->angle.y);
			ofRotateX(p->angle.x);
		//	ofSetColor(50,50,50,100);
		//	ofRect(0,0,0,sampling+10,sampling+10);
			glScalef(sampling*1.5,sampling*1.5,1);
			glBegin(GL_QUADS);
				glTexCoord2f(p->position.x,p->position.y);
				glVertex3f(0,0,0);
				glTexCoord2f(p->position.x+sampling,p->position.y);
				glVertex3f(1,0,0);
				glTexCoord2f(p->position.x+sampling,p->position.y+sampling);
				glVertex3f(1,1,0);
				glTexCoord2f(p->position.x,p->position.y+sampling);
				glVertex3f(0,1,0);

			glEnd();
		//	ofRect(1,1,sampling,sampling);
		}
		ofPopStyle();
	ofPopMatrix();
	}

		// enable blending
	glEnable(GL_BLEND);
}

/* drawing the kinect system */
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

void testApp::activatePoint(int xValue, int yValue){
	
	ofPoint diff ;          //Difference between particle and mouse
    float dist ;            //distance from particle to mouse ( as the crow flies ) 
    float ratio ;           //Ratio of how strong the effect is = 1 + (-dist/maxDistance) ;
    const ofPoint mousePosition = ofPoint( xValue , yValue ) ; //Allocate and retrieve mouse values once.

    
    //Create an iterator to cycle through the vector
    std::vector<Particle>::iterator p ; 
    for ( p = particles.begin() ; p != particles.end() ; p++ ) 
    {
        ratio = 1.0f ; 
        p->velocity *= friction ; 
        //reset acceleration every frame
        p->acceleration = ofPoint() ; 
        diff = mousePosition - p->position ;  
        dist = ofDist( 0 , 0 , diff.x , diff.y/3 ) ;
        //If within the zone of interaction
        if ( dist < forceRadius )  
        {
            ratio = -1 + dist / forceRadius ; 
            //Repulsion
            if ( cursorMode == 0 ) 
                p->acceleration -= ( diff * ratio) ;
            //Attraction
            else
                p->acceleration += ( diff * ratio ) ; 
        }
		/*
        if ( springEnabled ) 
        {
            //Move back to the original position
            p->acceleration.x += springFactor * (p->spawnPoint.x - p->position.x);
            p->acceleration.y += springFactor * (p->spawnPoint.y - p->position.y) ;
        }
        */
        p->velocity += p->acceleration * ratio ; 
        p->position += p->velocity ; 
		p->angle.z += p->velocity.y;
		p->angle.x += p->velocity.x;
		p->angle.y += p->velocity.y;
		
    }
}

void testApp::drawPointCloud(int left,int  up) {
	int w = 640;
	int h = 480;
	int step = 60;
	for(int y = 0; y < h; y += step) {
		for(int x = 0; x < w; x += step) {
			ofVec3f cur = kinect.getWorldCoordinateFor(x, y);
			ofColor color = kinect.getCalibratedColorAt(x,y);
		//	glColor3ub((unsigned char)color.r,(unsigned char)color.g,(unsigned char)color.b);
			ofSetColor(ofColor::fromHsb(sinf(cur.x)*128+128,255,255));
		//	glVertex3f(cur.x, cur.y, cur.z);
		//	ofRect(480-x,cur.y,10,10);
		//	ofRect(screenRatio-x*kinectRatio,cur.z*(ofGetHeight()/2),10,10);
		//	ofRect((cameraWidth-x)*screenRatio-sinf(cur.x),cur.z*(ofGetHeight()/2),10,10);
			int z = cur.z*(ofGetHeight()/2);
			float xRatio=-screenRatio*2*((z+100)*tanTimes)/(camera2Screen/2);
			int newX = xRatio*((320-x));
			if ((cur.z*(ofGetHeight()/2)<1080)&&(cur.z*(ofGetHeight()/2)>50)){
				if (cur.y>0.20){
					ofCircle(newX,z,20);
				}
				ofRect(newX,z,10,10);
				
					activatePoint(newX+left,z+up);
			}
		}
	}
	glEnd();
}

void testApp::drawPointCloud2(int left,int  up) {
	int w = 640;
	int h = 480;
	//glBegin(GL_POINTS);
	int step = 60;
	for(int y = 0; y < h; y += step) {
		for(int x = 0; x < w; x += step) {
			ofVec3f cur = kinect2.getWorldCoordinateFor(x, y);
			ofColor color = kinect2.getCalibratedColorAt(x,y);
		//	glColor3ub((unsigned char)color.r,(unsigned char)color.g,(unsigned char)color.b);
			ofSetColor(ofColor::fromHsb(sinf(cur.x)*128+128,255,255));
		//	glVertex3f(cur.x, cur.y, cur.z);
		//	ofRect(480-x,cur.y,10,10);
		//	ofRect(screenRatio-x*kinectRatio,cur.z*(ofGetHeight()/2),10,10);
		//	ofRect((cameraWidth-x)*screenRatio-sinf(cur.x),cur.z*(ofGetHeight()/2),10,10);
			int z = cur.z*(ofGetHeight()/2);
			float xRatio=-screenRatio*2*((z+100)*tanTimes)/(camera2Screen/2);
			int newX = xRatio*((320-x));
			if ((cur.z*(ofGetHeight()/2)<1080)&&(cur.z*(ofGetHeight()/2)>50)){
				if (cur.y>0.20){
					ofCircle(newX,z,20);
				}
				ofRect(newX,z,10,10);
					activatePoint(newX+left,z+up);
			}
		}
	}
	glEnd();
}

void testApp::drawPointCloud3(int left,int  up) {
	int w = 640;
	int h = 480;
	//glBegin(GL_POINTS);
	int step = 60;
	for(int y = 0; y < h; y += step) {
		for(int x = 0; x < w; x += step) {
			ofVec3f cur = kinect3.getWorldCoordinateFor(x, y);
			ofColor color = kinect3.getCalibratedColorAt(x,y);
		//	glColor3ub((unsigned char)color.r,(unsigned char)color.g,(unsigned char)color.b);
			ofSetColor(ofColor::fromHsb(sinf(cur.x)*128+128,255,255));
		//	glVertex3f(cur.x, cur.y, cur.z);
		//	ofRect(480-x,cur.y,10,10);
		//	ofRect(screenRatio-x*kinectRatio,cur.z*(ofGetHeight()/2),10,10);
		//	ofRect((cameraWidth-x)*screenRatio-sinf(cur.x),cur.z*(ofGetHeight()/2),10,10);
			int z = cur.z*(ofGetHeight()/2);
			float xRatio=-screenRatio*2*((z+100)*tanTimes)/(camera2Screen/2);
			int newX = xRatio*((320-x));
			if ((cur.z*(ofGetHeight()/2)<1080)&&(cur.z*(ofGetHeight()/2)>50)){
				if (cur.y>0.20){
					ofCircle(newX,z,20);
				}
				ofRect(newX,z,10,10);
					activatePoint(newX+left,z+up);
			}
		}
	}
	glEnd();
}

void testApp::drawPointCloud4(int left,int  up) {
	int w = 640;
	int h = 480;
	//glBegin(GL_POINTS);
	int step = 60;
	for(int y = 0; y < h; y += step) {
		for(int x = 0; x < w; x += step) {
			ofVec3f cur = kinect4.getWorldCoordinateFor(x, y);
			ofColor color = kinect4.getCalibratedColorAt(x,y);
			glColor3ub((unsigned char)color.r,(unsigned char)color.g,(unsigned char)color.b);
			ofSetColor(ofColor::fromHsb(sinf(cur.x)*128+128,255,255));
			
		//	ofRect(480-x,cur.y,10,10);
		//	ofRect(screenRatio-x*kinectRatio,cur.z*(ofGetHeight()/2),10,10);
		//	ofRect((cameraWidth-x)*screenRatio-sinf(cur.x),cur.z*(ofGetHeight()/2),10,10);
			int z = cur.z*(ofGetHeight()/2);
			float xRatio=-screenRatio*2*((z+100)*tanTimes)/(camera2Screen/2);
			int newX = xRatio*((320-x));
			if ((cur.z*(ofGetHeight()/2)<1080)&&(cur.z*(ofGetHeight()/2)>50)){
				if (cur.y>0.20){
					ofCircle(newX,z,20);
				}
				ofRect(newX,z,10,10);
					activatePoint(newX+left,z+up);
			}
		}
	}
	glEnd();
}

void testApp::drawPointCloud5(int left,int  up) {
	int w = 640;
	int h = 480;
	int step = 60;
	for(int y = 0; y < h; y += step) {
		for(int x = 0; x < w; x += step) {
			ofVec3f cur = kinect5.getWorldCoordinateFor(x, y);
			ofColor color = kinect5.getCalibratedColorAt(x,y);
		//	glColor3ub((unsigned char)color.r,(unsigned char)color.g,(unsigned char)color.b);
			ofSetColor(ofColor::fromHsb(sinf(cur.x)*128+128,255,255));
		//	glVertex3f(cur.x, cur.y, cur.z);
		//	ofRect(480-x,cur.y,10,10);
		//	ofRect(screenRatio-x*kinectRatio,cur.z*(ofGetHeight()/2),10,10);
		//	ofRect((cameraWidth-x)*screenRatio-sinf(cur.x),cur.z*(ofGetHeight()/2),10,10);
			int z = cur.z*(ofGetHeight()/2);
			float xRatio=-screenRatio*2*((z+100)*tanTimes)/(camera2Screen/2);
			int newX = xRatio*((320-x));
			if ((cur.z*(ofGetHeight()/2)<1080)&&(cur.z*(ofGetHeight()/2)>50)){
				if (cur.y>0.20){
					ofCircle(newX,z,20);
				}
				ofRect(newX,z,10,10);
					activatePoint(newX+left,z+up);
			}
		}
	}
	glEnd();
}

void testApp::drawPointCloud6(int left,int  up) {
	int w = 640;
	int h = 480;
	int step = 60;
	for(int y = 0; y < h; y += step) {
		for(int x = 0; x < w; x += step) {
			ofVec3f cur = kinect6.getWorldCoordinateFor(x, y);
			ofColor color = kinect6.getCalibratedColorAt(x,y);
		//	glColor3ub((unsigned char)color.r,(unsigned char)color.g,(unsigned char)color.b);
			ofSetColor(ofColor::fromHsb(sinf(cur.x)*128+128,255,255));
		//	glVertex3f(cur.x, cur.y, cur.z);
		//	ofRect(480-x,cur.y,10,10);
		//	ofRect(screenRatio-x*kinectRatio,cur.z*(ofGetHeight()/2),10,10);
		//	ofRect((cameraWidth-x)*screenRatio-sinf(cur.x),cur.z*(ofGetHeight()/2),10,10);
			int z = cur.z*(ofGetHeight()/2);
			float xRatio=-screenRatio*2*((z+100)*tanTimes)/(camera2Screen/2);
			int newX = xRatio*((320-x));
			if ((cur.z*(ofGetHeight()/2)<1080)&&(cur.z*(ofGetHeight()/2)>50)){
				if (cur.y>0.20){
					ofCircle(newX,z,20);
				}
	
				ofRect(newX,z,10,10);
					activatePoint(newX+left,z+up);
				/*
				ofSetColor(255, 255, 255);
					stringstream reportStream;
					reportStream << "xratio " << xRatio << endl;
					ofDrawBitmapString(reportStream.str(),newX,z);
					*/
			}
		}
	}
	glEnd();
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
		case ' ':
			bThreshWithOpenCV = !bThreshWithOpenCV;
		break;

		case'p':
			bDrawPointCloud = !bDrawPointCloud;
			break;

		case'b':
			bDrawSquares = !bDrawSquares;
			break;

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
			if (nearThreshold > 255) nearThreshold = 255;
			break;

		case '-':
			screenRatio= screenRatio -0.05;
			if (nearThreshold < 0) nearThreshold = 0;
			break;


		case 'o':
		//	kinect.setCameraTiltAngle(angle);	// go back to prev tilt
			kinect.open();
			break;

		case 'c':
		//	kinect.setCameraTiltAngle(0);		// zero the tilt
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
/*
		case 'r':
			bRecord = !bRecord;
			if(bRecord) {
				startRecording();
			} else {
				stopRecording();
			}
			break;

		case 'q':
			bPlayback = !bPlayback;
			if(bPlayback) {
				startPlayback();
			} else {
				stopPlayback();
			}
			break;

		case OF_KEY_UP:
			angle++;
			if(angle>30) angle=30;
			kinect.setCameraTiltAngle(angle);
			break;

		case OF_KEY_DOWN:
			angle--;
			if(angle<-30) angle=-30;
			kinect.setCameraTiltAngle(angle);
			break;
			*/
	}
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y) {
	pointCloudRotationY = x;
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

//--------------------------------------------------------------
void testApp::startRecording() {

	// stop playback if running
	stopPlayback();

	kinectRecorder.init(ofToDataPath("recording.dat"));
	bRecord = true;
}

//--------------------------------------------------------------
void testApp::stopRecording() {
	kinectRecorder.close();
	bRecord = false;
}

//--------------------------------------------------------------
void testApp::startPlayback() {

	stopRecording();
	kinect.close();

	// set record file and source
	kinectPlayer.setup(ofToDataPath("recording.dat"), true);
	kinectPlayer.loop();
	kinectSource = &kinectPlayer;
	bPlayback = true;
}

//--------------------------------------------------------------
void testApp::stopPlayback() {
	kinectPlayer.close();
	kinect.open();
	kinectSource = &kinect;
	bPlayback = false;
}
