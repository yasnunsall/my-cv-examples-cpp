#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>


int blending() {
    cv::Mat img1 = cv::imread("C:\\Users\\ben\\CLionProjects\\opencv_cpp\\blending\\img1.JPG");
    cv::Mat img2 = cv::imread("C:\\Users\\ben\\CLionProjects\\opencv_cpp\\blending\\img2.JPG");
    cv::namedWindow("Input", 0);
    cv::imshow("Input", img1);

    cv::Mat img1_cvt;
    cv::cvtColor(img1, img1_cvt, cv::COLOR_BGR2RGB);
    cv::namedWindow("Output", 0);
    cv::imshow("Output", img1_cvt);

    cv::Mat img1_resized;
    cv::Mat img2_resized;
    cv::resize(img1, img1_resized, cv::Size(600,600));
    cv::resize(img2, img2_resized, cv::Size(600,600));

    cv::Mat img_weighted;
    cv::addWeighted(img1_resized, .3, img2_resized, .5, 0, img_weighted);
    cv::namedWindow("Weighted", 0);
    cv::imshow("Weighted", img_weighted);

    cv::waitKey(0);
    return 0;
}