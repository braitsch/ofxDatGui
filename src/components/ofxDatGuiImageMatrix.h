#pragma once
#include "ofxDatGui.h"

class ofxDatGuiImageMatrixButton : public ofxDatGuiInteractiveObject {

public:
	ofxDatGuiImageMatrixButton(int size, int index, std::string imagePath, ofxDatGuiTemplate* tmplt)
	{
		mIndex = index;
		mSelected = false;
		mTemplate = tmplt;
		mImagePath = imagePath;
		mRect = ofRectangle(0, 0, size, size);
		mBkgdColor = mTemplate->matrix.color.normal.button;
	}

	void setOrigin(float x, float y)
	{
		origin.x = x;
		origin.y = y;
	}

	void draw(int x, int y)
	{
		mRect.x = x + origin.x;
		mRect.y = y + origin.y;
		ofPushStyle();
		ofFill();
		ofSetColor(mBkgdColor);
		ofDrawRectangle(mRect);
		if (mImagePath.size() > 0) {
			if (!mLoadedImage.isAllocated()) {
				mLoadedImage.load(mImagePath);
			}
			mLoadedImage.draw(mRect);
		}
		ofPopStyle();
	}

	void hitTest(ofPoint m, bool mouseDown)
	{
		if (mRect.inside(m) && !mSelected) {
			if (mouseDown) {
				mBkgdColor = mTemplate->matrix.color.selected.button;
			}
			else {
				mBkgdColor = mTemplate->matrix.color.hover.button;
			}
		}
		else {
			onMouseOut();
		}
	}

	void setSelected(bool selected)
	{
		mSelected = selected;
	}

	bool getSelected()
	{
		return mSelected;
	}

	void onMouseOut()
	{
		if (mSelected) {
			mBkgdColor = mTemplate->matrix.color.selected.button;
		}
		else {
			mBkgdColor = mTemplate->matrix.color.normal.button;
		}
	}

	void onMouseRelease(ofPoint m)
	{
		if (mRect.inside(m)) {
			mSelected = !mSelected;
			ofxDatGuiInternalEvent e(ofxDatGuiEventType::MATRIX_BUTTON_TOGGLED, mIndex);
			internalEventCallback(e);
		}
	}

private:
	int x;
	int y;
	int mIndex;
	ofPoint origin;
	ofRectangle mRect;
	ofColor mBkgdColor;
	bool mSelected;
	ofxDatGuiTemplate* mTemplate;
	std::string mImagePath;
	ofImage mLoadedImage;
};

class ofxDatGuiImageMatrix : public ofxDatGuiComponent {

public:

	ofxDatGuiImageMatrix(string label, std::vector<std::string> imagePaths, ofxDatGuiTemplate* tmplt = nullptr) : ofxDatGuiComponent(label, tmplt)
	{
		mRadioMode = false;
		mImagePaths = imagePaths;
		mType = ofxDatGuiType::IMAGE_MATRIX;
		mStripeColor = mTemplate->matrix.color.stripe;
		mButtonSize = mTemplate->matrix.buttonSize;
		setButtons();
		setWidth(mRow.width);
	}

	static ofxDatGuiImageMatrix* getInstance()
	{
		return new ofxDatGuiImageMatrix("X", std::vector<std::string>());
	}

	void setOrigin(int x, int y)
	{
		ofxDatGuiComponent::setOrigin(x, y);
		mMatrixRect.x = x + mRow.inputX;
		mMatrixRect.y = y + mRow.padding;
	}

	void setTemplate(ofxDatGuiTemplate* tmplt)
	{
		ofxDatGuiComponent::setTemplate(tmplt);
		mButtonSize = mTemplate->matrix.buttonSize;
		mStripeColor = mTemplate->matrix.color.stripe;
		setButtons();
		setWidth(mRow.width);
	}

