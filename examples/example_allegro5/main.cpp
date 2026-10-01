#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "imgui.h"
#include "imgui_impl_allegro5.h"
#include "workspace_ui.h"

int main(int, char**)
{
    if (!al_init())
        return 1;
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();

    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    ALLEGRO_DISPLAY* display = al_create_display(1280, 800);
    if (display == nullptr)
        return 1;
    al_set_window_title(display, "Sabaat");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    if (queue == nullptr)
    {
        al_destroy_display(display);
        return 1;
    }
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark();
    ImGui_ImplAllegro5_Init(display);

    bool running = true;
    while (running)
    {
        ALLEGRO_EVENT event;
        while (al_get_next_event(queue, &event))
        {
            ImGui_ImplAllegro5_ProcessEvent(&event);
            if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                running = false;
            if (event.type == ALLEGRO_EVENT_DISPLAY_RESIZE)
            {
                ImGui_ImplAllegro5_InvalidateDeviceObjects();
                al_acknowledge_resize(display);
                ImGui_ImplAllegro5_CreateDeviceObjects();
            }
        }

        ImGui_ImplAllegro5_NewFrame();
        ImGui::NewFrame();
        RenderWorkspace();
        ImGui::Render();

        al_clear_to_color(al_map_rgb(30, 30, 30));
        ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());
        al_flip_display();
    }

    ImGui_ImplAllegro5_Shutdown();
    ImGui::DestroyContext();
    al_destroy_event_queue(queue);
    al_destroy_display(display);
    return 0;
}
