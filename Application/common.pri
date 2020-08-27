PROJECT_ROOT_PATH = $${PWD}/../Build

CONFIG(debug, debug|release) {
    BUILD_FLAG = debug
    LIB_SUFFIX = d
} else {
    BUILD_FLAG = release
}

# Store intermedia stuff comewhere else
BUILD_PATH = $${PROJECT_ROOT_PATH}/$${BUILD_FLAG}/$${TARGET}
RCC_DIR = $${BUILD_PATH}/rcc
UI_DIR = $${BUILD_PATH}/ui
UI_HEADERS_DIR = $${BUILD_PATH}/ui
UI_SOURCES_DIR = $${BUILD_PATH}/ui
MOC_DIR = $${BUILD_PATH}/moc
OBJECTS_DIR = $${BUILD_PATH}/obj

# Включаем С++11 для всех платформ
CONFIG += c++11

QMAKE_CXXFLAGS += -Wall
QMAKE_CXXFLAGS += -Wno-undef

win32 {
    DEFINES += WIN32_LEAN_AND_MEAN
}
