#include "pch.h"
#include "ImageConvert.h"
 
void ImageConvert::convert() {

	for (int i = 0; i < MAX_INPUTS; i++) {

		hr = LoadFromWICFile(PB->inputFilePaths.at(i).c_str(), WIC_FLAGS_NONE, &screenshotImageInfo.at(i), screenshotImageIn.at(i));
		if (FAILED(hr)) displayError(hr);

		hr = resultImage.at(i).Initialize2D(DXGI_FORMAT_R8G8B8A8_UNORM, 2048, 2048, 1, 0, CP_FLAGS_NONE);
		if (FAILED(hr))displayError(hr);

		Rect r(0, 0, screenshotImageInfo.at(i).width, screenshotImageInfo.at(i).height);
		hr = CopyRectangle(*screenshotImageIn.at(i).GetImage(0, 0, 0), r, *resultImage.at(i).GetImage(0, 0, 0),
			TEX_FILTER_DEFAULT, 64, 484);
		if (FAILED(hr)) displayError(hr);

		hr = SaveToDDSFile(*resultImage.at(i).GetImage(0, 0, 0), DDS_FLAGS_NONE, PB->outputPaths.at(i).c_str());
		if (FAILED(hr)) displayError(hr);
	}
}

void ImageConvert::displayError(HRESULT hr) {

	_com_error err(hr);
	MessageBox(NULL, err.ErrorMessage(), "ALR_ERROR", MB_SETFOREGROUND);
	exit(EXIT_FAILURE);
}