#include "../Model/model.h"
namespace s21 {

    class Controller {
        Controller(){model = new Model;}
        ~Controller(){delete model;}
        std::pair<std::vector<double>, std::vector<unsigned>> GetPair(std::string filename);
        std::pair<unsigned ,unsigned> GetModelSize(){
            return model->GetSize();
        }
    private:
        Model* model;
    };
    }