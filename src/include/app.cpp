#include "app.h"

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

void LinkCallback( ImGui::MarkdownLinkCallbackData data_ );
inline ImGui::MarkdownImageData ImageCallback( ImGui::MarkdownLinkCallbackData data_ );

static ImFont* H1 = NULL;
static ImFont* H2 = NULL;
static ImFont* H3 = NULL;

static ImGui::MarkdownConfig mdConfig; 

inline ImGui::MarkdownImageData ImageCallback( ImGui::MarkdownLinkCallbackData data_ ){
    // In your application you would load an image based on data_ input. Here we just use the imgui font texture.
    #ifdef IMGUI_HAS_TEXTURES // used to detect dynamic font capability
        ImTextureID image = ImGui::GetIO().Fonts->TexRef.GetTexID();
    #else
        ImTextureID image = ImGui::GetIO().Fonts->TexID;
    #endif
    // > C++14 can use ImGui::MarkdownImageData imageData{ true, false, image, ImVec2( 40.0f, 20.0f ) };
    ImGui::MarkdownImageData imageData;
    imageData.isValid =         true;
    imageData.useLinkCallback = false;
    imageData.user_texture_id = image;
    imageData.size =            ImVec2( 40.0f, 20.0f );

    // For image resize when available size.x > image width, add
    ImVec2 const contentSize = ImGui::GetContentRegionAvail();
    if( imageData.size.x > contentSize.x )
    {
        float const ratio = imageData.size.y/imageData.size.x;
        imageData.size.x = contentSize.x;
        imageData.size.y = contentSize.x*ratio;
    }

    return imageData;
}

void ExampleMarkdownFormatCallback( const ImGui::MarkdownFormatInfo& markdownFormatInfo_, bool start_ )
{
    // Call the default first so any settings can be overwritten by our implementation.
    // Alternatively could be called or not called in a switch statement on a case by case basis.
    // See defaultMarkdownFormatCallback definition for furhter examples of how to use it.
    ImGui::defaultMarkdownFormatCallback( markdownFormatInfo_, start_ );        
       
    switch( markdownFormatInfo_.type )
    {
    // example: change the colour of heading level 2
    case ImGui::MarkdownFormatType::HEADING:
    {
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
    default:
    {
        break;
    }
    }
}

void Markdown( const std::string& markdown_ )
{
    // You can make your own Markdown function with your prefered string container and markdown config.
    // > C++14 can use ImGui::MarkdownConfig mdConfig{ LinkCallback, NULL, ImageCallback, ICON_FA_LINK, { { H1, true }, { H2, true }, { H3, false } }, NULL };
    mdConfig.linkCallback =         NULL;
    mdConfig.tooltipCallback =      NULL;
    mdConfig.imageCallback =        ImageCallback;
    mdConfig.linkIcon =             NULL;

    mdConfig.userData =             NULL;
    mdConfig.formatCallback =       ExampleMarkdownFormatCallback;
    ImGui::Markdown( markdown_.c_str(), markdown_.length(), mdConfig );
}

void MarkdownExample()
{
    const std::string markdownText = u8R"(
# H1 Header: Text and Links
You can add [links like this one to enkisoftware](https://www.enkisoftware.com/) and lines will wrap well.
You can also insert images ![image alt text](image identifier e.g. filename)
Horizontal rules:
***
___
*Emphasis* and **strong emphasis** change the appearance of the text.
## H2 Header: indented text.
  This text has an indent (two leading spaces).
    This one has two.
### H3 Header: Lists
  * Unordered lists
    * Lists can be indented with two extra spaces.
  * Lists can have [links like this one to Avoyd](https://www.avoyd.com/) and *emphasized text*
)";
    Markdown( markdownText );
}

App::App(){
  window = NULL;
}

void App::Initiate(){
  if(SDL_Init(SDL_INIT_VIDEO) < 0){
    std::cout << "SDL could not initialize! SDL_ERROR: " << SDL_GetError() << std::endl;
  }

  window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if(window == NULL){
    std::cout << "Window could not be created! SDL_ERROR: " << SDL_GetError() << std::endl;
  }
}

void App::Run(){
  SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
  SDL_GLContext sdlContext = SDL_GL_CreateContext(window);
  SDL_Event event;
  bool quit = false;

  SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
  SDL_UpdateWindowSurface(window);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

  ImGui_ImplSDL2_InitForOpenGL(window, sdlContext);
  ImGui_ImplOpenGL3_Init();

  while(quit == false){
    while(SDL_PollEvent(&event)){
      ImGui_ImplSDL2_ProcessEvent(&event);
      if(event.type == SDL_QUIT){
        quit = true;
        std::cout << "SDL Window closed." << std::endl;
      }
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    ImGui::ShowDemoWindow();
    MarkdownExample();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    SDL_GL_SwapWindow(window);
  }
}

void App::Destroy(){
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

  SDL_DestroyWindow(window);
  SDL_Quit();
}


