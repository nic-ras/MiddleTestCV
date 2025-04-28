#include "feature_matcher.h"
#include <filesystem>

void loadModelDescriptors(const std::string& model_folder, std::vector<ModelDescriptor>& model_descriptors) {
    cv::Ptr<cv::SIFT> sift = cv::SIFT::create();
    for (const auto& entry : std::filesystem::directory_iterator(model_folder)) {
        if (entry.path().extension() == ".jpg" || entry.path().extension() == ".png") {
            cv::Mat img = cv::imread(entry.path().string());
            if (img.empty()) continue;

            ModelDescriptor model;
            model.label = "object"; // Can customize per category if organized
            sift->detectAndCompute(img, cv::noArray(), model.keypoints, model.descriptors);
            model_descriptors.push_back(model);
        }
    }
}

void detectObjects(const std::vector<ModelDescriptor>& models, const cv::Mat& scene_img, std::vector<Detection>& detections) {
    cv::Ptr<cv::SIFT> sift = cv::SIFT::create();
    std::vector<cv::KeyPoint> scene_kp;
    cv::Mat scene_desc;
    sift->detectAndCompute(scene_img, cv::noArray(), scene_kp, scene_desc);

    if (scene_desc.empty()) return;

    cv::BFMatcher matcher(cv::NORM_L2);

    for (const auto& model : models) {
        std::vector<cv::DMatch> matches;
        matcher.match(model.descriptors, scene_desc, matches);

        double min_dist = 100;
        for (const auto& m : matches) {
            if (m.distance < min_dist) min_dist = m.distance;
        }

        std::vector<cv::DMatch> good_matches;
        for (const auto& m : matches) {
            if (m.distance <= std::max(2.5 * min_dist, 50.0)) {
                good_matches.push_back(m);
            }
        }

        if (good_matches.size() < 15) continue;

        std::vector<cv::Point2f> obj_pts, scene_pts;

        for (const auto& m : good_matches) {
            obj_pts.push_back(model.keypoints[m.queryIdx].pt);
            scene_pts.push_back(scene_kp[m.trainIdx].pt);
        }

        cv::Mat H = cv::findHomography(obj_pts, scene_pts, cv::RANSAC);
        if (H.empty()) continue;

        std::vector<cv::Point2f> corners = {
            {0.0f, 0.0f},
            {static_cast<float>(scene_img.cols), 0.0f},
            {static_cast<float>(scene_img.cols), static_cast<float>(scene_img.rows)},
            {0.0f, static_cast<float>(scene_img.rows)}
        };
        std::vector<cv::Point2f> projected_corners;
        cv::perspectiveTransform(corners, projected_corners, H);

        cv::Rect bbox = cv::boundingRect(projected_corners);
        if (bbox.area() < 1000) continue; // sanity check

        detections.push_back({model.label, bbox});
    }
}
