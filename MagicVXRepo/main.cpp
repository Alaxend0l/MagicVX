// Dear ImGui: standalone example application for DirectX 9
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include <d3d9.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <tchar.h>
#include "Global.h"
#include "GameThreading.h"

// Data
static LPDIRECT3D9              g_pD3D = NULL;
static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void ResetDevice();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void DisplayIntValue(Proxy<int>&, std::string, bool);
void DisplayIntValue(Proxy<int>&, std::string);
void DisplayFloatValue(Proxy<float>&, std::string, bool);
void DisplayFloatValue(Proxy<float>&, std::string);

// Main code
int main(int, char**)
{
    // Create application window
    //ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("ImGui Example"), NULL };
    ::RegisterClassEx(&wc);
    HWND hwnd = ::CreateWindow(wc.lpszClassName, _T("Dear ImGui DirectX9 Example"), WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);

    // Initialize Direct3D
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClass(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    // Our state
    bool show_demo_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    GameThreading gameThreading;

    const char* modeItems[] = {
        "Mission",
        "Challenge",
        "Drag Race",
        "Battle",
        "Joyride",
        "Score War",
        "Play Gear Hunt",
        "Make Gear Hunt",
        "Sandbox"
    };

    const char* missionItems[] = {
        "Mission 1",
        "Mission 2",
        "Mission 3",
        "Mission 4",
        "Mission 5",
        "Mission 6",
        "Mission 7",
        "Mission 8",
        "Mission 9",
        "Mission 10",
        "Mission 11",
        "Mission 12",
        "Mission 13",
        "Mission 14",
    };

    const char* challengeItems[] = {
        "Challenge 1",
        "Challenge 2",
        "Challenge 3",
        "Challenge 4",
        "Challenge 5",
        "Challenge 6",
        "Challenge 7",
        "Challenge 8",
        "Challenge 9",
        "Challenge 10",
        "Challenge 11",
        "Challenge 12",
        "Challenge 13",
        "Challenge 14",
        "Challenge 15",
        "Challenge 16",
        "Challenge 17",
        "Challenge 18",
    };

    const char* raceItems[] = {
        "Downtown Race",
        "Desert Race",
        "Ghost Town Race",
        "Bay Street Race",
        "Underworld Race",
        "Glacier Race"
    };

    const char* battleItems[] = {
        "Downtown",
        "Turbine City",
        "Warehouse District",
        "Combustion Caldera",
        "Sewer Pipe Arena",
        "Crankshaft Docks",
        "Treadwell Plaza",
        "Underworld Arena"
    };

    const char* worldItems[] = {
        "Monument City",
        "Turbine Sands",
        "Crankshaft Bay",
        "Burnout Glacier",
        "Underworld"
    };

    const char* carItems[] = {
        "Twin Mill 2",
        "At-A-Tude",
        "Overbored 454",
        "MS-T Suzuka",
        "Super Tuned",
        "Sooo Fast",
        "Flashfire",
        "Mega-Duty",
        "Muscle Tone",
        "Sho-Stopper",
        "Hammered Coupe",
        "Jaded",
        "Way 2 Fast",
        "Deora II",
        "Hyper Mite",
        "Power Pistons",
        "Evil Twin",
        "Surf Crate",
        "Rigor Motor",
        "Lakester",
        "Splittin' Image 2",
        "Greased Lightnin'",
        "Hyperliner",
        "Maelstrom",
        "Sol-Aire CX4",
        "Surfin' School Bus",
        "Vulture",
        "Arachnorod",
        "Krazy 8s",
        "Shadow Jet",
        "HW Prototype 12",
        "Power Rocket",
        "Jet Threat 3.0"
    };

    const char* weaponItems[] = {
        "Ripper Wheels",
        "Armor Repair",
        "Oil Drum",
        "Laser Cannon",
        "Sonic Boom",
        "Atom Blaster",
        "Freon Bomb",
        "Energy Shield",
        "Jet Boosters",
        "Super Zapper",
        "Magnet Mine",
        "Doom Disks"
    };

    const char* difficultyItems[]{
        "Easy",
        "Normal",
        "Hard",
        "Very Hard"
    };

    const char* deadWeightItems[]{
        "No Deadweight",
        "Money Bag",
        "Uranium",
        "Time Bomb",
        "Data Disk",
        "Temporal Transmission",
        "Volcanic Gas Collector"
    };

    const char* gearHuntItems[256];

    char GHC_Title[128] = "";
    char GHC_Filename[128] = "";
    char GHC_Author[128] = "";
    char GHC_Description[5192] = "";

    bool mvx_window_main = true;
    bool mvx_window_settings = false;
    bool mvx_window_customLaunch = false;
    bool mvx_window_globalWatch = false;
    bool mvx_window_gearHuntSave = false;

    bool mvx_window_players = false;

    bool mvx_window_xpc_main = false;

    int gearHuntSelected = 0;
    int gearHuntLastSelected = 0;
    int gearHuntAmount = 0;
    
    std::string carText;
    std::string carText2;
    std::string weaponText;
    std::string weaponText2;
    std::string worldText;
    std::string worldText2;

    mainSettings.LoadSettings();

    // Main loop
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            continue;
        }

        // Start the Dear ImGui frame
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        if (mvx_window_main)
        {
            ImGui::Begin("Main Menu", &mvx_window_main, ImGuiWindowFlags_MenuBar);
            ImGui::PushItemWidth(ImGui::GetFontSize() * -12);
            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("Menu"))
                {
                    ImGui::MenuItem("Test", NULL, &show_demo_window);
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Tools"))
                {
                    ImGui::MenuItem("Global Watch", NULL, &mvx_window_globalWatch);
                    ImGui::MenuItem("Player Monitor", NULL, &mvx_window_players);
                    //ImGui::MenuItem("Style Editor", NULL, &show_app_style_editor);
                    //ImGui::MenuItem("About Dear ImGui", NULL, &show_app_about);
                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("XPC"))
                {
                    ImGui::MenuItem("View XPC", NULL, &mvx_window_xpc_main);
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }
            if (ImGui::Button("Settings"))
            {
                mvx_window_settings = true;
            }

            if (ImGui::Button("Launch VX"))
            {
                gameThreading.LaunchThread(false);
            }
            if (ImGui::Button("Launch VX Custom"))
            {
                mvx_window_customLaunch = true;
                //gameThreading.LaunchThread(true);
            }
            ImGui::Text(mainSettings.GetExeDirectory().c_str());
            ImGui::End();
        }

        if (mvx_window_settings)
        {
            ImGui::Begin("Settings", &mvx_window_settings);

            if (ImGui::CollapsingHeader("MagicVX Pathing"))
            {
                //ImGui::text
                //ImGui::InputText("Velocity X Path", mainSettings.gameDirectory, 256);
                ImGui::Text(mainSettings.gameDirectory.c_str());
                if (ImGui::Button("Get New Path"))
                {
                    OPENFILENAME ofn;
                    char szFile[100];
                    ZeroMemory(&ofn, sizeof(ofn));
                    ofn.lStructSize = sizeof(ofn);
                    ofn.hwndOwner = NULL;
                    ofn.lpstrFile = szFile;
                    ofn.lpstrFile[0] = '\0';
                    ofn.nMaxFile = sizeof(szFile);
                    ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
                    ofn.nFilterIndex = 1;
                    ofn.lpstrFileTitle = NULL;
                    ofn.nMaxFileTitle = 0;
                    ofn.lpstrInitialDir = NULL;
                    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
                    GetOpenFileName(&ofn);

                    mainSettings.gameDirectory = (ofn.lpstrFile);
                }
            }

            if (ImGui::CollapsingHeader("Original Settings"))
            {
                ImGui::Checkbox((mainSettings.ColorDepth ? "32 Bit Color" : "16 Bit Color"), &mainSettings.ColorDepth);
                ImGui::Checkbox("No Vehicle Particles", &mainSettings.VehicleParticles);
                ImGui::Checkbox("No Antialiasing", &mainSettings.AntiAliasing);
                ImGui::Checkbox("Limit World Particles", &mainSettings.WorldParticles);
                ImGui::Checkbox("Short Draw Distance", &mainSettings.DrawDistance);
                ImGui::Checkbox("Low Geometry Detail", &mainSettings.GeometryDetail);
                ImGui::Checkbox("Disable Movies", &mainSettings.DisableMovies);
                const char* textureItems[] = { "Trilinear", "Bilinear", "None" };
                ImGui::Combo("Texture Filtering", &mainSettings.TextureFiltering, textureItems, IM_ARRAYSIZE(textureItems));
            }

            if (ImGui::CollapsingHeader("Enhancements"))
            {
                const char* screenModeItems[] = { "Fullscreen", "Windowed" };
                ImGui::Combo("Screen Mode", &mainSettings.ScreenMode, screenModeItems, IM_ARRAYSIZE(screenModeItems));
                ImGui::InputInt2("Resolution", mainSettings.Resolution);
                ImGui::Checkbox("Change Field of View", &mainSettings.PatchFOV);
                if (mainSettings.PatchFOV)
                {
                    ImGui::SliderInt("FOV", &mainSettings.ScreenFOV, 60, 179);
                }
                ImGui::SliderInt("Music Volume", &mainSettings.MusicVol, 0, 100);
                ImGui::SliderInt("Sound Volume", &mainSettings.SFXVol, 0, 100);
            }

            if (ImGui::Button("Save Settings"))
            {
                mainSettings.SaveSettings();
            }

            ImGui::End();
        }

        if (mvx_window_customLaunch)
        {
            ImGui::Begin("Custom Launch", &mvx_window_customLaunch, ImGuiWindowFlags_MenuBar);

            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("File"))
                {
                    ImGui::MenuItem("Save", NULL);
                    ImGui::MenuItem("Save As...", NULL);
                    ImGui::MenuItem("Load", NULL);
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Modify"))
                {
                    ImGui::Combo("Difficulty", &customLaunchSettings.Difficulty, difficultyItems, IM_ARRAYSIZE(difficultyItems));
                    ImGui::MenuItem("Enable All Cheats", NULL, &customLaunchSettings.Sandbox_EnableAllCheats);
                    ImGui::MenuItem("Armor Repair Glitch", NULL, &customLaunchSettings.ArmorRepairGlitch);
                    ImGui::MenuItem("Simple Physics", NULL, &customLaunchSettings.Sandbox_SimplifyPhysics);
                    ImGui::MenuItem("Zero Gravity", NULL, &customLaunchSettings.Sandbox_ZeroGravity);
                    
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Tools"))
                {
                    //ImGui::MenuItem("Metrics/Debugger", NULL, &show_app_metrics);
                    //ImGui::MenuItem("Style Editor", NULL, &show_app_style_editor);
                    //ImGui::MenuItem("About Dear ImGui", NULL, &show_app_about);
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }

            ImGui::Combo("Game Mode", &customLaunchSettings.Mode, modeItems, IM_ARRAYSIZE(modeItems));
            


            const char* winConditionItems[] = { "Rounds", "Wins" };
            const char* offOnRandom[] = { "Off", "On", "Random" };
            switch (customLaunchSettings.Mode)
            {
            case 0: //Mission
                ImGui::Combo("Mission", &customLaunchSettings.Act, missionItems, IM_ARRAYSIZE(missionItems));
                break;
            case 1: //Challenge
                ImGui::Combo("Car", &customLaunchSettings.Car, carItems, IM_ARRAYSIZE(carItems));
                ImGui::Combo("Weapon", &customLaunchSettings.Weapon, weaponItems, IM_ARRAYSIZE(weaponItems));
                ImGui::Combo("Challenge", &customLaunchSettings.Act, challengeItems, IM_ARRAYSIZE(challengeItems));
                break;
            case 2: //Drag Race
                ImGui::Combo("Car", &customLaunchSettings.Car, carItems, IM_ARRAYSIZE(carItems));
                ImGui::Combo("Weapon", &customLaunchSettings.Weapon, weaponItems, IM_ARRAYSIZE(weaponItems));
                ImGui::Combo("Race", &customLaunchSettings.Act, raceItems, IM_ARRAYSIZE(raceItems));
                ImGui::Text("");
                ImGui::InputInt("Time In Seconds", &customLaunchSettings.DragRace_Time);
                ImGui::SliderInt("Opponents", &customLaunchSettings.DragRace_Opponents, 1, 3);
                ImGui::Combo("Win Condition", &customLaunchSettings.DragRace_RoundsOrWins, winConditionItems, IM_ARRAYSIZE(winConditionItems));
                ImGui::SliderInt(winConditionItems[customLaunchSettings.DragRace_RoundsOrWins], &customLaunchSettings.DragRace_Rounds, 1, 9);
                ImGui::Combo("Gadgets", &customLaunchSettings.DragRace_Gadgets, offOnRandom, IM_ARRAYSIZE(offOnRandom));
                ImGui::Checkbox("Item Reset", &customLaunchSettings.DragRace_ItemReset);
                break;
            case 3: //Battle
                ImGui::Combo("Car", &customLaunchSettings.Car, carItems, IM_ARRAYSIZE(carItems));
                ImGui::Combo("Weapon", &customLaunchSettings.Weapon, weaponItems, IM_ARRAYSIZE(weaponItems));
                ImGui::Combo("Arena", &customLaunchSettings.Act, battleItems, IM_ARRAYSIZE(battleItems));
                ImGui::Text("");
                ImGui::InputInt("Time In Seconds", &customLaunchSettings.Battle_Time);
                ImGui::SliderInt("Opponents", &customLaunchSettings.Battle_Opponents, 1, 3);
                ImGui::Combo("Win Condition", &customLaunchSettings.Battle_RoundsOrWins, winConditionItems, IM_ARRAYSIZE(winConditionItems));
                ImGui::SliderInt(winConditionItems[customLaunchSettings.Battle_RoundsOrWins], &customLaunchSettings.Battle_Rounds, 1, 9);
                ImGui::Combo("Gadgets", &customLaunchSettings.Battle_Gadgets, offOnRandom, IM_ARRAYSIZE(offOnRandom));
                ImGui::Checkbox("Gadget Respawn", &customLaunchSettings.Battle_GadgetRespawn);
                ImGui::SliderInt("Kills To Win", &customLaunchSettings.Battle_Kills, 1, 30);
                break;
            case 4: //Joyride
                ImGui::Combo("Car", &customLaunchSettings.Car, carItems, IM_ARRAYSIZE(carItems));
                ImGui::Combo("Weapon", &customLaunchSettings.Weapon, weaponItems, IM_ARRAYSIZE(weaponItems));
                ImGui::Combo("World", &customLaunchSettings.Act, worldItems, IM_ARRAYSIZE(worldItems));
                break;
            case 5: //Score War
                ImGui::Combo("Car", &customLaunchSettings.Car, carItems, IM_ARRAYSIZE(carItems));
                ImGui::Combo("Weapon", &customLaunchSettings.Weapon, weaponItems, IM_ARRAYSIZE(weaponItems));
                ImGui::Combo("Arena", &customLaunchSettings.Act, battleItems, IM_ARRAYSIZE(battleItems));
                ImGui::Text("");
                ImGui::InputInt("Time In Seconds", &customLaunchSettings.Score_Time);
                ImGui::SliderInt("Opponents", &customLaunchSettings.Score_Opponents, 1, 3);
                ImGui::Combo("Win Condition", &customLaunchSettings.Score_RoundsOrWins, winConditionItems, IM_ARRAYSIZE(winConditionItems));
                ImGui::SliderInt(winConditionItems[customLaunchSettings.Score_RoundsOrWins], &customLaunchSettings.Score_Rounds, 1, 9);
                ImGui::Combo("Gadgets", &customLaunchSettings.Score_Gadgets, offOnRandom, IM_ARRAYSIZE(offOnRandom));
                ImGui::Checkbox("Gadget Respawn", &customLaunchSettings.Score_GadgetRespawn);
                ImGui::InputInt("Target Score", &customLaunchSettings.Score_Target);
                ImGui::InputInt("Points Per Kill", &customLaunchSettings.Score_PointsPerKill);
                break;
            case 6: //Play Gear Hunt
                //ImGui::Combo("World", &customLaunchSettings.Act, worldItems, IM_ARRAYSIZE(worldItems));
                
                ImGui::Text("");
                if (ImGui::Button("Refresh List"))
                {
                    GH_Manager.inFolder = GH_Manager.CollectGearHunts(GH_Manager.GetExeDirectory() + "\\GearHunts\\");
                    for (int i = 0; i < 256; i++)
                    {
                        if (GH_Manager.inFolder.size() > i)
                        {
                            gearHuntItems[i] = GH_Manager.inFolder[i].c_str();
                        }
                        else
                        {
                            gearHuntItems[i] = "";
                            gearHuntAmount = i;
                            break;
                        }
                    }

                    gearHuntLastSelected = -1;
                }
                ImGui::ListBox("Gear Hunts", &gearHuntSelected, gearHuntItems, gearHuntAmount, 10);
                ImGui::Text(GH_Manager.Title.c_str());
                ImGui::Text(("Made by: " + GH_Manager.Creator).c_str());
                
                if (gearHuntLastSelected != gearHuntSelected)
                {
                    GH_Manager.LoadInfo(GH_Manager.inFolder[gearHuntSelected]);

                    if (GH_Manager.ForceCar) customLaunchSettings.Car = GH_Manager.CarChoice;
                    if (GH_Manager.ForceWeapon) customLaunchSettings.Weapon = GH_Manager.WeaponChoice;
                    customLaunchSettings.Act = GH_Manager.World;

                    customLaunchSettings.GearHunt_File = GH_Manager.inFolder[gearHuntSelected];
                    gearHuntLastSelected = gearHuntSelected;
                }
                if (GH_Manager.ForceCar)
                {
                    carText = "Forced Car: ";
                    carText2 = (carItems[GH_Manager.CarChoice]);
                    carText += carText2;
                    ImGui::Text(carText.c_str());
                }
                else
                {
                    ImGui::Combo("Car", &customLaunchSettings.Car, carItems, IM_ARRAYSIZE(carItems));
                }
                if (GH_Manager.ForceWeapon)
                {
                    weaponText = "Forced Weapon: ";
                    weaponText2 = (weaponItems[GH_Manager.WeaponChoice]);
                    weaponText += weaponText2;
                    ImGui::Text(weaponText.c_str());
                }
                else
                {
                    ImGui::Combo("Weapon", &customLaunchSettings.Weapon, weaponItems, IM_ARRAYSIZE(weaponItems));
                }
                worldText = "World: ";
                worldText2 = (worldItems[GH_Manager.World]);
                worldText += worldText2;
                ImGui::Text(worldText.c_str());
                ImGui::TextWrapped(GH_Manager.Description.c_str());
                
                break;
            case 7: //Make Gear Hunt
                ImGui::Combo("Car", &customLaunchSettings.Car, carItems, IM_ARRAYSIZE(carItems));
                ImGui::Combo("Weapon", &customLaunchSettings.Weapon, weaponItems, IM_ARRAYSIZE(weaponItems));
                ImGui::Combo("World", &customLaunchSettings.Act, worldItems, IM_ARRAYSIZE(worldItems));
                break;
            case 8: //Sandbox
                ImGui::Combo("Car", &customLaunchSettings.Car, carItems, IM_ARRAYSIZE(carItems));
                ImGui::Combo("Weapon", &customLaunchSettings.Weapon, weaponItems, IM_ARRAYSIZE(weaponItems));
                ImGui::Combo("World", &customLaunchSettings.Act, worldItems, IM_ARRAYSIZE(worldItems));
                break;
            default:
                break;
            }
            if (ImGui::Button("Start"))
            {
                if (customLaunchSettings.Mode == 7)
                {
                    //Set up stuff for making gear hunts.
                    mvx_window_gearHuntSave = true;

                    GH_Manager.CarChoice = customLaunchSettings.Car;
                    GH_Manager.WeaponChoice = customLaunchSettings.Weapon;
                    GH_Manager.World = customLaunchSettings.Act;
                    GH_Manager.SimplePhysics = customLaunchSettings.Sandbox_SimplifyPhysics;
                    GH_Manager.ZeroGravity = customLaunchSettings.Sandbox_ZeroGravity;
                }
                gameThreading.LaunchThread(true);
            }

            ImGui::End();
        }

        if (mvx_window_globalWatch)
        {
            ImGui::Begin("Global Watch", &mvx_window_globalWatch);

            ImGui::Checkbox("Pipe Connected: ", &pipeConnect);
             
            ImGui::End();
        }

        if (mvx_window_gearHuntSave)
        {
            ImGui::Begin("Gear Hunt Save", &mvx_window_gearHuntSave);

            ImGui::InputText("Title", GHC_Title, 256);
            ImGui::InputText("Filename", GHC_Filename, 256);
            ImGui::InputText("Author", GHC_Author, 256);
            ImGui::InputTextMultiline("Description", GHC_Description, 5192);

            ImGui::Checkbox("Force Car", &GH_Manager.ForceCar);
            ImGui::Checkbox("Force Weapon", &GH_Manager.ForceWeapon);
            ImGui::Checkbox("Force Deadweight", &GH_Manager.ForceDeadWeight);
            if (GH_Manager.ForceDeadWeight)
            {
                ImGui::Combo("Deadweight", &GH_Manager.DeadWeightChoice, deadWeightItems, IM_ARRAYSIZE(deadWeightItems));
            }

            if (ImGui::Button("Save"))
            {
                GH_Manager.Title = GHC_Title;
                GH_Manager.Creator = GHC_Author;
                GH_Manager.Description = GHC_Description;
                GH_Manager.FileName = GHC_Filename;
                gearHuntSave = true;
            }
            
            ImGui::End();
        }

        if (mvx_window_players)
        {
            ImGui::Begin("Player Monitor", &mvx_window_players);

            for (int i = 0; i < 8; i++)
            {
                std::string headerText = "Monitor Player " + std::to_string(i);
                if (player[i].Active)
                {
                    if (ImGui::CollapsingHeader(headerText.c_str()))
                    {
                        std::stringstream ss1;
                        std::stringstream ss2;
                        std::stringstream ss3;

                        ss1 << "Player Address: " << std::hex << player[i].GetBaseAddress();
                        ImGui::Text(ss1.str().c_str());
                        ss2 << "Vehicle Address: " << std::hex << player[i].playerVehicle.GetBaseAddress();
                        ImGui::Text(ss2.str().c_str());

                        DisplayFloatValue(player[i].playerVehicle.currentX, "Position X ##" + std::to_string(i));
                        DisplayFloatValue(player[i].playerVehicle.currentY, "Position Y ##" + std::to_string(i));
                        DisplayFloatValue(player[i].playerVehicle.currentZ, "Position Z ##" + std::to_string(i));

                        DisplayFloatValue(player[i].playerVehicle.rotationX, "Rotation X ##" + std::to_string(i));
                        DisplayFloatValue(player[i].playerVehicle.rotationY, "Rotation Y ##" + std::to_string(i));
                        DisplayFloatValue(player[i].playerVehicle.rotationZ, "Rotation Z ##" + std::to_string(i));
                        DisplayFloatValue(player[i].playerVehicle.rotationW, "Rotation W ##" + std::to_string(i));

                        DisplayIntValue(player[i].playerVehicle.currentHealth, "Current Health ##" + std::to_string(i));
                        DisplayIntValue(player[i].playerVehicle.currentBoost, "Current Boost ##" + std::to_string(i));
                    }
                }
                
            }
            ImGui::End();
        }

        if (mvx_window_xpc_main)
        {
            ImGui::Begin("XPC Loader", &mvx_window_xpc_main);

            if (ImGui::Button("Load File"))
            {
                OPENFILENAME ofn;
                char szFile[100];
                ZeroMemory(&ofn, sizeof(ofn));
                ofn.lStructSize = sizeof(ofn);
                ofn.hwndOwner = NULL;
                ofn.lpstrFile = szFile;
                ofn.lpstrFile[0] = '\0';
                ofn.nMaxFile = sizeof(szFile);
                ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
                ofn.nFilterIndex = 1;
                ofn.lpstrFileTitle = NULL;
                ofn.nMaxFileTitle = 0;
                ofn.lpstrInitialDir = NULL;
                ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

                if (GetOpenFileName(&ofn) == TRUE)
                {
                    xpcHandle.FileContents = xpcHandle.ReadFile(ofn.lpstrFile);
                    xpcHandle.SetUpDatabase();
                }

                
            }

            if (xpcHandle.loaded)
            {
                ImGui::Text(xpcHandle.filePath.c_str());
                ImGui::Text((std::to_string(xpcHandle.size) + " Bytes").c_str());
                ImGui::Text((std::to_string(xpcHandle.entries) + " Entries").c_str());

                for (int i = 0; i < xpcHandle.entries; i++)
                {
                    std::string sectorTitle = ("Sector " + std::to_string(i));
                    if (ImGui::TreeNode(sectorTitle.c_str()))
                    {

                        std::stringstream ss1;
                        ss1 << "Address: 0x" << std::hex << xpcHandle.Headers[i].Address_File;
                        ImGui::Text(ss1.str().c_str());
                        ImGui::Text(("Object Type: " + std::to_string(xpcHandle.Headers[i].xpcTableEntry.objectType)).c_str());
                        ImGui::Text(("Object Index: " + std::to_string(xpcHandle.Headers[i].xpcTableEntry.objectIndex)).c_str());
                        ImGui::Text(("Unknown 2[0]: " + std::to_string(xpcHandle.Headers[i].xpcTableEntry.unknown2[0])).c_str());
                        ImGui::Text(("Unknown 2[1]: " + std::to_string(xpcHandle.Headers[i].xpcTableEntry.unknown2[1])).c_str());
                        ImGui::Text(("Stream Size: " + std::to_string(xpcHandle.Headers[i].xpcTableEntry.streamSize)).c_str());
                        ImGui::Text(("Offset: " + std::to_string(xpcHandle.Headers[i].xpcTableEntry.offset)).c_str());
                        std::stringstream ss3;
                        std::stringstream ss4;
                        std::stringstream ss5;
                        std::stringstream ss6;

                        if (ImGui::TreeNode((sectorTitle + " Contents").c_str()))
                        {
                            ImGui::Text(("DataPointer00: " + std::to_string(xpcHandle.Headers[i].xpcTopHeader.AddressPtr0)).c_str());
                            ImGui::Text(("DataPointer01: " + std::to_string(xpcHandle.Headers[i].xpcTopHeader.AddressPtr1)).c_str());
                            ImGui::Text(("DataPointer02: " + std::to_string(xpcHandle.Headers[i].xpcTopHeader.AddressPtr2)).c_str());
                            ImGui::Text(("Count: " + std::to_string(xpcHandle.Headers[i].xpcTopHeader.entryCnt)).c_str());
                            ImGui::Text(("UNKNOWN_INT_03: " + std::to_string(xpcHandle.Headers[i].xpcTopHeader.unknownInt3)).c_str());
                            ImGui::Text(("UNKNOWN_INT_04: " + std::to_string(xpcHandle.Headers[i].xpcTopHeader.unknownInt4)).c_str());
                            ImGui::Text(("UNKNOWN_INT_05: " + std::to_string(xpcHandle.Headers[i].xpcTopHeader.unknownInt5)).c_str());
                            ImGui::Text(("TexturePtr: " + std::to_string(xpcHandle.Headers[i].xpcTopHeader.AddressPtr6)).c_str());
                            ImGui::Text(("TextureCnt: " + std::to_string(xpcHandle.Headers[i].xpcTopHeader.textureCnt)).c_str());
                            ImGui::Text(("Count2: " + std::to_string(xpcHandle.Headers[i].xpcTopHeader.entryCnt2)).c_str());
                            ImGui::Text(("UNKNOWN_INT_08: " + std::to_string(xpcHandle.Headers[i].xpcTopHeader.unknownInt8)).c_str());
                            ImGui::Text(("UNKNOWN_INT_09: " + std::to_string(xpcHandle.Headers[i].xpcTopHeader.unknownInt9)).c_str());
                            ImGui::Text(("UNKNOWN_INT_10: " + std::to_string(xpcHandle.Headers[i].xpcTopHeader.unknownInt10)).c_str());
                            ImGui::Text(("UNKNOWN_INT_11: " + std::to_string(xpcHandle.Headers[i].xpcTopHeader.unknownInt11)).c_str());
                            ImGui::Text(("UNKNOWN_INT_12: " + std::to_string(xpcHandle.Headers[i].xpcTopHeader.unknownInt12)).c_str());
                            ImGui::Text(("UNKNOWN_INT_13: " + std::to_string(xpcHandle.Headers[i].xpcTopHeader.unknownInt13)).c_str());
                            ImGui::Text(("UNKNOWN_INT_14: " + std::to_string(xpcHandle.Headers[i].xpcTopHeader.unknownInt14)).c_str());
                            ImGui::Text(("UNKNOWN_INT_15: " + std::to_string(xpcHandle.Headers[i].xpcTopHeader.unknownInt15)).c_str());
                            ImGui::Text(("UNKNOWN_INT_16: " + std::to_string(xpcHandle.Headers[i].xpcTopHeader.unknownInt16)).c_str());
                            ImGui::Text(("UNKNOWN_INT_17: " + std::to_string(xpcHandle.Headers[i].xpcTopHeader.unknownInt17)).c_str());
                            ImGui::Text(("UNKNOWN_INT_18: " + std::to_string(xpcHandle.Headers[i].xpcTopHeader.musicAddress)).c_str());
                            
                            ImGui::TreePop();
                        }

                        if (ImGui::TreeNode((sectorTitle + " SFX").c_str()))
                        {
                            for (int j = 0; j < xpcHandle.Headers[i].xpcTopHeader.entryCnt; j++)
                            {
                                std::stringstream ss2;
                                ss2 << "Entry " << std::to_string(j) << ": " << std::hex << xpcHandle.Headers[i].entryAddresses[j] << " Size: " << std::hex << xpcHandle.Headers[i].carEntries[j].size;
                                ImGui::Text(ss2.str().c_str());
                            }
                            ImGui::TreePop();
                        }
                        switch (xpcHandle.Headers[i].Type)
                        {
                        case 0:
                            
                            ss3 << "Mesh Pointer: " << std::hex << xpcHandle.Headers[i].Address_Unknown0;
                            ss4 << "Data Pointer 1: " << std::hex << xpcHandle.Headers[i].Address_Unknown1;
                            ss5 << "Data Pointer 2: " << std::hex << xpcHandle.Headers[i].Address_Unknown2;
                            ss6 << "Texture Pointer: " << std::hex << xpcHandle.Headers[i].Address_Texture;
                            ImGui::Text(ss3.str().c_str());
                            ImGui::Text(ss4.str().c_str());
                            ImGui::Text(ss5.str().c_str());
                            ImGui::Text(ss6.str().c_str());
                            
                            break;
                        case 4: //World
                            ss3 << "SFX Pointer: " << std::hex << xpcHandle.Headers[i].Address_SFX;
                            ss4 << "Music Pointer: " << std::hex << xpcHandle.Headers[i].Address_Music;
                            ss5 << "Collectable Pointer: " << std::hex << xpcHandle.Headers[i].Address_Unknown2;
                            ImGui::Text(ss3.str().c_str());
                            ImGui::Text(ss4.str().c_str());
                            ImGui::Text(ss5.str().c_str());

                            if (ImGui::TreeNode((sectorTitle + " Music").c_str()))
                            {
                                for (int j = 0; j < xpcHandle.Headers[i].xpcRiffHeader.count; j++)
                                {
                                    std::stringstream ss2;
                                    ss2 << "Riff " << std::to_string(j) << ": " << std::hex << xpcHandle.Headers[i].entryAddressesRiff[j] << " Size: " << std::hex << xpcHandle.Headers[i].riffEntries[j].size;
                                    ImGui::Text(ss2.str().c_str());
                                }
                                ImGui::TreePop();
                            }

                            if (ImGui::TreeNode((sectorTitle + " Collectables").c_str()))
                            {
                                for (int j = 0; j < xpcHandle.Headers[i].xpcTopHeader.unknownInt4; j++)
                                {
                                    std::stringstream ss2;
                                    ss2 << "Collectable " << std::to_string(j) << ": " << std::hex << xpcHandle.Headers[i].entryAddressesThings[j] << " TextureID: " << std::to_string(xpcHandle.Headers[i].thingHeaders[j].textureID) << " Flag: " << std::to_string(xpcHandle.Headers[i].thingHeaders[j].flag);
                                    ImGui::Text(ss2.str().c_str());
                                }
                                ImGui::TreePop();
                            }
                            
                            break;
                        }

                        
                        ImGui::TreePop();
                    }
                }
            }
            
            ImGui::End();
        }

        /*
        */
        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);



        // Rendering
        ImGui::EndFrame();
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x * 255.0f), (int)(clear_color.y * 255.0f), (int)(clear_color.z * 255.0f), (int)(clear_color.w * 255.0f));
        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }
        HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

        // Handle loss of D3D9 device
        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
            ResetDevice();
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClass(wc.lpszClassName, wc.hInstance);

    return 0;
}

