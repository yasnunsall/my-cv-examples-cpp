#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

int edge_detection() {
    cv::Mat img = cv::imread("C:\\Users\\ben\\CLionProjects\\opencv_cpp\\edge_detection\\sehir.jpg", cv::IMREAD_GRAYSCALE);
    cv::imshow("Image", img);

    cv::Mat edges;
    cv::Canny(img, edges, 70, 255);
    cv::imshow("Edges", edges);

    double med_val = cv::mean(img)[0];
    std::cout << "Median value :" << med_val << std::endl;

    int low = std::max(0, static_cast<int>((1-.33)*med_val));
    int high = std::min(255, static_cast<int>((1+.33)*med_val));

    cv::Canny(img, edges, low, high);
    cv::imshow("Canny", edges);

    cv::Mat blurred_img;
    cv::blur(img, blurred_img, cv::Size(5,5));
    cv::imshow("Blurred image", blurred_img);

    double med_val_blur = cv::mean(blurred_img)[0];
    int low_blur = std::max(0, static_cast<int>((1-.33)*med_val_blur));
    int high_blur = std::min(255, static_cast<int>((1+.33)*med_val_blur));

    cv::Mat blurred_edges;
    cv::Canny(blurred_img, blurred_edges, low_blur, high_blur);
    cv::imshow("Blurred Edges", blurred_edges);


    cv::waitKey(0);
    return 0;
}