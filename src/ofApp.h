#pragma once

#include "ofMain.h"
#include "ofxGui.h"

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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		//drawing
		ofxPanel gui;
		ofxIntSlider lineColor;
		ofxIntSlider lineWeight;
		ofFbo fboDrawing;
		int px, py;

		//plot
		ofFbo fboPlot;
		ofPixels pixels;
		vector<ofVec2f> pixelsPos;
		ofxColorSlider color1, color2;
		ofxFloatSlider ratio1,ratio2;
		float pratio1, pratio2;
		ofxIntSlider plotNum;
		ofxFloatSlider plotR;
		ofxFloatSlider plotEntropy;

		//other
		bool drawing;
		bool isReleasedKey;
		unsigned bgColor;
};
