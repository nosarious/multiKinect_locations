#include "testApp.h"
#include "ofAppGlutWindow.h"

int main() {
	ofAppGlutWindow window;
	//ofSetupOpenGL(&window, 1024, 768, OF_WINDOW);
	ofSetupOpenGL(&window, 5760, 1080, OF_FULLSCREEN);
	//ofSetupOpenGL(&window, 5760, 1080,  OF_WINDOW);
	ofRunApp(new testApp());
}

