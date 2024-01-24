#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

int contour_detection() {
    cv::Mat img = cv::imread("C:\\Users\\ben\\CLionProjects\\opencv_cpp\\contour_detection\\contour.jpg", cv::IMREAD_GRAYSCALE);
    cv::imshow("Input", img);

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    cv::findContours(img, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

    cv::Mat external_contour(cv::Mat::zeros(img.size(), CV_64F)),
            internal_contour(cv::Mat::zeros(img.size(), CV_64F));

    for(int i=0; i<contours.size(); i++) {
        if(hierarchy[i][3] == -1) {
            cv::drawContours(external_contour, contours, i, 255, -1);
        }
        else{
            cv::drawContours(internal_contour, contours, i, 255, -1);
        }
    }

    cv::imshow("External contour", external_contour);
    cv::imshow("Internal contour", internal_contour);
    cv::waitKey(0);
    return 0;
}