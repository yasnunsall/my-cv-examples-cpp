#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

int joining_image() {
    cv::Mat img = cv::imread("C:\\Users\\ben\\CLionProjects\\opencv_cpp\\joining_image\\lenna.png");
    cv::namedWindow("Input", 0);
    cv::imshow("Input", img);

    cv::Mat hor;
    cv::Mat ver;
   // cv::hconcat(img, img, hor);
    cv::vconcat(img, img, ver);
    cv::namedWindow("Output", 0);
    cv::imshow("Output", ver);

    char c = (char)cv::waitKey(0);
    if (c=='q')
        cv::destroyAllWindows();


    return 0;
}