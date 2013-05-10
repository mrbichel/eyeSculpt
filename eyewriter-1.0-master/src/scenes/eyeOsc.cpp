//
//  eyeOsc.cpp
//  temptTracker021
//
//  Created by joseph saavedra on 1/5/12.
//  Copyright 2012 Saavedra. All rights reserved.
//

#include <iostream>
#include "eyeOsc.h"

void eyeOsc::setup(){
    
    ofxXmlSettings XML;
	XML.loadFile("settings/globalSettings.xml"); //in app/bin/data/settings
	HOST = XML.getValue("app:osc:host", "");
    PORT = XML.getValue("app:osc:port", 0);
    
	// open an outgoing connection to HOST:PORT
	sender.setup( HOST, PORT );
    
}

float constrain(float x, float low, float high) {
    return x < low ? low : x > high ? high : x;
}

void eyeOsc::update(float eyeX, float eyeY){
    x = ofMap(eyeX, 0, ofGetWidth(), 0., 1.);
    
    y = ofMap(eyeY, 0, ofGetHeight(), 0., 1.);
    
    x = constrain(x, 0., 1.);
    y = constrain(y, 0., 1.);
    
    ofxOscMessage mX;
	mX.setAddress( "/eye/pos/x" );
	mX.addFloatArg( x );
	sender.sendMessage( mX );
    
    ofxOscMessage mY;
	mY.setAddress( "/eye/pos/y" );
	mY.addFloatArg( y );
	sender.sendMessage( mY );
    
    //need to add message for eye BLINK
}
void eyeOsc::draw(){
    
    ofFill();
    ofSetColor(255,255,255);
    ofDrawBitmapString( "OSC", 20, 40 );
   	string info;
	info = "Sending osc messages to: " + string( HOST ) + " on port: " + ofToString( PORT );
	ofDrawBitmapString( info, 20, 60 );

    ofDrawBitmapString( "/eye/pos/x " + ofToString(x), 20, 100 );
    ofDrawBitmapString( "/eye/pos/y " + ofToString(y), 20, 120 );
    
}

void eyeOsc::dragEvent(ofDragInfo dragInfo){
    
}
void eyeOsc::gotMessage(ofMessage msg){
    
    
}