/* Noyan Erdin Kilic */

#ifndef DATASET_H
#define DATASET_H

#include <unordered_map>
#include <vector>

#include <opencv2/opencv.hpp>

struct Model
{
    std::string objectId; // this is the id of the object, e.g. sugar box has id 004 (004_sugar_box)
    std::string modelId; // this is the id of the model, e.g. view_30_006_mask.png has id 006
    std::string angle;
    cv::Mat color;
    cv::Mat mask;

    static Model load(Model &model, const std::string &file, std::string &type);
};

struct Label
{
    std::string objectId;
    std::string objectName;
    int xmin;
    int ymin;
    int xmax;
    int ymax;

    static Label parse(const std::string &line);
    static std::string toString(const Label &label);

    friend std::ostream &operator<<(std::ostream &os, const Label &label)
    {
        os << "Object ID: " << label.objectId << ", "
           << "Object Name: " << label.objectName << ", "
           << "Bounding Box: (" << label.xmin << ", " << label.ymin
           << ", " << label.xmax << ", " << label.ymax << ")";
        return os;
    }
};

// NOTE: object ids are truncated, e.g. "004" becomes "4" for the sugar box.
class Dataset
{
public:
    static std::unique_ptr<Dataset> load(const std::string &folderPath);

    void print() const;
    // use this function to access a certain model from m_models if needed
    static std::string createModelMapKey(const std::string &objectId, const std::string &angle, const std::string &modelId)
    {
        return objectId + "_" + angle + "_" + modelId;
    }

    const std::unordered_map<std::string , cv::Mat> &getTestImages() const { return m_testImages; };
    const std::unordered_map<std::string, Model> &getModels() const { return m_models; };
    const std::unordered_map<std::string , std::vector<Label>> &getLabels() const { return m_labels; };
    const std::unordered_map<std::string, std::string> &getObjects() const { return m_objects; };

private:
    std::unordered_map<std::string , cv::Mat> m_testImages; // filename -> image
    // perhaps it doesn't make much sense to make this a map, but it would be easier to look up if needed
    std::unordered_map<std::string, Model> m_models; // createModelMapKey(objectId, angle, modelId) -> model
    std::unordered_map<std::string, std::vector<Label>> m_labels; // filename -> label

    std::unordered_map<std::string, std::string> m_objects; // id -> name
};

#endif