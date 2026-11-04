#include "tutorialui.h"

namespace fs = std::filesystem;

void ExampleMarkdownFormatCallback(const ImGui::MarkdownFormatInfo& markdownFormatInfo_, bool start_){
    ImGui::defaultMarkdownFormatCallback( markdownFormatInfo_, start_ );

    switch( markdownFormatInfo_.type ){
      case ImGui::MarkdownFormatType::HEADING: {
          if( markdownFormatInfo_.level == 2 )
          {
              if( start_ )
              {
                  ImGui::PushStyleColor( ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_TextDisabled] );
              }
              else
              {
                  ImGui::PopStyleColor();
              }
          }
          break;
      }
      default: {
          break;
      }
    }
}

void TutorialUI::SlideshowWindow(){
    static ImGui::MarkdownConfig mdConfig;
    mdConfig.linkCallback = NULL;
    mdConfig.tooltipCallback = NULL;
    mdConfig.imageCallback = NULL;
    mdConfig.linkIcon = NULL;

    mdConfig.userData = NULL;
    mdConfig.formatCallback = ExampleMarkdownFormatCallback;

    ImGui::SetNextWindowSize(ImVec2(1920.0f, 1080.0f), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;

    if(ImGui::Begin("Presentation", nullptr, flags)){

      ImVec2 child_size = ImVec2(1800.0f, 900.0f);
      ImVec2 avail_size = ImGui::GetContentRegionAvail();
      ImVec2 start_pos = ImGui::GetCursorPos();

      float off_x = (avail_size.x - child_size.x) * 0.5f;
      float off_y = (avail_size.y - child_size.y) * 0.5f;

      if(off_x > 0.0f) ImGui::SetCursorPosX(start_pos.x + off_x);
      if(off_y > 0.0f) ImGui::SetCursorPosY(start_pos.y + off_y);

      ImGui::BeginChild("markdown", child_size, ImGuiChildFlags_Borders);
      ImGui::Markdown(currentSlide.content.c_str(), currentSlide.content.length(), mdConfig);
      ImGui::EndChild();

      if(ImGui::Button("Anterior")){
        if(currentSlide.id > 0){
          currentSlide = slides[currentSlide.id - 1];
        }
      }

      const char* right_label = "Proximo";
      ImGuiStyle& style = ImGui::GetStyle();
      float button_width = ImGui::CalcTextSize(right_label).x + (style.FramePadding.x * 2.0f);

      float target_x = ImGui::GetWindowContentRegionMax().x - button_width;

      ImGui::SameLine(target_x);
      if(ImGui::Button(right_label)){
        if(currentSlide.id < slides.size() - 1){
          currentSlide = slides[currentSlide.id + 1];
        }
      }
    }
    ImGui::End();

    return;
}

TutorialUI::TutorialUI(){
  slides = {};
  currentSlide = {0, ""};
}

void TutorialUI::LoadSlide(const std::string path){
  Slide slide;
  std::string line;
  std::ifstream file(path);

  if(!file.is_open()){
    std::cout << "ERROR: couldn't open file!" << std::endl;
    return;
  }

  slide.id = slides.size();
  while(getline(file, line)){
    slide.content += line + "\n";
  }

  if(file.eof()){
    std::cout << "Reached the end of file: " + path << std::endl;
    slides.push_back(slide);
  }
  else {
    std::cout << "ERROR: error while reading file!" << std::endl;
    file.close();
    return;
  }

  std::cout << "Number of slides stored: " << slides.size() << std::endl;
  file.close();
}

void TutorialUI::LoadContent(){
  fs::path slides_dir = "./slides";

  if(fs::exists(slides_dir) && fs::is_directory(slides_dir)){
    std::cout << "Accessing slides directory: " << fs::absolute(slides_dir) << std::endl;
    for(const auto& entry : fs::directory_iterator(slides_dir)){
      LoadSlide(entry.path().string());
    }
  }
  else {
    std::cout << "Couldn't find slides directory: " + slides_dir.string() << std::endl;
    return;
  }
}

void TutorialUI::Initiate(){
  LoadContent();
  currentSlide = slides[0];
}
