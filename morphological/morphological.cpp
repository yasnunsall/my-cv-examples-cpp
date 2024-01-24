#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>



int morphological() {
    cv::Mat img = cv::imread("C:\\Users\\ben\\CLionProjects\\opencv_cpp\\morphological\\datai_team.jpg", cv::IMREAD_GRAYSCALE);
    cv::imshow("Org image", img);

    //erosion
    cv::Mat kernel = cv::Mat::ones(cv::Size(5,5), CV_8U);
    cv::Mat erode_mat;
    cv::erode(img, erode_mat, kernel, cv::Point(1));
    cv::imshow("Erode", erode_mat);

    //dilation
    cv::Mat dilate_img;
    cv::dilate(img, dilate_img, kernel, cv::Point(1));
    cv::imshow("Dilate", dilate_img);

    cv::Mat white_noise(img.size(), CV_8U);
    cv::randu(white_noise, cv::Scalar(0), cv::Scalar(2));
    white_noise *= 255;
    cv::imshow("White Noise", white_noise);

    //opening
    cv::Mat noise_img = img + white_noise;
    cv::imshow("Noise img", white_noise);

    cv::Mat opening;
    noise_img.convertTo(noise_img, CV_32F);
    cv::morphologyEx(noise_img, opening, cv::MORPH_OPEN, kernel);
    cv::imshow("Opening", opening);

    //closing
    cv::Mat black_noise(img.size(), CV_8U);
    black_noise *= -255;
    cv::Mat black_noise_img = black_noise + img;
    cv::threshold(black_noise_img, black_noise_img, -245, 0, cv::THRESH_TOZERO);
    cv::Mat closing;
    cv::morphologyEx(black_noise_img, closing, cv::MORPH_CLOSE, kernel);
    cv::imshow("Closing", closing);

    cv::Mat gradient;
    cv::morphologyEx(img, gradient, cv::MORPH_GRADIENT, kernel);
    cv::imshow("Gradient", gradient);


    cv::waitKey(0);
    return 0;
}