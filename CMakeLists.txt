cmake_minimum_required(VERSION 3.21)

project(LongPetUiDemo VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Gui Widgets Svg)

qt_add_executable(LongPetUiDemo WIN32
    src/main.cpp
    src/DemoWindow.h
    src/DemoWindow.cpp
    src/widgets/VisualTokens.h
    src/widgets/PetFaceWidget.h
    src/widgets/PetFaceWidget.cpp
    src/widgets/VisualComponents.h
    src/widgets/VisualComponents.cpp
    src/pages/HomePage.h
    src/pages/HomePage.cpp
    src/pages/CompanionPage.h
    src/pages/CompanionPage.cpp
    src/pages/ConversationPage.h
    src/pages/ConversationPage.cpp
    src/pages/CarePage.h
    src/pages/CarePage.cpp
    src/pages/ReminderPage.h
    src/pages/ReminderPage.cpp
    src/pages/ReminderEditPage.h
    src/pages/ReminderEditPage.cpp
    src/pages/SettingsPage.h
    src/pages/SettingsPage.cpp
    src/pages/EmergencyPage.h
    src/pages/EmergencyPage.cpp
    src/pages/SleepPage.h
    src/pages/SleepPage.cpp
    src/pages/EngineeringPage.h
    src/pages/EngineeringPage.cpp
    src/pages/UiGalleryPage.h
    src/pages/UiGalleryPage.cpp
    resources/resources.qrc
)

target_include_directories(LongPetUiDemo PRIVATE src)

target_link_libraries(LongPetUiDemo PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Svg
)

set_target_properties(LongPetUiDemo PROPERTIES
    WIN32_EXECUTABLE TRUE
)
