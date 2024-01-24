#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <deque>

int ball_detection_and_tracking() {
    int buffer_size = 16;
    std::deque<cv::Point> pts;

    cv::Scalar blue_lower(84, 98, 0);
    cv::Scalar blue_upper(179, 255, 255);

    cv::VideoCapture cap(0);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 960);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

    while (1) {
        cv::Mat frame;
        bool success = cap.read(frame);

        if (!success) {
            break;
        }

        cv::Mat hsv;
        cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);

        cv::Mat mask;
        cv::inRange(hsv, blue_lower, blue_upper, mask);

        cv::Mat erode, dilate;
        cv::erode(mask, erode, cv::Mat(), cv::Point(2));
        cv::dilate(erode, dilate, cv::Mat(), cv::Point(2));

        std::vector<std::vector<cv::Point>> contours;
        std::vector<cv::Vec4i> hierarchy;
        cv::findContours(dilate.clone(), contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        if (!contours.empty()) {
            double max_area = -1;
            int max_area_idx = -1;
            for (int i=0; i<contours.size(); i++) {
                double area = cv::contourArea(contours[i]);
                if (area > max_area){
                    max_area = area;
                    max_area_idx = i;
                }
            }

            if (max_area_idx != -1) {
                std::vector<cv::Point> largest_contour = contours[max_area_idx];
                cv::RotatedRect rect = cv::minAreaRect(largest_contour);

                cv::Point2f vertices[4];
                rect.points(vertices);
                for (int i=0; i<4; i++) {
                    cv::line(frame, vertices[i], vertices[(i+1)%4], cv::Scalar(0,255,255), 2);
                }
            }

        }


        cv::imshow("Object Tracking", frame);

        char c = static_cast<char>(cv::waitKey(1));
        if (c == 'q') {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}
