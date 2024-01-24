#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

int thresholding() {
    cv::Mat img1 = cv::imread("C:\\Users\\ben\\CLionProjects\\opencv_cpp\\thresholding\\img1.JPG");
    cv::Mat img;
    cv::cvtColor(img1, img, cv::COLOR_BGR2GRAY);
    cv::namedWindow("Input", 0);
    cv::imshow("Input", img);

    cv::Mat thresh_img;
    cv::threshold(img, thresh_img, 60, 255, cv::THRESH_BINARY);
    cv::namedWindow("Output", 0);
    //cv::imshow("Output", thresh_img);

    cv::Mat thresh_img2;
    cv::adaptiveThreshold(img, thresh_img2, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 11, 8);
    cv::imshow("Output", thresh_img2);

    cv::waitKey(0);
    return 0;
}