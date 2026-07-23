# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(quiesink)

# 13.3" E Ink Spectra 6, Color ePaper Display
idf_build_set_property(COMPILE_DEFINITIONS "BOARD_SCREEN_COMBO=510" APPEND)

# Seeed Studio EE02
idf_build_set_property(COMPILE_DEFINITIONS "USE_XIAO_EPAPER_DISPLAY_BOARD_EE02=1" APPEND)
# Arduino D* aliases missing from the registry-packaged esp32s3 variant.
idf_build_set_property(COMPILE_DEFINITIONS "D8=${CONFIG_QUIESINK_PIN_D8}" APPEND)
idf_build_set_property(COMPILE_DEFINITIONS "D10=${CONFIG_QUIESINK_PIN_D10}" APPEND)
