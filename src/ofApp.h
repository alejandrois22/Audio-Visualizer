#pragma once

#include "ofMain.h"
#include "AudioVisualizer.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

		void drawMode1(vector<float> amplitudes);
		void drawMode2(vector<float> amplitudes);
		void drawMode3(vector<float> amplitudes);
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void updateVolume();
		void counterUpdate();
		void replay();
		void endRep();
		void throwNotification(int, int);
		void record(char);
		char validCheck(char);


	private:
		ofSoundPlayer sound;
		AudioVisualizer visualizer;

		vector<string>canciones
		{"beat.wav","geesebeat.wav","mora.wav","pigeon-coo.wav,rock-song.wav","spiderman.wav"};
		int cancion = 0;//counter
		//

		char mode = '1';
		vector<char> keyRec;
		int counter;
		bool keyCheck = false;
		unsigned int nextKey = 0;
		bool isRep = false;
		unsigned int repObject = 0;
		bool lastObject = false;
		bool isRec = false;
		int notification;
		bool playing = false;
		bool pause = false;
		bool cancel = false;

};
