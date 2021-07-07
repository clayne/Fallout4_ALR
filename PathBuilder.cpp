#include "pch.h"
#include "pathBuilder.h"
 
void PathBuilder::findDLLPath() {

	ostringstream pathSS;
	TCHAR path[_MAX_PATH + 1];
	GetModuleFileName(GetModuleHandle(("ALR.dll")), path, sizeof(path) / sizeof(path[0]));
	for (int i = 0; path[i + PLUGIN_PATH_LEN] != 0; i++)
		pathSS << path[i];

	outputPath = pathSS.str() + "Textures\\Interface\\ALR_Backgrounds\\";
	iniPath = pathSS.str() + "F4SE\\Plugins\\ALR.ini";
}

void PathBuilder::findInputFiles() {
	for (auto& p : std::experimental::filesystem::directory_iterator(inputPath))
		if (p.path().extension() == ".jpg" || p.path().extension() == ".png" || p.path().extension() == ".JPG" || p.path().extension() == ".PNG")
			inputFiles.emplace_back(p.path().stem().string() + p.path().extension().string());
}

void PathBuilder::correctFiles() {

	random_device rd;
	mt19937 g(rd());

	if (inputFiles.size() > MAX_INPUTS) {
		shuffle(inputFiles.begin(), inputFiles.end(), g);
		inputFiles.resize(MAX_INPUTS);
	}
	else if (inputFiles.size() < MAX_INPUTS) {

		vector<string> tCopy = inputFiles;
		for (int i = 0; inputFiles.size() < MAX_INPUTS; i++) {
			shuffle(tCopy.begin(), tCopy.end(), g);
			inputFiles.insert(inputFiles.end(), tCopy.begin(), tCopy.end());
		}
		inputFiles.resize(MAX_INPUTS);
	}
}

void PathBuilder::generateInputPaths() {
	for (_int64 i = 0; i < MAX_INPUTS; i ++) {
		string temp = inputPath + inputFiles.at(i);
		inputFilePaths.emplace_back(wstring(temp.begin(), temp.end()));
	}
}

void PathBuilder::generateOutputPaths() {
	for (int i = 0; i < MAX_INPUTS; i++) {
		string temp = outputPath + to_string(i) + ".dds";
		outputPaths.at(i) = wstring(temp.begin(), temp.end());
	}
}

void PathBuilder::displayErrorMessage(string title, string message) {
	MessageBox(NULL, message.c_str(), title.c_str(), MB_SETFOREGROUND);
	exit(EXIT_FAILURE);
}