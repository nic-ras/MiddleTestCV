#include "libraries.h"

int SIFT( cv::Mat& original, cv::Mat& output){

    if (original.empty()) {
        std::cerr << "Impossible to load the image!" << std::endl;
        return -1;
    }

    // Create a SIFT detector
    cv::Ptr<cv::SIFT> siftPtr = cv::SIFT::create();

    // Detect the keypoints
    std::vector<cv::KeyPoint> keypoints;
    siftPtr->detect(original, keypoints);

    // Add results to image and save.
    cv::drawKeypoints(original, keypoints, output);
    cv::imwrite("sift_result.jpg", output);

    return 0;  

}