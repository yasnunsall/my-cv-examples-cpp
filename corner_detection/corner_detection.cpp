#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

int corner_detection() {
    cv::Mat img = cv::imread("C:\\Users\\ben\\CLionProjects\\opencv_cpp\\corner_detection\\sudoku.jpg", cv::IMREAD_GRAYSCALE);
    cv::imshow("Image", img);
    cv::Mat img_32f;
    img.convertTo(img_32f, CV_32F, 1./255.);

    cv::Mat dst;
    cv::cornerHarris(img, dst, 2, 5, .04);
    cv::imshow("Harris img", dst);

    cv::Mat dst_dilate;
    cv::dilate(dst, dst_dilate, cv::Mat());
    cv::imshow("Dst dilate", dst_dilate);
    double max_val;
    cv::minMaxLoc(dst_dilate, nullptr, &max_val);
    cv::Mat mask = (dst_dilate > .2*max_val);
    cv::imshow("Mask", mask);
    cv::Mat result = img_32f.clone();
    result.setTo(1, mask);
    cv::imshow("Result", result);

    cv::Mat img_clone(img_32f.clone());
    cv::Mat blur;
    cv::blur(img_clone, blur, cv::Size(4,4));
    cv::imshow("Blur img", blur);
    cv::Mat blur_dilate;
    cv::dilate(blur, blur_dilate, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(4,4)));
    cv::imshow("Blur dilate", blur_dilate);

    std::vector<cv::Point2f> corners;
    cv::goodFeaturesToTrack(blur_dilate, corners, 120, .1, 10);

    for(const cv::Point2f corner: corners) {
        int x = static_cast<int>(corner.x);
        int y = static_cast<int>(corner.y);
        cv::circle(blur_dilate, cv::Point(x,y), 6, cv::Scalar(125,125,125), cv::FILLED);
    }

    cv::imshow("Modified img", blur_dilate);






    cv::waitKey(0);
    return 0;
}