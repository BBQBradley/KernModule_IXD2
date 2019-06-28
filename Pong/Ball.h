
#pragma once


#include "ofMain.h"

#define BALL_RADIUS 50

class Ball {
        ofPoint position;
        ofVec2f speed;

    public:
        Ball();
        void reset();

        bool update(int paddleY);

        void draw();
};

