# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(hello_world)

FILE(GLOB app_sources src/*.c src/*.s)
target_sources(app PRIVATE ${app_sources})

# Code relocation
#zephyr_code_relocate(FILES src/data.s LOCATION EXTFLASH_TEXT_DATA_BSS NOCOPY)
