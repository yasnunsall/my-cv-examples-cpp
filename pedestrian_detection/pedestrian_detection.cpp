#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

int pedestrian_detection() {
    std::vector<std::string> img_path_list;
    std::string directory_path = "C:\\Users\\ben\\CLionProjects\\opencv_cpp\\cat_face_detection";

    for (const auto &entry: std::filesystem::directory_iterator(directory_path)) {
        if (entry.path().extension() == ".jpg") {
            img_path_list.push_back(entry.path().string());
        }
    }

    cv::HOGDescriptor hog;
    hog.setSVMDetector(cv::HOGDesqcriptor::getDefaultPeopleDetector());

    for (std::string image_path: img_path_list) {
        cv::Mat img = cv::imread(image_path);

        std::vector<cv::Rect> rects;
        std::vector<double> weights;

        hog.detectMultiScale(img, rects, weights, .0, cv::Size(8, 8), cv::Size(32,32), 1.02);
        for (int i=0; i<rects.size(); i++) {
            cv::Rect region = rects[i];
            cv::rectangle(img, region, cv::Scalar(0,0,255), 2);
        }

        cv::imshow("Pedestrian: ", img);
    }

    cv::VideoCapture cap("C:\\Users\\ben\\CLionProjects\\opencv_cpp\\pedestrian_detection\\yaya.mp4");

    cv::Mat frame;
    while (1) {
        if (!cap.read(frame))
            break;

        cv::Mat ret;
        cv::Size new_size = cv::Size(int(frame.cols * 0.6), int(frame.rows * 0.6));
        cv::resize(frame, ret, new_size, 0, 0, cv::INTER_AREA);

        std::vector<cv::Rect> rects;
        std::vector<double> weights;

        hog.detectMultiScale(ret, rects, weights, 1.1, cv::Size(5,5));
        for (int i=0; i<rects.size(); i++) {
            cv::Rect area = rects[i];
            cv::rectangle(ret, area, cv::Scalar(0,255,255), 2);
        }

        cv::imshow("Video: ", ret);
        char c = (char)cv::waitKey(1);
        if (c == 'q')
            break;


    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}