#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int warp_perspective() {
    cv::Mat img = cv::imread("C:\\Users\\ben\\CLionProjects\\opencv_cpp\\warp_perspective\\kart.png");
    cv::namedWindow("Input", 0);
    //cv::imshow("Input", img);

    int width = 400, height = 500;

    cv::Point2f pts1[] = {
            cv::Point(203,1),
            cv::Point(1,472),
            cv::Point(540,150),
            cv::Point(338,617)
    };

    cv::Point2f pts2[] = {
            cv::Point(0,0),
            cv::Point(0, img.size().height),
            cv::Point (img.size().width, 0),
            cv::Point(img.size().width, img.size().height)
    };

    cv::Mat output;

    cv::Mat matrix = cv::getPerspectiveTransform(pts1, pts2);
    cv::warpPerspective(img, output, matrix, cv::Size(img.size().width, img.size().height));

    cv::namedWindow("Output", 0);
    cv::imshow("Output", output);


    cv::circle(img, cv::Point(203,1), 10, cv::Scalar(15,128,128), cv::FILLED);
    cv::imshow("Input", img);


    char c = (char)cv::waitKey(0);
    if (c == 'q')
        cv::destroyAllWindows();

    return 0;
}