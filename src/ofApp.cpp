#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	bgColor = 255;
	ofBackground(bgColor);
	ofSetFrameRate(60);
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);

	//drawing setup
	fboDrawing.allocate(ofGetWidth(), ofGetHeight());
	fboDrawing.begin();
	ofBackground(bgColor);
	fboDrawing.end();

	gui.setup();
	gui.add(lineColor.setup("line color", 255-bgColor, 0, 255));
	gui.add(lineWeight.setup("line weight", 2, 1, 5));

	//plot setup
	fboPlot.allocate(ofGetWidth(), ofGetHeight());

	ofColor minColor = ofColor(0, 0, 0, 0);
	ofColor maxColor = ofColor(255, 255, 255, 255);
	ofColor initColor1 = ofColor(255, 0, 0, 128);
	ofColor initColor2 = ofColor(0, 0, 255, 128);
	gui.add(color1.setup("color1", initColor1, minColor, maxColor));
	gui.add(color2.setup("color2", initColor2, minColor, maxColor));
	
	gui.add(ratio1.setup("ratio1", 0.5, 0.0, 1.0));
	gui.add(ratio2.setup("ratio2", 0.5, 0.0, 1.0));
	pratio1 = ratio1;
	pratio2 = ratio2;
	gui.add(plotNum.setup("plot num", 10000, 1, 20000));
	gui.add(plotR.setup("plot radius", 1.0, 1.0, 5.0));
	gui.add(plotEntropy.setup("entropy", 10.0, 0.0, 20.0));

	//other
	drawing = true;
	isReleasedKey = true;
}

//--------------------------------------------------------------
void ofApp::update(){
	if (ratio1 != pratio1) ratio2 = 1.0 - ratio1;
	if (ratio2 != pratio2) ratio1 = 1.0 - ratio2;
	pratio1 = ratio1;
	pratio2 = ratio2;
}

//--------------------------------------------------------------
void ofApp::draw(){
	//fbo draw
	if (drawing) {

		fboDrawing.draw(0, 0);
		//info
		gui.draw();
		string str = "'p' : plots dots.\n'c' : clear drawing.";
		ofSetColor(255 - bgColor);
		ofDrawBitmapString(str, 10, ofGetHeight() - 20);
		ofSetColor(bgColor);
	}
	else fboPlot.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (isReleasedKey) {
		if (key == 'c') {
			fboDrawing.begin();
			ofBackground(bgColor);
			fboDrawing.end();
		}

		//plot
		if (key == 'p') {
			if (drawing) {
				pixels.clear();
				fboDrawing.readToPixels(pixels);
				
				//get pixels pos
				pixelsPos.clear();
				for (int y = 0; y < pixels.getHeight(); y++) {
					for (int x = 0; x < pixels.getWidth(); x++) {
						ofColor c = pixels.getColor(x, y);
						unsigned gray = (2.0*c.r + 4.0*c.g + c.b) / 7.0;
						if (gray != bgColor) pixelsPos.emplace_back(ofVec2f(x, y));
					}
				}

				//plot dots
				fboPlot.begin();
				ofBackground(bgColor);
				int plotNum1 = plotNum*ratio1;
				int plotNum2 = plotNum - plotNum1;
				int count1 = 0;
				int count2 = 0;
				for (int i = 0; i < plotNum; i++) {
					//pos
					ofVec2f pos;
					if (!pixelsPos.empty()) {
						int num = ofRandom(pixelsPos.size());
						pos = pixelsPos[num];
						if (plotEntropy != 0) pos += ofVec2f(ofRandom(-plotEntropy, plotEntropy), ofRandom(-plotEntropy, plotEntropy));
					}
					//color
					if (count1 >= plotNum1) {
						ofSetColor(color2);
						count2++;
					}
					else if (count2 >= plotNum2) {
						ofSetColor(color1);
						count1++;
					}
					else {
						if ((int)ofRandom(2.0) == 0) {
							ofSetColor(color1);
							count1++;
						}
						else {
							ofSetColor(color2);
							count2++;
						}
					}
					//plot
					ofDrawCircle(pos, plotR);
				}
				//info
				ofSetColor(255-bgColor);
				float r1 = ratio1;
				float r2 = ratio2;
				string str = "ratio1:ratio2 = " + ofToString(r1) + ":" + ofToString(r2);
				ofDrawBitmapString(str, 10, ofGetHeight() - 20);

				fboPlot.end();				
				drawing = false;
			}
			else {
				drawing = true;
			}
		}//plot end
		isReleasedKey = false;
	}//isReleasedKey end
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	isReleasedKey = true;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	px = x; py = y;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	fboDrawing.begin();
	ofSetColor(lineColor);
	//ofSetLineWidth(lineWeight);
	glLineWidth(lineWeight);
	ofDrawLine(px, py, x, y);
	fboDrawing.end();
	px = x; py = y;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	fboDrawing.begin();
	ofSetColor(lineColor);
	ofDrawCircle(x, y, lineWeight/2.0);
	fboDrawing.end();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
