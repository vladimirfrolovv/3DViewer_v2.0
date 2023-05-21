#include "controller.h"

namespace s21{
    std::pair<double*, unsigned*> Controller::GetPair(std::string filename){
        model->Parse(filename);
        return model->GetArr();
    }
    std::pair<unsigned ,unsigned> Controller::GetModelSize(){
        return model->GetSize();
    }
    void Controller::RotateModelX(double angle){
        model->RotationX(angle);
    }
    void Controller::RotateModelY(double angle){
        model->RotationY(angle);
    }
    void Controller::RotateModelZ(double angle){
        model->RotationZ(angle);
    }
    void Controller::SetModelScale(double scale){
        model->SetScale(scale);
    }
    void Controller::MoveModel(double value, char axis) {
        model->Move(value,axis);
    }
}