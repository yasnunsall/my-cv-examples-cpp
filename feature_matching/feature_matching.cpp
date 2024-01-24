#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <iostream>

int feature_matching() {
    //main img
    cv::Mat chos = cv::imread("C:\\Users\\ben\\CLionProjects\\opencv_cpp\\feature_matching\\chocolates.jpg");
    cv::imshow("Main img", chos);

    //img to searching
    cv::Mat cho = cv::imread("C:\\Users\\ben\\CLionProjects\\opencv_cpp\\feature_matching\\nestle.jpg");
    cv::imshow("Img to search", cho);

    //orb identifier
    //features of the object such as corner-edge
    cv::Ptr<cv::Feature2D> orb = cv::ORB::create();
    cv::Ptr<cv::Feature2D> sift = cv::SIFT::create();

    std::vector<cv::KeyPoint> kp1, kp2;
    cv::Mat des1, des2;

    orb->detectAndCompute(cho, cv::noArray(), kp1, des1);
    orb->detectAndCompute(chos, cv::noArray(), kp2, des2);

    cv::BFMatcher bf_orb(cv::NORM_HAMMING);
    std::vector<cv::DMatch> matches_orb;
    bf_orb.match(des1, des2, matches_orb);

    std::sort(matches_orb.begin(), matches_orb.end(), [](cv::DMatch a, cv::DMatch b) {
        return a.distance < b.distance;
    });

    cv::Mat img_match_orb;
    std::vector<cv::DMatch> first_20_match;
    for(int i=0;i<20;i++){
        first_20_match.push_back(matches_orb[i]);
    }
    cv::drawMatches(cho, kp1, chos, kp2, first_20_match, img_match_orb);
    cv::imshow("Draw Matches ORB", img_match_orb),

    //SIFT
    sift ->detectAndCompute(cho, cv::noArray(), kp1, des1);
    sift ->detectAndCompute(chos, cv::noArray(), kp2, des2);

    cv::BFMatcher bf_sift(cv::NORM_L2);
    std::vector<std::vector<cv::DMatch>> matches_sift;
    bf_sift.knnMatch(des1, des2, matches_sift, 2);

    std::vector<cv::DMatch> good_matches_sift;
    for (int i=0; i<matches_sift.size(); i++) {
        if (matches_sift[i][0].distance < .75 * matches_sift[i][1].distance) {
            good_matches_sift.push_back(matches_sift[i][0]);
        }
    }

    cv::Mat img_match_sift;
    cv::drawMatches(cho, kp1, chos, kp2, good_matches_sift, img_match_sift);
    cv::imshow("Draw Matches SIFT", img_match_sift);

    cv::waitKey(0);
    return 0;
}