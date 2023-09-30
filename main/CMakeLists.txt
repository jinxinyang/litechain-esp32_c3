idf_component_register(SRCS "http_request_example_main.c"
                    INCLUDE_DIRS ".")
                    
                    
# 设置包含文件夹路径
set(INCLUDE_DIR "../litechain")

# 递归搜索所有头文件
file(GLOB_RECURSE HEADER_FILES "${INCLUDE_DIR}/*.h")

# 递归搜索所有源文件
file(GLOB_RECURSE SOURCE_FILES "${INCLUDE_DIR}/*.c" "${INCLUDE_DIR}/*.cpp")

# 将头文件添加到组件包含路径中
include_directories(${HEADER_FILES})

# 将源文件添加到组件中
target_sources(${COMPONENT_TARGET} PRIVATE ${SOURCE_FILES})