	void setButtons()
	{
		btns.clear();
		for (int i = 0; i<mImagePaths.size(); i++) {
			ofxDatGuiImageMatrixButton btn(mButtonSize, i, mImagePaths[i], mTemplate);
			btn.onInternalEvent(this, &ofxDatGuiImageMatrix::onButtonSelected);
			btns.push_back(btn);
		}
	}

	void setRadioMode(bool enabled)
	{
		mRadioMode = enabled;
	}

	void setWidth(int w)
	{
		ofxDatGuiComponent::setWidth(w);
		mMatrixRect.x = x + mRow.inputX;
		mMatrixRect.y = y + mRow.padding;
		mMatrixRect.width = mRow.width - mRow.padding - mRow.inputX;
		int nCols = floor(mMatrixRect.width / (mButtonSize + mMinPadding));
		int nRows = ceil(btns.size() / float(nCols));
		float padding = (mMatrixRect.width - (mButtonSize*nCols)) / (nCols - 1);
		for (int i = 0; i<btns.size(); i++) {
			float bx = (mButtonSize + padding)*(i%nCols);
			float by = (mButtonSize + padding)*(floor(i / nCols));
			btns[i].setOrigin(bx, by + mRow.padding);
		}
		mRow.height = (mRow.padding * 2) + ((mButtonSize + padding)*(nRows - 1)) + mButtonSize;
		mMatrixRect.height = mRow.height - (mRow.padding * 2);
	}

	bool hitTest(ofPoint m)
	{
		if (mMatrixRect.inside(m)) {
			for (int i = 0; i<btns.size(); i++) btns[i].hitTest(m, mMouseDown);
			return true;
		}
		else {
			for (int i = 0; i<btns.size(); i++) btns[i].onMouseOut();
			return false;
		}
	}

	void draw()
	{
		if (!mVisible) return;
		ofPushStyle();
		ofxDatGuiComponent::drawBkgd();
		ofxDatGuiComponent::drawLabel();
		ofxDatGuiComponent::drawStripe();
		ofSetColor(mTemplate->row.color.inputArea);
		ofDrawRectangle(mMatrixRect);
		for (int i = 0; i<btns.size(); i++) btns[i].draw(x + mRow.inputX, y);
		ofPopStyle();
	}

	void clear()
	{
		for (int i = 0; i<btns.size(); i++) btns[i].setSelected(false);
	}

	void setSelected(vector<int> v)
	{
		clear();
		for (int i = 0; i<v.size(); i++) btns[v[i]].setSelected(true);
	}

	vector<int> getSelected()
	{
		vector<int> selected;
		for (int i = 0; i<btns.size(); i++) if (btns[i].getSelected()) selected.push_back(i);
		return selected;
	}

	ofxDatGuiImageMatrixButton* getChildAt(int index)
	{
		return &btns[index];
	}

	void onMouseRelease(ofPoint m)
	{
		ofxDatGuiComponent::onFocusLost();
		ofxDatGuiComponent::onMouseRelease(m);
		for (int i = 0; i<btns.size(); i++) btns[i].onMouseRelease(m);
	}

	void onButtonSelected(ofxDatGuiInternalEvent e)
	{
		if (mRadioMode) {
			// deselect all buttons save the one that was selected //
			for (int i = 0; i<btns.size(); i++) btns[i].setSelected(e.index == i);
		}
		if (imageMatrixEventCallback != nullptr) {
			ofxDatGuiImageMatrixEvent ev(this, e.index, btns[e.index].getSelected());
			imageMatrixEventCallback(ev);
		}
		else {
			ofxDatGuiLog::write(ofxDatGuiMsg::EVENT_HANDLER_NULL);
		}
	}

private:

	int mButtonSize;
	std::vector<std::string> mImagePaths;
	bool mRadioMode;
	ofRectangle mMatrixRect;
	static const int mMinPadding = 2;
	vector<ofxDatGuiImageMatrixButton> btns;

};


