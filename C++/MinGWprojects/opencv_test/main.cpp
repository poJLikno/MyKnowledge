#include <iostream>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;

int main() {

	VideoCapture cap(0);
	if (!cap.isOpened()) {
		cout << "Error initializing video camera!" << endl;
		return -1;
	}

	char* windowName = "Webcam Feed";
	namedWindow(windowName, WINDOW_AUTOSIZE);

	Mat frame;

	int frameWidth = cap.get(CAP_PROP_FRAME_WIDTH);
	int frameHeight = cap.get(CAP_PROP_FRAME_HEIGHT);
	printf("%dx%d\n", frameWidth, frameHeight);

	VideoWriter output("output.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, Size(frameWidth, frameHeight));

	while (cap.read(frame))
    {
		imshow(windowName, frame);

		output.write(frame);

		if (waitKey(10) >= 0) break;
	}

	output.release();
	cap.release();
	destroyAllWindows();

	return 0;
}
