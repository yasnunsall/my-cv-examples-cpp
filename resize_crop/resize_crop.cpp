#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int resize_crop() {
    cv::Mat img = cv::imread("C:\\Users\\ben\\CLionProjects\\opencv_cpp\\resize_crop\\lenna.png");
    cv::namedWindow("Input", 0);
    cv::imshow("Input", img);
    std::cout << img.size << std::endl;


    cv::Mat output;
    cv::resize(img, output, cv::Size(1024,1024));
    cv::namedWindow("Output", 0);
    cv::imshow("Output", output);

    cv::Mat output_crop = img(cv::Range(50,100), cv::Range(40,80));
    cv::namedWindow("Crop img", 0);
    cv::imshow("Crop img", output_crop);

    char c = (char)cv::waitKey(0);
    if (c=='q')
        cv::destroyAllWindows();

    return 0;
}