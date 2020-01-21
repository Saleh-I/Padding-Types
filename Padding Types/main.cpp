#include<opencv2\core.hpp>
#include<opencv2\highgui.hpp>
#include<opencv2\imgcodecs.hpp>
#include<opencv2\imgproc.hpp>
#include <string>

using namespace cv;
using namespace std;

//  function to pad the image before convolution
Mat padding(Mat scr, int k_width, int k_height, string type)
{
	int pad_rows, pad_cols;
	pad_rows = (k_height - 1) / 2;
	pad_cols = (k_width - 1) / 2;
	Mat pad_image(Size(scr.cols + 2 * pad_cols, scr.rows + 2 * pad_rows), CV_8UC1, Scalar(0));
	scr.copyTo(pad_image(Rect(pad_cols, pad_rows, scr.cols, scr.rows)));
	// mirror padding
	if (type == "mirror")
	{
		for (int i = 0; i < pad_rows; i++)
		{
			scr(Rect(0, pad_rows - i, scr.cols, 1)).copyTo(pad_image(Rect(pad_cols, i, scr.cols, 1)));
			scr(Rect(0, (scr.rows - 1) - pad_rows + i, scr.cols, 1)).copyTo(pad_image(Rect(pad_cols,
				(pad_image.rows - 1) - i, scr.cols, 1)));
		}

		for (int j = 0; j < pad_cols; j++)
		{
			pad_image(Rect(2 * pad_cols - j, 0, 1, pad_image.rows)).copyTo(pad_image(Rect(j, 0, 1, pad_image.rows)));
			pad_image(Rect((pad_image.cols - 1) - 2 * pad_cols + j, 0, 1, pad_image.rows)).
				copyTo(pad_image(Rect((pad_image.cols - 1) - j, 0, 1, pad_image.rows)));
		}

		return pad_image;
	}
	// replicate padding
	else if (type == "replicate")
	{
		for (int i = 0; i < pad_rows; i++)
		{
			scr(Rect(0, 0, scr.cols, 1)).copyTo(pad_image(Rect(pad_cols, i, scr.cols, 1)));
			scr(Rect(0, (scr.rows - 1), scr.cols, 1)).copyTo(pad_image(Rect(pad_cols,
				(pad_image.rows - 1) - i, scr.cols, 1)));
		}

		for (int j = 0; j < pad_cols; j++)
		{
			pad_image(Rect(pad_cols, 0, 1, pad_image.rows)).copyTo(pad_image(Rect(j, 0, 1, pad_image.rows)));
			pad_image(Rect((pad_image.cols - 1) - pad_cols, 0, 1, pad_image.rows)).
				copyTo(pad_image(Rect((pad_image.cols - 1) - j, 0, 1, pad_image.rows)));
		}
		// zero padding
		return pad_image;
	}
	else
	{
		return pad_image;
	}

}



int main() {
	Mat img, dst;
	img = imread("airship.jpg", 0);

	Mat kernel;
	int k_w = 51;  // kernel width
	int k_h = 51;  // kernel height

	dst = padding(img, k_w, k_h, "mirror");

	namedWindow("dst", WINDOW_AUTOSIZE);
	imshow("dst", dst);

	waitKey(0);
	return 0;
}