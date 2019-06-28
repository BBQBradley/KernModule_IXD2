#include "Ball.h"
#include "ofApp.h"

Ball::Ball() {
    position = ofPoint(ofGetWidth() / 4, ofGetHeight() / 2);
}

void Ball::reset() {
    position = ofPoint(ofGetWidth() / 4, ofGetHeight() / 2);
    speed = ofVec2f(ofRandom(1, 3) * 3 + 2, ofRandom(-1, 1) * 5 + 2);
}

bool Ball::update(int paddleY) {
    position += speed;

    if (position.y > ofGetHeight() - BALL_RADIUS || position.y < BALL_RADIUS) {
        speed.y = -speed.y;
    }

    if (position.x > ofGetWidth() - BALL_RADIUS - ofApp::PADDLE_WIDTH) {
        if (position.y >= paddleY && position.y <= paddleY + ofApp::PADDLE_HEIGHT) {
            float diff = (position.y - paddleY - ofApp::PADDLE_HEIGHT / 2) / 30;
            speed.x = -speed.x;
            speed.y += diff;
        } else {
            reset();
            return true;
        }

    } else if (position.x < BALL_RADIUS) {
        speed.x = -speed.x;
    }

    return false;
}

void Ball::draw() {
    ofSetColor(ofColor::green);
    ofDrawCircle(position, BALL_RADIUS);
}
