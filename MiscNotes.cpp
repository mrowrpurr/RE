// auto wideProcessName = Util::GetWideCharPtr(processName);

// // AllocConsole();
// // FILE* f;
// // freopen_s(&f, "CONOUT$", "w", stdout);
// // DLLInjection::MODULE_BASE = (uintptr_t)GetModuleHandle(wideProcessName);

// // Call your stuff!
// try {
//     Injected_DLL_Main();
// } catch (const std::exception& e) {
//     std::cout << "Exception: " << e.what() << std::endl;
// } catch (...) {
//     std::cout << "Unknown Exception" << std::endl;
// }

// MessageBoxA(0, "Close to eject .dll", "Close to eject .dll", MB_OK);
// fclose(f);
// FreeConsole();
// FreeLibraryAndExitThread(module, 0);
