#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	for (int i = 0; i < 3; i++) {

		ofMesh mesh;
		this->mesh_list.push_back(mesh);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	int len = 580;
	int span = 1;
	ofColor color;

	int index = 0;
	for (auto& mesh : this->mesh_list) {

		mesh.clear();
		auto seed = ofRandom(1000);
		for (int x = len * -0.5; x < len * 0.5; x += span) {

			for (int y = len * -0.5; y < len * 0.5; y += span) {

				auto noise_value = ofMap(ofNoise(seed, x * 0.003, y * 0.003, ofGetFrameNum() * 0.01), 0, 1, 0, 10);
				if ((int)noise_value % 2 == 0) {

					continue;
				}

				mesh.addVertex(glm::vec3(x, y, 0));
				mesh.addVertex(glm::vec3(x + span, y, 0));
				mesh.addVertex(glm::vec3(x + span, y + span, 0));
				mesh.addVertex(glm::vec3(x, y + span, 0));

				mesh.addIndex(mesh.getNumVertices() - 1); mesh.addIndex(mesh.getNumVertices() - 4); mesh.addIndex(mesh.getNumVertices() - 3);
				mesh.addIndex(mesh.getNumVertices() - 1); mesh.addIndex(mesh.getNumVertices() - 2); mesh.addIndex(mesh.getNumVertices() - 3);

				noise_value = noise_value - (int)noise_value;
				color.setHsb(ofMap(index, 0, 3, 128, 255), 255, 255, ofMap(abs(noise_value - 0.5), 0, 0.5, 255, 0));
				for (int i = 0; i < 4; i++) {

					mesh.addColor(color);
				}
			}
		}

		index++;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	for (auto& mesh : this->mesh_list) {

		mesh.draw();
	}

	/*
	ostringstream os;
	os << setw(4) << setfill('0') << ofGetFrameNum() + 1;
	ofImage image;
	image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
	image.saveImage("image/img_" + os.str() + ".jpg");
	if (ofGetFrameNum() + 1 >= 24 * 20) {

		std::exit(1);
	}
	*/

	// > ffmpeg -i img_%04d.jpg -r 24 out.mp4
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}