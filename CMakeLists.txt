cmake_minimum_required(VERSION 3.10)
project(2048_Projesi)

set(CMAKE_CXX_STANDARD 17)

# SFML'in projenin içindeki yerini belirle
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
set(SFML_DIR "${CMAKE_SOURCE_DIR}/SFML2/SFML-3.1.0")

# Header dosyalarını dahil et
include_directories("${SFML_DIR}/include")

# Kütüphane dosyalarının yolunu göster
link_directories("${SFML_DIR}/lib")

add_executable(2048_Game main.cpp oyunMantigi.cpp)

# Kütüphaneleri bağla (Windows/MinGW için statik veya dinamik)
target_link_libraries(2048_Game PRIVATE 
    sfml-graphics 
    sfml-window 
    sfml-system
)