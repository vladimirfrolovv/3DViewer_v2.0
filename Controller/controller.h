#include "../Model/model.h"
namespace s21 {

    class Controller {
    public:
        Controller(){model = new Model;}
        ~Controller(){delete model;}
        std::pair<double*, unsigned*> GetPair(std::string filename);
        std::pair<unsigned ,unsigned> GetModelSize();
        void RotateModelX(double angle);
        void RotateModelY(double angle);
        void RotateModelZ(double angle);
        void SetModelScale(double scale);
        void MoveModel(double value , char axis);
    private:
        Model* model;
    };
    }
