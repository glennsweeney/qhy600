project(
    'qhy',
    ['cpp'],
    default_options: [
        'cpp_std=c++20',
        'b_pie=true',
        'default_library=static',
        'warning_level=3'
    ],
    license : 'MIT'
)

# Note: also hard-coded above, because the variable cannot be defined before project()
project_name = 'qhy'


extra_warning_flags=[
    '-Wdouble-promotion'
]

extra_compiler_flags = [
]

add_project_arguments(extra_warning_flags, language:'cpp')
add_project_arguments(extra_compiler_flags, language:'cpp')


########################
##### File Sources #####
########################

lib_includes = include_directories(
    'include',
    'qhy_sdk/usr/local/include'
)

lib_sources = files(
    'src/qhy.cpp',
    'src/camera.cpp'
)

cli_sources = files(
    'cli/main.cpp'
)

test_sources = files(
    'test/test_qhy.cpp'
)

gui_includes = include_directories(
    'gui'
)

gui_sources = files(
    'gui/main.cpp',
    'gui/application.cpp'
)


#######################
##### Subprojects #####
#######################

spdlog_proj = subproject(
    'spdlog',
    default_options: [
        'tests=false',
        'compile_library=true'
    ]
)
spdlog_dep = spdlog_proj.get_variable('spdlog_dep')

gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_dep')
gtest_main_dep = gtest_proj.get_variable('gtest_main_dep')

glfw_proj = subproject('glfw')
glfw_dep = glfw_proj.get_variable('glfw_dep')

imgui_proj = subproject('imgui')
imgui_dep = imgui_proj.get_variable('imgui_dep')

implot_proj = subproject('implot')
implot_dep = implot_proj.get_variable('implot_dep')


###################
##### QHY SDK #####
###################

cpp = meson.get_compiler('cpp')
libdir = meson.current_source_dir() + '/qhy_sdk/usr/local/lib/'
message('HIHIHI')
message(libdir)
qhy_sdk_dep = cpp.find_library('qhyccd', dirs : libdir)


#########################
##### Build Library #####
#########################

qhy = library(
    project_name,
    lib_sources,
    include_directories: lib_includes,
    dependencies : [
        spdlog_dep,
        qhy_sdk_dep
    ]
)

qhy_dep = declare_dependency(
    link_with: qhy,
    include_directories : lib_includes
)


#####################
##### Build CLI #####
#####################

cli = executable(
    project_name + '_cli',
    cli_sources,
    dependencies : [
        qhy_dep,
        spdlog_dep
    ]
)


#######################
##### Build Tests #####
#######################

unit_tests = executable(
    project_name + '_test',
    test_sources,
    dependencies : [
        gtest_dep,
        gtest_main_dep,
        qhy_dep
    ]
)
test('Unit Tests', unit_tests)


#####################
##### Build GUI #####
#####################=

gui = executable(
    project_name + '_gui',
    gui_sources,
    include_directories : gui_includes,
    dependencies : [
        glfw_dep,
        imgui_dep,
        implot_dep,
        spdlog_dep,
        qhy_dep
    ]
)
