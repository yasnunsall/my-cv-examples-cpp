#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "stdlib.h"

cv::Mat gaussian_noise(cv::Mat& image) {
    cv::Mat noisy = image.clone();

    int row = image.rows;
    int col = image.cols;
    int ch = image.channels();
    double mean = 0.0;
    double var = 0.05;
    double sigma = sqrt(var);

    cv::RNG rng;

    for (int i=0; i<row; i++) {
        for (int j=0; j<col; j++) {
            for (int c=0; c<ch; c++) {
                double gaussian_value = rng.gaussian(sigma);
                noisy.at<cv::Vec3b>(i,j)[c] = cv::saturate_cast<uchar>(image.at<cv::Vec3b>(i,j)[c] + gaussian_value);

            }
        }
    }

    return noisy;
}

cv::Mat salt_pepper_noise (cv::Mat& image) {
    cv::Mat noisy = image.clone();
    int row = image.rows;
    int col = image.cols;
    int ch = image.channels();
    double s_vs_p = 0.5;
    double amount = 0.004;

    //salt mode
    int num_salt = cvRound(amount * image.size().area() * s_vs_p);
    //coords = [np.random.randint(0, i - 1, int(num_salt)) for i in image.shape]
    for (int i=0; i < num_salt; i++) {
      int x = rand() % col;
      int y = rand() % row;
      noisy.at<cv::Vec3b>(y,x) = cv::Vec3b(255,255,255);
    }

    //pepper mode
    int mum_salt = cvRound(amount * image.size().area() * (1-s_vs_p));
    for (int i=0; i < num_salt; i++) {
        int x = rand() % col;
        int y = rand() % row;
        noisy.at<cv::Vec3b>(y,x) = cv::Vec3b(0,0,0);
    }

    return noisy;

}

int blurring() {
    cv::Mat img = cv::imread("C:\\Users\\ben\\CLionProjects\\opencv_cpp\\blurring\\NYC.jpg");
    cv::Mat img_rgb;
    cv::cvtColor(img, img_rgb, cv::COLOR_BGR2RGB);
    cv::namedWindow("Input", 0);
    cv::imshow("Input", img_rgb);

    cv::Mat blur_img;
    cv::blur(img, blur_img, cv::Size(3,3));
    cv::namedWindow("Blurring", 0);
    cv::imshow("Blurring", blur_img);

    cv::Mat gaussian_img;
    cv::GaussianBlur(img, gaussian_img, cv::Size(3,3), 7);
    cv::namedWindow("Gaussian", 0);
    cv::imshow("Gaussian", gaussian_img);

    cv::Mat image_scaled = img / 255;

    cv::Mat gaussianNoise = gaussian_noise(image_scaled);
    cv::namedWindow("Gaussian Noise", 0);
    cv::imshow("Gaussian Noise", gaussianNoise);

    cv::Mat spImage = salt_pepper_noise(image_scaled);
    cv::namedWindow("Salt Pepper Noise", 0);
    cv::imshow("Salt Pepper Noise", spImage);

    cv::Mat gaussian_noise_blur;
    cv::GaussianBlur(gaussian_img, gaussian_noise_blur, cv::Size(3,3), 7);
    cv::namedWindow("Gaussian Noise Blur ", 0);
    cv::imshow("Gaussian Noise Blur", gaussian_noise_blur);



    cv::waitKey(0);
    return 0;
}