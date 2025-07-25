cmake_minimum_required(VERSION 3.13)

if (NOT DEFINED VERSION)
    set(VERSION 1.2.2)
endif ()
#set(CMAKE_BUILD_TYPE "Debug")
#project(application)
#add_subdirectory(../3rdparty/docx docx_binary_dir)
#add_subdirectory(../3rdparty/QtXlsxWriter)
configure_file(environments.h.in environments.h @ONLY)
set (EXE_NAME deepin-log-viewer)

configure_file(config.h.in config.h @ONLY)




set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
#set(CMAKE_CXX_FLAGS "-g -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")#${EXE_NAME}
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--as-needed -fPIE")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++11")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pie")
#安全测试加固编译参数
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -z relro -z now -z noexecstack -pie")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -z relro -z now -z noexecstack -pie")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -fstack-protector-all")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -fstack-protector-all")

if(CMAKE_COVERAGE_ARG STREQUAL "CMAKE_COVERAGE_ARG_ON")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -fprofile-arcs -ftest-coverage")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -fprofile-arcs -ftest-coverage")
endif()

set(APP_RES_DIR "assets")
#安全测试加固编译参数
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -z relro -z now -z noexecstack -pie")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -z relro -z now -z noexecstack -pie")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -fstack-protector-all")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -fstack-protector-all")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIE")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIE")
if (${CMAKE_SYSTEM_PROCESSOR} MATCHES "sw_64")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mieee")
endif ()

if (NOT (${CMAKE_BUILD_TYPE} MATCHES "Debug"))
    add_definitions(-DQT_NO_DEBUG_OUTPUT)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")



     execute_process(COMMAND deepin-desktop-ts-convert "init" "assets/deepin-log-viewer.desktop.tmp" "../translations/desktop"
                                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} RESULT_VARIABLE desktop_transinit_var OUTPUT_VARIABLE desktop_transinit_out ERROR_VARIABLE desktop_transinit_error)
     execute_process(COMMAND deepin-desktop-ts-convert "desktop2ts" "assets/deepin-log-viewer.desktop.tmp" "../translations/desktop"
                                                                       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} RESULT_VARIABLE desktop_trans_desktop2ts_var OUTPUT_VARIABLE desktop_trans_desktop2ts_out ERROR_VARIABLE desktop_trans_desktop2ts_error)
     execute_process(COMMAND deepin-desktop-ts-convert "ts2desktop" "assets/deepin-log-viewer.desktop.tmp" "../translations/desktop" "assets/deepin-log-viewer.desktop"
           WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} RESULT_VARIABLE desktop_trans_desktop2ts_var OUTPUT_VARIABLE desktop_trans_desktop2ts_out ERROR_VARIABLE desktop_trans_desktop2ts_error)

    # # generate qm files
    # execute_process(COMMAND bash "assets/translate_generation.sh"
    #                 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} RESULT_VARIABLE trans_var OUTPUT_VARIABLE trans_out ERROR_VARIABLE trans_error)
    #             message("trans_var ${trans_var} ")#trans_out ${trans_out} trans_error ${trans_error}
    execute_process(COMMAND deepin-policy-ts-convert "init" "assets/com.deepin.pkexec.logViewerAuth.policy.tmp" "../translations/policy/auth"
                                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} RESULT_VARIABLE policy2ts_init_var OUTPUT_VARIABLE policy2ts_init_out ERROR_VARIABLE policy2ts_init_error)

    execute_process(COMMAND deepin-policy-ts-convert "policy2ts" "assets/com.deepin.pkexec.logViewerAuth.policy.tmp" "../translations/policy/auth"
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} RESULT_VARIABLE policy2ts_var OUTPUT_VARIABLE policy2ts_out ERROR_VARIABLE policy2ts_error)
                 message("policy2ts_var ${policy2ts_var} policy2ts_out ${policy2ts_out} policy2ts_error ${policy2ts_error}")
    execute_process(COMMAND deepin-policy-ts-convert "ts2policy" "assets/com.deepin.pkexec.logViewerAuth.policy.tmp" "../translations/policy/auth" "assets/com.deepin.pkexec.logViewerAuth.policy"
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} RESULT_VARIABLE ts2policy_var OUTPUT_VARIABLE ts2policy_out ERROR_VARIABLE ts2policy_error)
                 message("ts2policy_var ${ts2policy_var} ts2policy_out ${ts2policy_out} ts2policy_error ${ts2policy_error}")
