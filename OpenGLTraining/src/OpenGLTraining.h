#pragma once

void ImGuiExample(bool& show_demo_window, bool& show_another_window, ImVec4& clear_color, ImGuiIO& io);

void ImGuiShowAnotherWindowExample(bool& show_another_window);

void ImGuiTranslationExample(glm::vec3& translation, int id);

void ImGuiObjectColorExample(ImVec4& obj_color);

void DrawObject(Shader& shader, glm::vec3& translation, glm::mat4& proj, glm::mat4& view, ImVec4& obj_color, Renderer& renderer, VertexArray& va, IndexBuffer& ib);
