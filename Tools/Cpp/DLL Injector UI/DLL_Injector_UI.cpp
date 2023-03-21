#include <Logging.h>
SetLogFilePath("DLL_Injector_UI.log");
//

#include <DLL_Injector.h>
#include <SimpleIni.h>
#include <StringFormatting.h>
#include <UserInterface.h>

#include <filesystem>

constexpr auto ProjectRoot = "../../../../..";
constexpr auto IniFileName = "dll_injector.ini";

struct InjectableDLL {
    std::string Name;
    std::string DLL;
    std::string EXE;
};

std::vector<InjectableDLL> GetDLLs() {
    std::vector<InjectableDLL> DLLs;

    CSimpleIniA ini;
    auto iniLoadError = ini.LoadFile(string_format("{}/{}", ProjectRoot, IniFileName).c_str());

    if (iniLoadError < 0) return DLLs;

    CSimpleIniA::TNamesDepend DLLsNames;
    ini.GetAllSections(DLLsNames);

    for (auto& DLLName : DLLsNames) {
        InjectableDLL DLL;
        DLL.Name = DLLName.pItem;

        auto dllRelativePathToProject = ini.GetValue(DLLName.pItem, "DLL", "");
        auto dllAbsolutePath =
            std::filesystem::absolute(string_format("{}/{}", ProjectRoot, dllRelativePathToProject)
            );

        DLL.DLL = std::filesystem::absolute(std::filesystem::path{dllAbsolutePath}).string();
        DLL.EXE = ini.GetValue(DLLName.pItem, "EXE", "");
        DLLs.push_back(DLL);
    }

    return DLLs;
}

UI_Main {
    UserInterface::Run([](auto& app) {
        auto injectableDLLs = GetDLLs();

        app.SetTitle("Choose DLL to Inject");
        app.SetHeight(15 * injectableDLLs.size());
        app.SetWidth(500);

        for (auto& injectableDLL : injectableDLLs) {
            app.AddButton(injectableDLL.Name, [&, injectableDLL]() {
                DLL_Injector::InjectDLL(injectableDLL.EXE, injectableDLL.DLL);
            });
        }
    });
}