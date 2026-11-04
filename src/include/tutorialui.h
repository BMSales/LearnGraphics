#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_markdown.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Slide {
  unsigned int id;
  std::string content;
};

class TutorialUI {
  public:
    TutorialUI();

    void SlideshowWindow();
    void Initiate();
    // void StartSlideShow();
    // void EndSlideShow();
    // void NextSlide();
    // void PreviousSlide();
    //
    // int Initiate();
    // void Destroy();
  private:
    std::vector<Slide> slides;
    Slide currentSlide;

    void LoadSlide(const std::string);
    void LoadContent();
};
