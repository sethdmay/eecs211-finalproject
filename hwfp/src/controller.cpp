#include "controller.h"

using namespace ge211;



Controller::Controller()
        : model_(2)
        , view_(model_)
        , m_pos_(0,0)
{ }

void Controller::draw(Sprite_set& sprites)
{
    view_.draw(sprites);
}

Dimensions Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

std::string Controller::initial_window_title() const
{
    return view_.initial_window_title();
}

void Controller::on_key_down(ge211::Key key) {

    if(key.code() == '\n')
        model_.placeTile(std::make_shared<Tile>(key.code() - 32), 3, 3);
}

// TODO: Add or remove if necessary

void Controller::on_mouse_down(ge211::Mouse_button, ge211::Position pos) {
    if(pos.y >= view_.rack_offset_.height)
        if(mouse_to_rack(pos) == view_.selected_tile_loc)
            view_.select_tile(-1);
        else
            view_.select_tile(mouse_to_rack(pos));
    else if(view_.selected_tile_loc >= 0)
        view_.move_tile(mouse_to_board(pos));
    else {
        view_.select_tile(mouse_to_board(pos));
    }

}

const int Controller::mouse_to_rack(ge211::Position pos) {
    return (pos - view_.rack_offset_).x/(view_.tile_side_length_ + view_.margin_);
}

const ge211::Position Controller::mouse_to_board(ge211::Position pos) {
    return {pos.x/(view_.space_side_length_ + view_.margin_),
            pos.y/(view_.space_side_length_ + view_.margin_)};
}

void Controller::on_start() {
    background_color = {153, 0, 0};
}


