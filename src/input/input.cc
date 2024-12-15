#include "input.h"

#include <Vector2.hpp>

#include <algorithm>

namespace fow {

    void Input::Zoom(RCamera2D* camera, float zoom_factor, float min_zoom_bound, float max_zoom_bound) {

        RVector2 screen_mouse_pos = GetMousePosition();

        RVector2 world_pos_before = camera->GetScreenToWorld(screen_mouse_pos);

        float zoom = camera->GetZoom() + zoom_factor;

        zoom = std::clamp(zoom, min_zoom_bound, max_zoom_bound);

        camera->SetZoom(zoom);

        RVector2 world_pos_after = camera->GetScreenToWorld(screen_mouse_pos);

        RVector2 delta = world_pos_before - world_pos_after;
        camera->SetTarget(delta + camera->GetTarget());
    }

    void Input::DragScreen(RCamera2D* camera) {
        RVector2 delta = GetMouseDelta();
        delta *= -1.0f / camera->GetZoom();
        camera->SetTarget(delta + camera->GetTarget());
    }

}