// Helper functions

bool CreateDeviceD3D(HWND hWnd)
{
    if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
        return false;

    // Create the D3DDevice
    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
    //g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
    if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
        return false;

    return true;
}

void CleanupDeviceD3D()
{
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
    if (g_pD3D) { g_pD3D->Release(); g_pD3D = NULL; }
}

void ResetDevice()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
    if (hr == D3DERR_INVALIDCALL)
        IM_ASSERT(0);
    ImGui_ImplDX9_CreateDeviceObjects();
}

void DisplayIntValue(Proxy<int>& value, std::string label, bool lock = true)
{
    if (lock)
    {
        string lockLabel = "##lock" + label;
        ImGui::Checkbox(lockLabel.c_str(), &value.lock);
        ImGui::SameLine();
    }
    ImGui::InputInt(label.c_str(), &value.guiValue);
}

void DisplayIntValue(Proxy<int>& value, std::string label)
{
    DisplayIntValue(value, label, true);
}

void DisplayFloatValue(Proxy<float>& value, std::string label, bool lock = true)
{
    if (lock)
    {
        string lockLabel = "##lock" + label;
        ImGui::Checkbox(lockLabel.c_str(), &value.lock);
        ImGui::SameLine();
    }
    ImGui::InputFloat(label.c_str(), &value.guiValue);
}

void DisplayFloatValue(Proxy<float>& value, std::string label)
{
    DisplayFloatValue(value, label, true);
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            g_d3dpp.BackBufferWidth = LOWORD(lParam);
            g_d3dpp.BackBufferHeight = HIWORD(lParam);
            ResetDevice();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}
