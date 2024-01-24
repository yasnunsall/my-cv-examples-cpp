#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int histogram() {
    cv::Mat red_blue = cv::imread("C:\\Users\\ben\\CLionProjects\\opencv_cpp\\histogram\\red_blue.jpg", cv::IMREAD_COLOR);
    cv::imshow("Input", red_blue);

    cv::Mat img_hist;
    int hist_size = 256;
    float range[]{0,256};
    const float* hist_range{range};
    int channels[]{0};

    cv::calcHist(&red_blue, 1, channels, cv::Mat(), img_hist, 1, &hist_size, &hist_range);
    std::cout << img_hist.size() << std::endl;

    cv::imshow("Hist", img_hist);

    cv::waitKey(0);
    return 0;
}