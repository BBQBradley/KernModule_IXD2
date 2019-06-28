#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "Ball.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void mousePressed(int x, int y, int button);
 
		ofVideoGrabber grabber;

		ofxCvColorImage rgbImage;
		ofxCvColorImage hsvImage;
		//ofxCvColorImage hueImage;

		ofxCvGrayscaleImage hueImage;
		ofxCvGrayscaleImage satImage;
		ofxCvGrayscaleImage valImage;

		ofxCvGrayscaleImage filtered;

		int selectedHue;
		int yPosBlob;

		ofxCvContourFinder contours;

		bool showHSVComponents = true;
		bool showFilter = true;
		bool showContours = true;
		bool showVideo = true;

		// Eye Tracker
		ofxCvHaarFinder haarFinder;
		ofImage image;


		//pong

		static const int PADDLE_WIDTH = 20;
		static const int PADDLE_HEIGHT = 250;

	private:
		Ball ball;
		int missedCount;
		int paddleY;

		
};
