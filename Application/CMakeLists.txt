cmake_minimum_required(VERSION 3.16)
project(PLAG)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}")

find_package(Qt6 COMPONENTS Core)
find_package(Qt6 COMPONENTS Gui)
find_package(Qt6 COMPONENTS Sql)
find_package(Qt6 COMPONENTS Network)

qt_add_executable(PLAG WIN32 MACOSX_BUNDLE
	Interfaces/iapplication.h
	Interfaces/icore.h
	Interfaces/ipluginhandler.h
	Sources/application.h
	Sources/application_common.cpp
	Sources/main.cpp
	Sources/pluginhandler.cpp Sources/pluginhandler.h
	Sources/pluginloader.cpp Sources/pluginloader.h
        "res.qrc"
        "Resources/Logo.png"
	"Resources/Logo128.png"
	"Resources/Logo256.png"
	"Resources/Logo512.png"
	"Sources/Main.qml"
	"Sources/OptionButton.qml"
)
target_link_libraries(PLAG PUBLIC
	Qt::Core
	Qt::Gui
	Qt::Network
	Qt::Sql
)

target_compile_options( PLAG PRIVATE -Wall -Wno-undef )

if(NOT IS_CLI_APP)
	find_package(Qt6 COMPONENTS Widgets)
	find_package(Qt6 COMPONENTS QuickWidgets)
	find_package(Qt6 COMPONENTS Qml)
	find_package(Qt6 COMPONENTS Quick)
	target_link_libraries(PLAG PUBLIC
		Qt::Qml
		Qt::Quick
		Qt::QuickWidgets
		Qt::Widgets
	)
endif()

qt6_add_qml_module(QML_StaticLib
	VERSION 1.0
	URI "Plugins"
)

if(ANDROID)
	target_sources(PLAG PUBLIC
		Sources/application_android.cpp
		Sources/pluginloader_android.cpp Sources/pluginloader_android.h
	)
	target_link_libraries(PLAG PUBLIC
		Qt::AndroidExtras
	)
endif()

if(NOT ANDROID)
	target_sources(PLAG PUBLIC
		Sources/application_pc.cpp
	)
endif()

if(WIN32)
	target_compile_definitions(PLAG PUBLIC
		WIN32_LEAN_AND_MEAN
	)
endif()

INSTALL( TARGETS PLAG
	RUNTIME DESTINATION ../Plugins/
)
