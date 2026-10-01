#pragma once

#include <algorithm>

#include "imgui.h"

inline void RenderWorkspace()
{
    static bool show_left_panel = false;
    static bool show_terminal = true;

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    constexpr ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_MenuBar;

    ImGui::Begin("Sabaat Workspace", nullptr, window_flags);
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("View"))
        {
            ImGui::MenuItem("Left panel", nullptr, &show_left_panel);
            ImGui::MenuItem("Terminal", nullptr, &show_terminal);
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    const ImVec2 available = ImGui::GetContentRegionAvail();
    const float terminal_height = show_terminal
        ? std::min(available.y, std::max(150.0f, available.y * 0.3f))
        : 0.0f;
    const float upper_height = std::max(0.0f, available.y - terminal_height);

    ImGui::BeginChild("Workspace", ImVec2(available.x, upper_height), ImGuiChildFlags_None);
    if (show_left_panel)
    {
        ImGui::BeginChild("LeftPanel", ImVec2(220.0f, 0.0f), ImGuiChildFlags_Borders);
        ImGui::TextUnformatted("Explorer");
        ImGui::Separator();
        ImGui::EndChild();
        ImGui::SameLine();
    }
    ImGui::BeginChild("MainArea", ImVec2(0.0f, 0.0f), ImGuiChildFlags_None);
    ImGui::EndChild();
    ImGui::EndChild();

    if (show_terminal)
    {
        ImGui::BeginChild("Terminal", ImVec2(available.x, terminal_height), ImGuiChildFlags_Borders);
        ImGui::TextUnformatted("Terminal");
        ImGui::Separator();
        ImGui::TextUnformatted("$ Terminal ready.");
        ImGui::EndChild();
    }
    ImGui::End();
}