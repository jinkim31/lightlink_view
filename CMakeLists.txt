cmake_minimum_required(VERSION 3.12)
project(lightlink_view)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
Set(FETCHCONTENT_QUIET FALSE)
FetchContent_Declare(
        imgui_bundle
        GIT_REPOSITORY https://github.com/pthom/imgui_bundle.git
        GIT_PROGRESS TRUE
        GIT_TAG main
)
FetchContent_MakeAvailable(imgui_bundle)
list(APPEND CMAKE_MODULE_PATH ${IMGUIBUNDLE_CMAKE_PATH})
include(imgui_bundle_add_app)
set(IMGUI_BUNDLE_FETCH_OPENCV OFF)
set(HELLOIMGUI_WIN32_NO_CONSOLE OFF)

imgui_bundle_add_app(lightlink_view
        main.cpp
        custom_widgets.cpp
        view/master_view.cpp
        )