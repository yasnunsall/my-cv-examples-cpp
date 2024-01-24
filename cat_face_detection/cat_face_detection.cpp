#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

int cat_face_detection() {
    std::vector<std::string> img_path_list;
    for (const auto &entry: fs::directory_iterator("C:\\Users\\ben\\CLionProjects\\opencv_cpp\\cat_face_detection")) {
        if (entry.path().extension() == ".jpg") {
            img_path_list.push_back(entry.path().string());
        }
    }

    for (const std::string &path: img_path_list) {
        std::cout << path << std::endl;
    }

    for (std::string j : img_path_list) {
        cv::Mat img = cv::imread(j);
        cv::Mat gray_img;
        cv::cvtColor(img, gray_img, cv::COLOR_BGR2GRAY);
        cv::CascadeClassifier detector = cv::CascadeClassifier("C:\\Users\\ben\\CLionProjects\\opencv_cpp\\cat_face_detection\\haarcascade_frontalcatface.xml");
        std::vector<cv::Rect> rects;
        detector.detectMultiScale(gray_img, rects, 1.045, 4);

        for (int i=0; i<rects.size(); i++) {
            cv::rectangle(img, cv::Point(rects[i].x, rects[i].y),
                          cv::Point(rects[i].x+rects[i].width, rects[i].y+rects[i].height),
                          cv::Scalar(0,255,255), 2);
            cv::putText(img, "Kedi " + std::to_string(i+1), cv::Point(rects[i].x,rects[i].y-10),
                        cv::FONT_HERSHEY_SIMPLEX, .55, cv::Scalar(0,255,255), 2);
        }

        cv::imshow("Output", img);
        cv::waitKey(0);

    }


    return 0;
}