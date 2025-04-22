/* Noyan Erdin Kilic */

#include "dataset.h"

#include <filesystem>
#include <fstream>
#include <string>

namespace util
{
    static constexpr unsigned int hash(const char *s, int off = 0)
    {
        return !s[off] ? 5381 : (hash(s, off+1)*33) ^ s[off];
    }

    static std::string getObjectId(const std::string &idAndName)
    {
        std::istringstream iss(idAndName);
        std::string token;
        iss >> token;
        size_t underscorePos = token.find('_');
       return std::to_string(stoi(token.substr(0, underscorePos)));
    }
}

void Dataset::print() const
{
    std::cout << "object list\n";
    std::cout << "*************************\n";
    for (const auto &obj : m_objects)
    {
        std::cout << "id: " << obj.first << " name: " << obj.second << "\n";
    }
    std::cout << "*************************\n";

    std::cout << "labels\n";
    std::cout << "*************************\n";
    for (const auto &[filename, labels]: m_labels)
    {
        for (const auto &l: labels)
            std::cout << filename << " -> " << l << std::endl;
        std::cout << "----\n";
    }
    std::cout << "*************************\n";

    std::cout << "models\n";
    std::cout << "*************************\n";
    for (const auto &[key, model]: m_models)
    {
        std::cout << "obj: " << model.objectId << " angle: " << model.angle
                  << " model: " << model.modelId << " color: " << model.color.size()
                  << " mask: " << model.mask.size() << std::endl;
    }
    std::cout << "*************************\n";

    std::cout << "test_images\n";
    std::cout << "*************************\n";
    for (const auto &[key, img]: m_testImages)
    {
        std::cout << "file: " << key << " img: " << img.size() << std::endl;
    }
    std::cout << "*************************\n";
}

std::unique_ptr<Dataset> Dataset::load(const std::string &folderPath)
{
    std::unique_ptr<Dataset> dataset(new Dataset());

    std::filesystem::path dir(folderPath);
    for (const auto &it : std::filesystem::directory_iterator(dir))
    {
        if (it.is_directory())
        {
            std::string object = it.path().filename();
            std::string id = "failedToRead";
            std::string name = "failedToRead";
            size_t underscorePos = object.find('_');
            if (underscorePos != std::string::npos) {
                id = std::to_string(std::stoi(object.substr(0, underscorePos))); // may throw, idc
                name = object.substr(underscorePos + 1);
            }
            dataset->m_objects[id] = name;
        }
    }

    std::ifstream ifs;
    for (const auto &it: std::filesystem::recursive_directory_iterator(dir))
    {
        if (it.is_regular_file())
        {
            // labels
            if (it.path().parent_path().filename() == "labels")
            {
                ifs.open(it.path().string());
                if (ifs.is_open())
                {
                    dataset->m_labels[it.path().filename()] = std::vector<Label>();

                    std::string line;
                    while (std::getline(ifs, line))
                    {
                        dataset->m_labels[it.path().filename()].push_back(Label::parse(line));
                    }
                    ifs.close();
                }
                ifs.close();
            }
            // models
            else if (it.path().parent_path().filename() == "models")
            {
                std::string objectId = util::getObjectId(it.path().parent_path().parent_path().filename());
                std::string modelId;
                std::string angle;

                const std::string &file = it.path().filename();
                size_t pos = file.find_last_of('.');
                std::string baseName = file.substr(0, pos);
                std::stringstream ss(baseName);
                std::string token;
                std::getline(ss, token, '_');
                std::getline(ss, angle, '_');
                std::getline(ss, modelId, '_');
                // modelId = std::to_string(std::stoi(model.modelId)); // should we do this?
                std::string type;
                std::getline(ss, type, '_');

                if (dataset->m_models.find(Dataset::createModelMapKey(objectId, angle, modelId)) != dataset->m_models.end())
                {
                    Model::load(dataset->m_models[Dataset::createModelMapKey(objectId, angle, modelId)], it.path().string(), type);
                }
                else
                {
                    Model newModel;
                    newModel.objectId = objectId;
                    newModel.angle = angle;
                    newModel.modelId = modelId;
                    Model::load(newModel, it.path().string(), type);
                    dataset->m_models[Dataset::createModelMapKey(objectId, angle, modelId)] = newModel;
                }
            }
            else if (it.path().parent_path().filename() == "test_images")
            {
                cv::Mat mat = cv::imread(it.path().string());
                dataset->m_testImages[it.path().filename()] = mat;
            }
        }
    }

    return dataset;
}

Label Label::parse(const std::string &line)
{
    Label label;
    std::istringstream iss(line);
    std::string token;

    iss >> token;
    size_t underscorePos = token.find('_');
    label.objectId = token.substr(0, underscorePos);
    label.objectName = token.substr(underscorePos + 1);

    iss >> label.xmin >> label.ymin >> label.xmax >> label.ymax;

    return label;
}

std::string Label::toString(const Label &label)
{
    return label.objectId + "_" + label.objectName + " " +
           std::to_string(label.xmin) + " " + std::to_string(label.ymin) + " " +
           std::to_string(label.xmax) + " " + std::to_string(label.ymax);
}

Model Model::load(Model &model, const std::string &file, std::string &type)
{
    cv::Mat mat = cv::imread(file);
    if (type == "color")
    {
        model.color = mat;
    }
    else if (type == "mask")
    {
        model.mask = mat;
    }
    else
    {
        std::cerr << "unknown type: " << type << " file: " << file << std::endl;
        throw;
    }

    return model;
}
