#pragma once
#include "pch.h"
#include "PathBuilder.h"
 
class ImageConvertParent {
public:
	virtual void displayError(HRESULT hr) = 0,
		convert() = 0;
};

class ImageConvert : public ImageConvertParent {
private:

	HRESULT hr;
	PathBuilderParent* PB = NULL;

	void displayError(HRESULT hr),
		convert();

	array<ScratchImage, MAX_INPUTS> screenshotImageIn,
		resultImage;
	array<TexMetadata, MAX_INPUTS> screenshotImageInfo;

public:

	ImageConvert(PathBuilderParent* PBT) : PB(PBT) {
		hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
		if (FAILED(hr)) displayError(hr);

		convert();
	}
};