#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    sound.loadSound("spiderman.wav"); //Loads a sound file (in bin/data/)
    sound.setVolume(0.5); // Sets the song volume
    ofSetBackgroundColor(38, 184, 237); // Sets the Background Color
}

//--------------------------------------------------------------
void ofApp::update(){
    /* The update method is called muliple times per second
    It's in charge of updating variables and the logic of our app */
    ofSoundUpdate(); // Updates all sound players
    visualizer.updateAmplitudes(); // Updates Amplitudes for visualizer
    updateVolume();
    counter ++;
    counterUpdate();
    sound.setLoop(true);

}
 

//--------------------------------------------------------------
void ofApp::draw(){
    /* The update method is called muliple times per second
    It's in charge of drawing all figures and text on screen */
    if(!playing){
        ofSetColor(255);
        ofDrawBitmapString("Press 'p' to play some music!", ofGetWidth()/2 - 50, ofGetHeight()/2);
    }
    vector<float> amplitudes = visualizer.getAmplitudes();
    if(mode == '1'){
        drawMode1(amplitudes);
    }else if(mode == '2'){
        drawMode2(amplitudes);
    }else if(mode == '3'){
        drawMode3(amplitudes);
    }
    if (isRec){
        ofSetColor(255, 0, 0);
        ofFill();
        ofDrawCircle(ofGetWidth() - 40, 40, 15);
        ofDrawBitmapString("Recording", 0, 30);
    }
    if (isRep){
        ofSetColor(0, 0, 0);
        ofFill();
        ofDrawRectangle(ofGetWidth() - 55, 25, 40, 40);
        ofDrawBitmapString("Replaying", 0, 30);
    }
}

void ofApp::drawMode1(vector<float> amplitudes){
        ofFill(); // Drawn Shapes will be filled in with color
        ofSetColor(256); // This resets the color of the "brush" to white
        ofDrawBitmapString("Rectangle Height Visualizer", 0, 15);
        ofSetColor(ofRandom(255), ofRandom(255), ofRandom(255)); 
        ofDrawRectangle(2, ofGetHeight() - 100, 50,  amplitudes[0]);
		
        double width = ofGetWidth()/visualizer.getBands();
//multiplebars
        for (int i =0 ; i<visualizer.getBands();i++){
            ofDrawRectangle(width * i, ofGetHeight()-100,width,amplitudes[i]* 3.14);//
}

        
}
void ofApp::drawMode2(vector<float> amplitudes){
        ofSetLineWidth(5); // Sets the line width
        ofNoFill(); // Only the outline of shapes will be drawn
        ofSetColor(256); // This resets the color of the "brush" to white
        ofDrawBitmapString("Circle Radius Visualizer", 0, 15);
        int bands = amplitudes.size();
        for(int i=0; i< bands; i++){
            ofSetColor((bands - i)*32 %256,18,144); // Color varies between frequencies
            ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, amplitudes[0]/(i +1));
        }
}

void ofApp::drawMode3(vector<float> amplitudes){
    ofFill();
    ofSetColor(256); // This resets the color of the "brush" to white
    ofDrawBitmapString("Rectangle Width Visualizer", 0, 15);
    ofSetColor(ofRandom(255), ofRandom(255), ofRandom(255));
    // YOUR CODE HERE
    double height = ofGetHeight() / visualizer.getBands();
    for (int i = 0; i< visualizer.getBands(); i++){
        ofDrawRectangle(ofGetWidth(),ofGetHeight()* i, amplitudes[i], height);
        }
    }
//--------------------------------------------------------------
vector<string>canciones
{"beat.wav","geesebeat.wav","mora.wav","pigeon-coo.wav,rock-song.wav","spiderman.wav"};



void ofApp::keyPressed(int key){

    // This method is called automatically when any key is pressed
    switch(key){
        case 'p':
            if (isRec)
                record('p');
            if(playing){
                sound.stop();
            }else{
                sound.play();
            }
            playing = !playing;
            break;
        case '-':
            if (isRec)
                record('-');
            sound.setVolume(sound.getVolume() - 0.1);
            break;
        case '=':
        if (isRec)
                record('=');
            sound.setVolume((sound.getVolume() + 0.1));
            break;
        case 'A':
            playing = !playing;
            if (playing){
                sound.setPaused(false);
            }
            else{
                sound.setPaused(true);
            }
            break;
        case '1':
            if (isRec)
                record('1');
            mode = '1';
            break;
        case '2':
            if (isRec)
                record('2');
            mode = '2';
            break;
        case '3':
            if (isRec)
                record('3');
            mode = '3';
            break;
        case 'D':
            if (isRec)
                record('D');
            sound.load(canciones[cancion%canciones.size()]);
            sound.play();
            cancion ++;
            break;
        case 'r':
            if (isRec)
                record('r');
            if (!isRec){
                isRec = true;
                keyRec.clear();
            }
            else {
                isRec = false;
            }
            break;
        case 't':
            if (isRec)
                record('t');
            isRec = false;
            isRep = true;
            break;
    }
}

void ofApp::updateVolume(){
    if (sound.getVolume() >= 1){
                sound.setVolume(1);
            }     
    if (sound.getVolume() <= 0){
                sound.setVolume(0.0);
            }
}

void ofApp::counterUpdate(){
    if (counter == 1200)
        counter = 0;
    if (isRep){
        replay();
    }
    if (pause)  
        return;
}

void ofApp::record(char key){
    keyRec.push_back(key);
}

void ofApp::replay(){
    if (counter % 120 == 0){
        keyPressed(keyRec.at(repObject));
        if (repObject == keyRec.size() && !lastObject){
            keyRec.push_back(' ');
            lastObject = true;
        }
    }
    if (repObject == keyRec.size()){
        endRep();
    }
}

void ofApp::endRep(){
    isRep = false;
    keyRec.clear();
    repObject = 0;
    nextKey = 0;
    keyCheck = false;
    lastObject = false;
}

char ofApp::validCheck(char key){
    if (pause){
        if (key == 'a'){
            return key;
        }
        else return ' ';
    }
    if (isRep && key == keyRec.at(repObject)){
        if (repObject > nextKey){
            keyCheck = false;
        }
        if (!keyCheck){
            keyCheck = true;
            nextKey = repObject;
            return keyRec.at(repObject);
        }
    }
    if (isRep){
        if (key == 't'){
            endRep();
        }
        return ' ';
    }
    else return key;
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

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