#    execute_process(COMMAND cp "assets/com.deepin.pkexec.logViewerAuth.policy.tmp" "assets/com.deepin.pkexec.logViewerAuth.policy"
#                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} RESULT_VARIABLE cp_var OUTPUT_VARIABLE cp_out ERROR_VARIABLE cp_error)
#                   message("cp_var ${cp_var} cp_out ${cp_out} cp_error ${cp_error}")

 execute_process(COMMAND deepin-policy-ts-convert "init" "assets/com.deepin.pkexec.logViewerTruncate.policy.tmp" "../translations/policy/truncate"
                                                      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} RESULT_VARIABLE policy2ts_var OUTPUT_VARIABLE policy2ts_out ERROR_VARIABLE policy2ts_error)
execute_process(COMMAND deepin-policy-ts-convert "policy2ts" "assets/com.deepin.pkexec.logViewerTruncate.policy.tmp" "../translations/policy/truncate"
                                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} RESULT_VARIABLE policy2ts_var OUTPUT_VARIABLE policy2ts_out ERROR_VARIABLE policy2ts_error)
                                message("policy2ts_var ${policy2ts_var} policy2ts_out ${policy2ts_out} policy2ts_error ${policy2ts_error}")
 execute_process(COMMAND deepin-policy-ts-convert "ts2policy" "assets/com.deepin.pkexec.logViewerTruncate.policy.tmp" "../translations/policy/truncate" "assets/com.deepin.pkexec.logViewerTruncate.policy"
                                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} RESULT_VARIABLE ts2policy_var OUTPUT_VARIABLE ts2policy_out ERROR_VARIABLE ts2policy_error)
                                message("ts2policy_var ${ts2policy_var} ts2policy_out ${ts2policy_out} ts2policy_error ${ts2policy_error}")
#execute_process(COMMAND cp "assets/com.deepin.pkexec.logViewerTruncate.policy.tmp" "assets/com.deepin.pkexec.logViewerTruncate.policy"
#                                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} RESULT_VARIABLE cp_var OUTPUT_VARIABLE cp_out ERROR_VARIABLE cp_error)
#  message("cp_var ${cp_var} cp_out ${cp_out} cp_error ${cp_error}")
endif ()

add_definitions(-DUSE_POLKIT -DENABLE_INACTIVE_DISPLAY)
# Find the library
find_package(PkgConfig REQUIRED)
find_package(RapidJSON)
find_package(Boost)
find_package(XercesC)
find_package(ZLIB)
find_package(PolkitQt${QT_DESIRED_VERSION}-1)
# IMPORTED_TARGET failed to work for some of libs under flatpak env

set(qt_required_components Core DBus Gui Network Widgets Concurrent)

if (QT_DESIRED_VERSION MATCHES 6)
    list(APPEND qt_required_components Core5Compat)
else()
    pkg_check_modules(Gsetting REQUIRED gsettings-qt)
endif()
message("   >>> Build with DTK: ${DTK_VERSION_MAJOR}")

find_package(Qt${QT_DESIRED_VERSION} REQUIRED COMPONENTS ${qt_required_components})
find_package(Dtk${DTK_VERSION_MAJOR} COMPONENTS Core Gui Widget REQUIRED)

set(LINK_LIBS
    Qt${QT_DESIRED_VERSION}::Core
    Qt${QT_DESIRED_VERSION}::DBus
    Qt${QT_DESIRED_VERSION}::Gui
    Qt${QT_DESIRED_VERSION}::Network
    Qt${QT_DESIRED_VERSION}::Widgets
    Qt${QT_DESIRED_VERSION}::Concurrent
    Dtk${DTK_VERSION_MAJOR}::Widget
    Dtk${DTK_VERSION_MAJOR}::Core
    Dtk${DTK_VERSION_MAJOR}::Gui
    PolkitQt${QT_DESIRED_VERSION}-1::Agent
)

