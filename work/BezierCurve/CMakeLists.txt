set(target_ bezierCurve)

FILE(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.*)

FIND_PACKAGE(glfw3 CONFIG REQUIRED)
FIND_PACKAGE(glad CONFIG REQUIRED)

ADD_EXECUTABLE(${target_} ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(${target_} PRIVATE glfw glad::glad)

target_include_directories(${target_}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../Headers
)
