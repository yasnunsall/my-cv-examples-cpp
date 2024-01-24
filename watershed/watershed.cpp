#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

//int first();
int second();
int watershed() {
    second();
    return 0;
}

int first() {
    cv::Mat coins = cv::imread("C:\\Users\\ben\\CLionProjects\\opencv_cpp\\watershed\\coins.jpg");
    cv::imshow("Coins", coins);

    cv::Mat coins_blur;
    cv::medianBlur(coins, coins_blur, 13);
    cv::imshow("Blurred coins", coins_blur);

    cv::Mat coins_gray;
    cv::cvtColor(coins_blur, coins_gray, cv::COLOR_BGR2GRAY);
    cv::imshow("Blurred gray coins", coins_gray);

    cv::Mat coins_thresh;
    cv::threshold(coins_gray, coins_thresh, 75, 255, cv::THRESH_BINARY);
    cv::imshow("Coins thresh", coins_thresh);

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(coins_thresh.clone(), contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);
    for (int i=0; i<contours.size(); i++) {
        if (hierarchy[i][3] == -1) {
            cv::drawContours(coins, contours, i, cv::Scalar(0,255,0), 10);
        }
    }
    cv::imshow("Coin Thresh Contours", coins);

    cv::waitKey(0);
    return 0;
}

int second() {
    cv::Mat coins = cv::imread("C:\\Users\\ben\\CLionProjects\\opencv_cpp\\watershed\\coins.jpg");
    cv::imshow("Image", coins);

    cv::Mat coins_blur;
    cv::medianBlur(coins, coins_blur, 15);
    cv::imshow("Blurred", coins_blur);

    cv::Mat coins_gray;
    cv::cvtColor(coins_blur, coins_gray, cv::COLOR_BGR2GRAY);
    cv::imshow("Gray", coins_gray);

    cv::Mat coins_thresh;
    cv::threshold(coins_gray, coins_thresh, 65, 255, cv::THRESH_BINARY);
    cv::imshow("Thresholdig", coins_thresh);

    cv::Mat kernel = cv::Mat::ones(cv::Size(4, 4), CV_8U);
    cv::Mat opening;
    cv::morphologyEx(coins_thresh, opening, cv::MORPH_OPEN, kernel);
    cv::imshow("Opening", opening);

    cv::Mat dist_transform;
    cv::distanceTransform(opening, dist_transform, cv::DIST_L2, 5);
    cv::imshow("Distance Transform", dist_transform);

    cv::Mat sure_foreground;
    double max_val;
    cv::minMaxLoc(dist_transform, nullptr, &max_val, nullptr, nullptr);
    cv::threshold(dist_transform, sure_foreground, .4 * max_val, 255, 0);

    cv::Mat sure_foreground_8u, sure_background_8u;

    cv::Mat sure_background;
    cv::dilate(opening, sure_background, kernel);

    sure_foreground.convertTo(sure_foreground_8u, CV_8U);
    sure_background.convertTo(sure_background_8u, CV_8U);

    cv::Mat unknown;
    cv::subtract(sure_background_8u, sure_foreground_8u, unknown);
    cv::imshow("Unknown", unknown);

    cv::Mat marker;
    cv::connectedComponents(sure_foreground_8u, marker, 8);
    marker += 1;
    marker.setTo(0, unknown == 255);
    cv::Mat marker_8u;
    marker.convertTo(marker_8u, CV_8U),
    cv::imshow("Marker", marker_8u);

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(marker_8u.clone(), contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

    for(int i=0; i<contours.size(); i++) {
        if (hierarchy[i][3] == -1) {
            cv::drawContours(coins, contours, i, cv::Scalar(255,0,0), 2);
        }
    }

    cv::imshow("Contours", coins);


    cv::waitKey(0);
    return 0;
}
