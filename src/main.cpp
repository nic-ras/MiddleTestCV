#include "libraries.h"
#include <opencv2/opencv.hpp>
#include "feature_matcher.h"
#include "utils.h"

int main(int argc, char** argv)
{
    std::string model_folder = "data/004_sugar_box/models";
    std::string test_image_path = "data/004_sugar_box/test_images/4_0001_000121-color.jpg";

    // Load as grayscale
    cv::Mat test_img = cv::imread(test_image_path,0);

    if (test_img.empty()) {
        std::cerr << "Impossible to load the image!" << std::endl;
        return -1;
    }

     // Preprocess the test image
    cv::Mat preprocessed_img = preprocessImage(test_img);

    // Load model descriptors
    std::vector<ModelDescriptor> model_descriptors;
    loadModelDescriptors(model_folder, model_descriptors);

    // Detect objects
    std::vector<Detection> detections;
    detectObjects(model_descriptors, preprocessed_img, detections);

    // Draw detections
    drawDetections(preprocessed_img, detections);

    // Save results
    saveDetections("results/boxes.txt", detections);
    cv::imwrite("results/output.jpg", preprocessed_img);

    // // Create a SIFT detector - Moved sift implementation to feature_matcher
    // cv::Ptr<cv::SIFT> siftPtr = cv::SIFT::create();

    // // Detect the keypoints
    // std::vector<cv::KeyPoint> keypoints;
    // siftPtr->detect(test_img, keypoints);

    // // Add results to image and save.
    // cv::Mat output;
    // cv::drawKeypoints(test_img, keypoints, output);
    // cv::imwrite("sift_result.jpg", output);

    return 0;
}