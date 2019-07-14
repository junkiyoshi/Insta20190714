#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(150, 3);
	this->triangles = ico_sphere.getMesh().getUniqueFaces();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.5);

	vector<glm::vec3> locations;
	vector<glm::vec3> moving_locations;
	for (auto& triangle : this->triangles) {

		auto avg = glm::vec3(triangle.getVertex(0) + triangle.getVertex(1) + triangle.getVertex(2)) / 3;
		auto param = (int)(ofMap(ofNoise(avg.x * 0.004, avg.y * 0.004, avg.z * 0.004), 0, 1, 0, 650) + ofGetFrameNum()) % 650;
		auto y = 0;
		auto alpha = 255.f;
		if (param > 500) {

			y = ofMap(param, 500, 650, 0, 600);
			auto moving_location = avg + glm::vec3(0, y, 0);
			moving_locations.push_back(moving_location);
		} else {

			locations.push_back(avg);
		}
	}

	for (auto& location : locations) {

		ofDrawSphere(location, 2);
		for (auto& other : locations) {

			if (location == other) { continue; }
			float distance = glm::distance(location, other);
			if (distance < 15) {

				ofDrawLine(location, other);
			}
		}
	}

	for (auto& moving_location : moving_locations) {

		ofDrawSphere(moving_location, 2);
		for (auto& other : moving_locations) {

			if (moving_location == other) { continue; }
			float distance = glm::distance(moving_location, other);
			if (distance < 15) {

				ofDrawLine(moving_location, other);
			}
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}