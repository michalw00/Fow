#pragma once

#include "Camera2D.hpp"

namespace fow {

    class Input {


    private:
    public:
        void DragScreen(RCamera2D* camera);

        void Zoom(RCamera2D* camera, float zoom_factor, float min_zoom_bound, float max_zoom_bound);
    };

}