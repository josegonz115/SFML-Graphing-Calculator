#ifndef GRAPH_CONSTANTS_H
#define GRAPH_CONSTANTS_H

const float SCREEN_WIDTH = 1333.333;//1500
const float SCREEN_HEIGHT = 1000;
const int FRAME_RATE = 60;
const float GRAPH_PANEL = SCREEN_WIDTH*3/4; 
const float SIDE_BAR = SCREEN_WIDTH*1/4;

const float BOX_WIDTH = 0;
const float BOX_HEIGHT = 50;

const float X_ORIGIN = GRAPH_PANEL / 2;
const float Y_ORIGIN = SCREEN_HEIGHT / 2;


const float AXIS_SIZE = 3;
const float LOW = -X_ORIGIN;
const float HIGH = X_ORIGIN;
const float INCREMENT = (HIGH - LOW) / GRAPH_PANEL ;


#endif // GRAPH_CONSTANTS_H