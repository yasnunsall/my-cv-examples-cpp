#include <opencv2/opencv.hpp>
#include <iostream>

cv::Mat region_of_interest(cv::Mat image, std::vector<cv::Point> vertices) {
    cv::Mat mask = cv::Mat::zeros(image.size(), CV_8U);
    std::vector<cv::Point> roi_vertices;
    for (int i=0; i<3; i++) {
        roi_vertices.push_back(vertices[i]);
    }
    const cv::Point* ppt[1] = {&roi_vertices[0]};
    int npt[] = {static_cast<int>(roi_vertices.size())};
    cv::fillPoly(mask, ppt, npt, 1, cv::Scalar(255));
    cv::Mat masked_img;
    cv::bitwise_and(image, mask, masked_img);
    return masked_img;

}

cv::Mat draw_lines(cv::Mat image, std::vector<cv::Vec4i> lines) {
    cv::Mat image_copy(image.clone());
    cv::Mat blank_image(cv::Mat::zeros(image.size(), CV_8UC3));

    for (const auto& line: lines) {
        cv::line(blank_image, cv::Point(line[0], line[1]),
                 cv::Point(line[2], line[3]),
                 cv::Scalar(0,255,0), 10);
    }

    cv::addWeighted(image_copy, 1, blank_image, .5, 0, image_copy);
    return image_copy;
}

cv::Mat process(cv::Mat image) {
    int height(image.rows), width(image.cols);
    std::vector<cv::Point> region_of_interest_vertices = {
            cv::Point(0, height),
            cv::Point(width/2, height/2),
            cv::Point(width, height)
    };

    cv::Mat gray_image;
    cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);

    cv::Mat canny_image;
    cv::Canny(gray_image, canny_image, 250, 150);

    cv::Mat roi = region_of_interest(canny_image, region_of_interest_vertices);

    std::vector<cv::Vec4i> lines;
    cv::HoughLinesP(roi, lines, 3, CV_PI/180, 200, 150, 5);

    cv::Mat image_with_lines = draw_lines(image, lines);
    return image_with_lines;
}

int road_line_detection() {
    cv::VideoCapture cap("C:\\Users\\ben\\CLionProjects\\opencv_cpp\\road_line_detection\\video1.mp4");

    while (true) {
        cv::Mat img;
        cap >> img;

        if (img.empty())
            break;

        cv::Mat processed_img = process(img);

        cv::imshow("Image", processed_img);

        char c = (char)cv::waitKey(1);
        if (c=='q')
            break;
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}