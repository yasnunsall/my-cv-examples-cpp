#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

int meanshift_camshift() {

    cv::VideoCapture cap("C:\\Users\\ben\\Desktop\\python_projects\\opencv_python\\Gİ-1\\Python OpenCV ile Sıfırdan Uzmanlığa Görüntü İşleme (Gİ-1)\\3_Görüntü İşleme Projeleri\\sleep_detection\\video1.mp4");

    cv::Mat frame;
    cap.read(frame);

    if (frame.empty())
        return -1;

    cv::CascadeClassifier face_cascade;
    face_cascade.load("C:\\Users\\ben\\CLionProjects\\opencv_cpp\\meanshift_camshift\\haarcascade_frontalface_default.xml");

    std::vector<cv::Rect> face_rects;
    face_cascade.detectMultiScale(frame, face_rects);

    if (!face_rects.empty()) {
        cv::Rect track_window = face_rects[0];
        cv::Mat roi = frame(track_window);

        cv::Mat hsv_roi;
        cv::cvtColor(roi, hsv_roi, cv::COLOR_BGR2HSV);

        int h_bins = 180;
        int histSize[] = {h_bins};
        float h_ranges[] = {0, 180};
        const float* ranges[] = {h_ranges};
        cv::MatND roi_hist;
        int channels[] = {0};
        cv::calcHist(&hsv_roi, 1, channels, cv::Mat(), roi_hist, 1, histSize, ranges, true, false);
        cv::normalize(roi_hist, roi_hist, 0, 255, cv::NORM_MINMAX);

        cv::TermCriteria term_crit(cv::TermCriteria::EPS | cv::TermCriteria::COUNT, 5, 1);

        while (true) {
            cap.read(frame);

            if (!frame.empty()) {
                cv::Mat hsv;
                cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);

                cv::Mat dst;
                cv::calcBackProject(std::vector<cv::Mat>{hsv}, std::vector<int>{0},
                                    roi_hist, dst, std::vector<float>{0,180}, 1);

                cv::Rect new_track_window;
                cv::meanShift(dst, track_window, term_crit);
                new_track_window = track_window;

                cv::rectangle(frame, new_track_window, cv::Scalar(0,255,255), 5);
                cv::imshow("Takip", frame);

                char c = (char)cv::waitKey(1);
                if (c == 'q') break;
            } else {
                std::cout << "Frame is empty!" << std::endl;
                break;
            }
        }

        cap.release();
        cv::destroyAllWindows();

        return 0;
    } else {
        std::cout << "Face not found" << std::endl;
        return -1;
    }
}
