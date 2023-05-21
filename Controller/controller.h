#include "../Model/model.h"
namespace s21 {

    class Controller {
    public:
        Controller(){model = new Model;}
        ~Controller(){delete model;}
        std::pair<double*, unsigned*> GetPair(std::string filename);
        std::pair<unsigned ,unsigned> GetModelSize(){
            return model->GetSize();
        }
    private:
        Model* model;
    };
    }
