
cmake_minimum_required(VERSION 3.4.1)

#设置头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/include)

#设置FFmpeg库路径变量
#CMAKE_CURRENT_SOURCE_DIR,指的是当前处理的 CMakeLists.txt 所在的路径，CMAKE_SOURCE_DIR，不论采用何种编译方式,都是工程顶层目录

set(FFMPEG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/${ANDROID_ABI})

#添加avcodec
add_library(avcodec STATIC IMPORTED)
set_target_properties(avcodec PROPERTIES IMPORTED_LOCATION ${FFMPEG_DIR}/libavcodec.a)

#添加avfilter
add_library(avfilter STATIC IMPORTED)
set_target_properties(avfilter PROPERTIES IMPORTED_LOCATION ${FFMPEG_DIR}/libavfilter.a)

#添加avformat
add_library(avformat STATIC IMPORTED)
set_target_properties(avformat PROPERTIES IMPORTED_LOCATION ${FFMPEG_DIR}/libavformat.a)

#添加avutil
add_library(avutil STATIC IMPORTED)
set_target_properties(avutil PROPERTIES IMPORTED_LOCATION ${FFMPEG_DIR}/libavutil.a)

add_library(aac STATIC IMPORTED)
set_target_properties(aac PROPERTIES IMPORTED_LOCATION ${FFMPEG_DIR}/libfdk-aac.a)

add_library(mp3lame STATIC IMPORTED)
set_target_properties(mp3lame PROPERTIES IMPORTED_LOCATION ${FFMPEG_DIR}/libmp3lame.a)

add_library(postproc STATIC IMPORTED)
set_target_properties(postproc PROPERTIES IMPORTED_LOCATION ${FFMPEG_DIR}/libpostproc.a)

#添加swresample
add_library(swresample STATIC IMPORTED)
set_target_properties(swresample PROPERTIES IMPORTED_LOCATION ${FFMPEG_DIR}/libswresample.a)

#添加swscale
add_library(swscale STATIC IMPORTED)
set_target_properties(swscale PROPERTIES IMPORTED_LOCATION ${FFMPEG_DIR}/libswscale.a)

add_library(aacenc STATIC IMPORTED)
set_target_properties(aacenc PROPERTIES IMPORTED_LOCATION ${FFMPEG_DIR}/libvo-aacenc.a)

add_library(x264 STATIC IMPORTED)
set_target_properties(x264 PROPERTIES IMPORTED_LOCATION ${FFMPEG_DIR}/libx264.a)

add_library( audioencoder
        STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/audio_encoder.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/AudioEncoder.cpp
        )

find_library( log-lib log )

target_link_libraries( audioencoder
        android
        avcodec
        avfilter
        avformat
        avutil
        aac
        mp3lame
        postproc
        swresample
        swscale
        aacenc
        x264
        ${log-lib} )