if (QT_DESIRED_VERSION MATCHES 6)
    list(APPEND LINK_LIBS Qt${QT_DESIRED_VERSION}::Core5Compat)
else()
    list(APPEND LINK_LIBS ${Gsetting_LIBRARIES})
    include_directories(${Gsetting_INCLUDE_DIRS})
endif()

message("XercesC_FOUND ${XercesC_FOUND}")
message("zlib version: " ${ZLIB_LIBRARIES})

list(APPEND LXW_PRIVATE_INCLUDE_DIRS ${ZLIB_INCLUDE_DIRS})

set (APP_CPP_FILES
     main.cpp
     cliapplicationhelper.cpp
     filtercontent.cpp
     displaycontent.cpp
     logcollectormain.cpp
     logfileparser.cpp
     logtreeview.cpp
     journalwork.cpp
     logexportthread.cpp
     utils.cpp
     loglistview.cpp
     logperiodbutton.cpp
     logviewheaderview.cpp
     logviewitemdelegate.cpp
     logiconbutton.cpp
     logspinnerwidget.cpp
     logdetailinfowidget.cpp
     logauththread.cpp
     logapplicationhelper.cpp
     logapplicationparsethread.cpp
     logoocfileparsethread.cpp
     journalbootwork.cpp
     exportprogressdlg.cpp
     logscrollbar.cpp
     logcombox.cpp
     dbusmanager.cpp
     lognormalbutton.cpp
     logapplication.cpp
     sharedmemorymanager.cpp
     dbusproxy/dldbusinterface.cpp
     dbusproxy/dldbushandler.cpp
     logsettings.cpp
     DebugTimeManager.cpp
     wtmpparse.cpp
     logdetailedit.cpp
#     viewsortfilter.cpp
     logallexportthread.cpp
     eventlogutils.cpp
     logbackend.cpp
     logsegementexportthread.cpp
     parsethread/parsethreadbase.cpp
     parsethread/parsethreadkern.cpp
     parsethread/parsethreadkwin.cpp
    )
set (APP_QRC_FILES
assets/resources.qrc
)


set (APP_HEADERS_FILES
    cliapplicationhelper.h
    logcollectormain.h
    displaycontent.h
    logfileparser.h
    filtercontent.h
    structdef.h
    logtreeview.h
    journalwork.h
    logexportwidget.h
    utils.h
    loglistview.h
    logperiodbutton.h
    logviewheaderview.h
    logviewitemdelegate.h
    logiconbutton.h
    logspinnerwidget.h
    logdetailinfowidget.h
    logauththread.h
    logapplicationhelper.h
    logapplicationparsethread.h
    logoocfileparsethread.h
    logdetailedit.h
    wtmpparse.h
    model/log_sort_filter_proxy_model.h
    dbusproxy/dldbusinterface.h
    dbusproxy/dldbushandler.h
#    viewsortfilter.h
    logallexportthread.h
    eventlogutils.h
    logbackend.h
    accessible.h
    logsegementexportthread.h
    parsethread/parsethreadbase.h
    parsethread/parsethreadkern.h
    parsethread/parsethreadkwin.h
    qtcompat.h
    )

