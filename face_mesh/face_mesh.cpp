#include <opencv2/opencv.hpp>
#include <iostream>

int face_mesh() {
 //   cv::VideoCapture cap("C:\\Users\\ben\\CLionProjects\\opencv_cpp\\face_mesh\\video3.mp4");
    cv::VideoCapture cap(0);
    cv::CascadeClassifier face_cascade;

    if (!face_cascade.load("C:\\Users\\ben\\CLionProjects\\opencv_cpp\\face_mesh\\haarcascade_frontalface_default.xml")) {
        std::cerr << "Error loading" << std::endl;
        return -1;
    }

    cv::Mat frame;

    while(cap.read(frame)) {
        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        std::vector<cv::Rect> faces;
        face_cascade.detectMultiScale(gray, faces, 1.1, 5, 0, cv::Size(30,30));

        for(const auto& face: faces) {
            cv::rectangle(frame, face, cv::Scalar(0,255,0), 2);
        }
        cv::imshow("Face Mesh", frame);

        char c = (char)cv::waitKey(1);
        if (c=='q')
            break;

    }
    cap.release();
    cv::destroyAllWindows();
}