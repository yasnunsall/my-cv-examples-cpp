#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int gradients() {
    cv::Mat img = cv::imread("C:\\Users\\ben\\CLionProjects\\opencv_cpp\\gradients\\sudoku.jpg", cv::IMREAD_GRAYSCALE);
    cv::imshow("Input", img);

    cv::Mat laplacian;
    cv::Laplacian(img, laplacian, CV_16S);
    cv::imshow("Laplacian", laplacian);

    cv::Mat sobelx;
    cv::Sobel(img, sobelx, CV_16S, 1, 0, 5);
    cv::imshow("Sobel X", sobelx);

    cv::Mat sobely;
    cv::Sobel(img, sobely, CV_16S, 0, 1, 5);
    cv::imshow("Sobel Y", sobely);

    cv::waitKey(0);
    return 0;
}