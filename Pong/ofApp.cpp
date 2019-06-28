#include "ofApp.h"
#include "Ball.cpp"

#define GRABBER_WIDTH 640
#define GRABBER_HEIGHT 480

#define HUE_MARGIN 5

//--------------------------------------------------------------
void ofApp::setup()
{
	grabber.setup(GRABBER_WIDTH, GRABBER_HEIGHT);

	// Color Tracking

	rgbImage.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
	hsvImage.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
	hueImage.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
	satImage.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
	valImage.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
	filtered.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);

	/* //Eye Tracking
	haarFinder.setup("haarcascade_eyes.xml");

	image.load("eyes.png");
	*/

	ofSetBackgroundColor(ofColor::black);
	ofSetCircleResolution(30);

}

void ofApp::update()
{
	//paddleY = MIN(MAX(mouseY - PADDLE_HEIGHT / 2, 0), ofGetHeight() - PADDLE_HEIGHT);

	

	//paddleY = MIN(MAX(yPosBlob - PADDLE_HEIGHT / 2, 0), ofGetHeight() - PADDLE_HEIGHT);

	paddleY = MIN(MAX(yPosBlob, 0), ofGetHeight() - PADDLE_HEIGHT);

	bool wasReset = ball.update(paddleY);
	if (wasReset) 
	{
		missedCount++;
	}

	grabber.update();

	if (grabber.isFrameNew()) 
	{
		rgbImage.setFromPixels(grabber.getPixels());
		rgbImage.mirror(false, true);

		hsvImage = rgbImage;
		hsvImage.convertRgbToHsv();
		hsvImage.convertToGrayscalePlanarImages(hueImage, satImage, valImage);

		for (int i = 0; i < GRABBER_HEIGHT * GRABBER_WIDTH; i++)
		{
			if (ofInRange(hueImage.getPixels()[i], selectedHue - HUE_MARGIN, selectedHue + HUE_MARGIN))
			{
				filtered.getPixels()[i] = 255;
			}
			else
			{
				filtered.getPixels()[i] = 0;
			}
		}
		filtered.flagImageChanged();

		contours.findContours(filtered, 50, GRABBER_WIDTH * GRABBER_HEIGHT/2, 1, false);
	}

	

	/* //Eye Tracking
	if (grabber.isFrameNew())
	{
		haarFinder.findHaarObjects(grabber.getPixels(), 75, 75);
	}
	*/

}

void ofApp::draw()
{


	if (showVideo) {
		rgbImage.draw(0, 0, ofGetWidth(), ofGetHeight());
	}

	
	if (showHSVComponents) {
		hsvImage.draw(0, 0);
		hueImage.draw(0, 240);
		satImage.draw(320, 240);
		valImage.draw(640, 240);
	}
	

	if (showFilter) {
		filtered.draw(0, 480);
	}

	if (showContours) {
		contours.draw(0, 0, ofGetWidth(), ofGetHeight());
	}

	ofSetColor(ofColor::blue, 100);
	ofFill();
	for (int i = 0; i < contours.blobs.size(); i++) 
	{
		ofDrawCircle(contours.blobs[i].centroid.x * ofGetWidth() / GRABBER_WIDTH,
			contours.blobs[i].centroid.y * ofGetHeight() / GRABBER_HEIGHT,
			20);
	}
	ofSetColor(ofColor::white);

	//yPosBlob = contours.y; // heb een var nodig met de y pos van selectedhue

	//yPosBlob = contours.blobs.getPixels()[y * GRABBER_WIDTH];
	

	rgbImage.draw(0, 0, ofGetWidth(), ofGetHeight());

	//hsvImage.draw(0, 0);

	//hueImage.draw(0, GRABBER_HEIGHT);
	//valImage.draw(GRABBER_WIDTH, GRABBER_HEIGHT);
	//satImage.draw(GRABBER_WIDTH * 2, GRABBER_HEIGHT);
	//filtered.draw(0, GRABBER_HEIGHT);
	ofFill();
	
	contours.draw(0, 0, ofGetWidth(), ofGetHeight());
	
	ofSetColor(ofColor::blue, 100);
	for (int i = 0; i < contours.blobs.size(); i++) 
	{
		ofDrawCircle(contours.blobs[i].centroid.x * ofGetWidth() / GRABBER_WIDTH,
			contours.blobs[i].centroid.y * ofGetHeight() / GRABBER_HEIGHT,
			20);

		yPosBlob = contours.blobs[i].centroid.y;
	}


	
	

	

	/* //Eye Tracking
	ofSetColor(ofColor::white);
	grabber.draw(0,0);

	ofNoFill();
	ofSetColor(ofColor::green);

	for (int i = 0; i < haarFinder.blobs.size(); i++)
	{
		ofRectangle boundingBox = haarFinder.blobs[i].boundingRect;
		ofDrawRectangle(boundingBox);

		//image.draw(boundingBox);
	}
	*/ //Eye Tracking

	ball.draw();
	ofDrawRectangle(ofGetWidth() - PADDLE_WIDTH,
		paddleY,
		PADDLE_WIDTH, PADDLE_HEIGHT);

	ofDrawBitmapString("Missed: " + ofToString(missedCount), 10, 10);
}

void ofApp::keyPressed(int key)
{
	if (key == ' ') {
		ball.reset();
	}
	if (key == 'h') {
		showHSVComponents = !showHSVComponents;
	}
	else if (key == 'v') {
		showVideo = !showVideo;
	}
	else if (key == 'f') {
		showFilter = !showFilter;
	}
	else if (key == 'c') {
		showContours = !showContours;
	}
}

void ofApp::mousePressed(int x, int y, int button)
{
	selectedHue = hueImage.getPixels()[y * GRABBER_WIDTH + x];
	//selectedHue = hueImage.getPixels()[y];
	cout << "Selected" << selectedHue << endl;
}