# 5. 头文件
# 5.1. 定义函数，用于递归添加头文件
function(include_sub_directories_recursively root_dir)
    if (IS_DIRECTORY ${root_dir})               # 当前路径是一个目录吗，是的话就加入到包含目录
        #message("include dir: " ${root_dir})
        include_directories(${root_dir})
    endif()

    file(GLOB ALL_SUB RELATIVE ${root_dir} ${root_dir}/*) # 获得当前目录下的所有文件，让如ALL_SUB列表中
    foreach(sub ${ALL_SUB})
        if (IS_DIRECTORY ${root_dir}/${sub})
            include_sub_directories_recursively(${root_dir}/${sub}) # 对子目录递归调用，包含
        endif()
    endforeach()
endfunction()

#--------------------libxlsx源码引入---------------------------------
file(GLOB LXW_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/libxlsxwriter/src/*.c)
file(GLOB_RECURSE LXW_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/libxlsxwriter/include *.h)

set (MINIZIP_SOURCES
    ../3rdparty/minizip/ioapi.c
#../3rdparty/minizip/miniunz.c
 ../3rdparty/minizip/minizip.c
../3rdparty/minizip/mztools.c
../3rdparty/minizip/unzip.c
../3rdparty/minizip/zip.c
    )

file(GLOB TMPFILE_SOURCES  ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/tmpfileplus/*.c)
file(GLOB MD5SOURCES   ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/md5/*.c)
#---------------------------------------------
#---------------DOCXFACTORY源码引入----------------------
file(GLOB_RECURSE DOCXFAC_SOURCES  "${PROJECT_SOURCE_DIR}/3rdparty/DocxFactory/src/*.cpp" )
file(GLOB_RECURSE DOCXFAC_SOURCES_C  "${PROJECT_SOURCE_DIR}/3rdparty/DocxFactory/src/*.c" )
#-----------------------------------------------------

#file(GLOB_RECURSE application_source_files "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
#set(CMAKE_INSTALL_PREFIX /usr)
#set(BINDIR binr)
#isEmpty(BINDIR):BINDIR=/usr/bin
#isEmpty(APPDIR):APPDIR=/usr/share/applications
#isEmpty(DSRDIR):DSRDIR=/usr/share/deepin-log-viewer

find_library(ICUIL18N_LIB icui18n)
find_library(ICUUC_LIB icuuc)

#lupdate start
set(TS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../translations")
set(TS_FILES
    "${TS_DIR}/${EXE_NAME}.ts"
)
find_program(LUPDATE_EXECUTABLE lupdate)
foreach(_ts_file ${TS_FILES})
    execute_process(
        COMMAND ${LUPDATE_EXECUTABLE} -recursive ${CMAKE_SOURCE_DIR} -ts ${_ts_file})
endforeach()
#lupdate end

add_executable (${EXE_NAME} ${APP_CPP_FILES}  ${APP_QRC_FILES} ${DOCX_CPP_FILES} ${MINIZIP_SOURCES} ${LXW_SOURCES} ${DOCXFAC_SOURCES} ${DOCXFAC_SOURCES_C} ${TMPFILE_SOURCES} ${MD5SOURCES} )
include_sub_directories_recursively("${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/docx")
include_sub_directories_recursively("${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/libxlsxwriter")
include_sub_directories_recursively("${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/DocxFactory/include")
include_sub_directories_recursively("${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/md5")
include_sub_directories_recursively("${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/minizip")
include_sub_directories_recursively("${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/tmpfileplus")
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories( ${Boost_INCLUDE_DIRS})
include_directories( ${ZLIB_INCLUDE_DIRS})
message("ZLIB_INCLUDE_DIRS ${ZLIB_INCLUDE_DIRS}")
include_directories( ${RapidJSON_INCLUDE_DIRS})
#include_directories(${ImageMagick_INCLUDE_DIRS})
include_directories(${XercesC_INCLUDE_DIRS})

target_link_libraries(${EXE_NAME}  ${LINK_LIBS} -lsystemd -licui18n -licuuc  -ldl -fPIC)
#当binutils>=2.22时，对于链接的静态库链接的静态库，cmake并不会递归链接，所以需要手动链接libxlsxwriter需要的lzlib
target_link_libraries(${EXE_NAME} ${ZLIB_LIBRARIES})
target_link_libraries(${EXE_NAME} ${Boost_LIBRARIES})
target_link_libraries(${EXE_NAME} ${RapidJSON_LIBRARIES})
#target_link_libraries(${EXE_NAME} ${ImageMagick_LIBRARIES})
target_link_libraries(${EXE_NAME} ${XercesC_LIBRARIES})

#target_link_libraries(${EXE_NAME} ${CMAKE_BINARY_DIR}/3rdparty/libxlsxwriter/libxlsxwriter.a)

#target_link_libraries(${EXE_NAME} ${MINIZIP_LIBRARIES})

#target_link_libraries(${EXE_NAME} ${Zint_LIBRARIES})
#target_link_libraries(${EXE_NAME} ${RapidJSON_LIBRARIES})
#install(FILES ${ICUIL18N_LIB} ${ICUUC_LIB} ${SYSTEMD_LIB} DESTINATION lib)
#set(CMAKE_INSTALL_PREFIX /usr)

# translation files
TRANSLATION_GENERATE(QM_FILES ${CMAKE_SOURCE_DIR}/translations)
add_custom_target(${EXE_NAME}_qm_files DEPENDS ${QM_FILES})
add_dependencies(${EXE_NAME} ${EXE_NAME}_qm_files)

# Install translations
install(FILES ${QM_FILES} DESTINATION share/${EXE_NAME}/translations)

file(GLOB DOCXFAC_TEMPLATE "assets/doc_template/*.dfw")
install(FILES assets/deepin-log-viewer.desktop DESTINATION ${CMAKE_INSTALL_PREFIX}/share/applications)
install(FILES ${DOCXFAC_TEMPLATE} DESTINATION ${CMAKE_INSTALL_PREFIX}/share/deepin-log-viewer/DocxTemplate)
install(FILES assets/com.deepin.pkexec.logViewerAuth.policy DESTINATION ${CMAKE_INSTALL_PREFIX}/share/polkit-1/actions)
install(FILES assets/images/deepin-log-viewer.svg
            DESTINATION ${CMAKE_INSTALL_PREFIX}/share/icons/hicolor/scalable/apps/)
install(FILES assets/com.deepin.pkexec.logViewerAuth.policy
                    DESTINATION ${CMAKE_INSTALL_PREFIX}/share/polkit-1/actions)
install(FILES assets/com.deepin.pkexec.logViewerTruncate.policy DESTINATION ${CMAKE_INSTALL_PREFIX}/share/polkit-1/actions)
install(FILES gschema/com.deepin.log.viewer.gschema.xml
                DESTINATION ${CMAKE_INSTALL_PREFIX}/share/glib-2.0/schemas)

# Install files
install(TARGETS ${EXE_NAME} DESTINATION bin)
install(DIRECTORY assets/deepin-log-viewer
                DESTINATION ${CMAKE_INSTALL_PREFIX}/share/deepin-manual/manual-assets/application/)

# Install aduit rule config file.
install(FILES assets/auditRule.conf DESTINATION ${CMAKE_INSTALL_PREFIX}/share/deepin-log-viewer)

# Install cli script deepin-logger
install(FILES assets/deepin-logger DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

# Install log json config file.
install(FILES configs/logconfig/deepin-log-viewer.json DESTINATION ${CMAKE_INSTALL_PREFIX}/share/deepin-log-viewer/deepin-log.conf.d/)

# Install debugmode json config file.
install(FILES configs/debugconfig/org.deepin.log.viewer.json DESTINATION ${CMAKE_INSTALL_PREFIX}/share/deepin-debug-config/deepin-debug-config.d/)

# Install coredump report service&timer
install(FILES ./configs/coredump-reporter.timer ./configs/coredump-reporter.service DESTINATION lib/systemd/user/)

#安装DConfig配置
set(APPID org.deepin.log.viewer)
set(configFile configs/dconfig/org.deepin.log.viewer.json)
if (DEFINED DSG_DATA_DIR)
    if (DTK_VERSION_MAJOR EQUAL "6")
        dtk_add_config_meta_files(APPID ${APPID} FILES ${configFile})
    else()
        dconfig_meta_files(APPID ${APPID} FILES ${configFile})
    endif()
    message("-- DConfig is supported by DTK")
else()
    install(FILES ${configFile} DESTINATION ${CMAKE_INSTALL_PREFIX}/share/dsg/configs/${APPID}/)
    message("-- DConfig is not supported by DTK")
endif()


