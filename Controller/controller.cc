#include "controller.h"

namespace s21{
    std::pair<double*, unsigned*> Controller::GetPair(std::string filename){
        model->Parse(filename);
        return model->GetArr();
    }
}