project(
    'implot',
    'cpp',
    version: '0.14', 
    license: 'MIT'
)

include_dirs = include_directories('.')
sources = files(
  'implot.cpp',
  'implot_demo.cpp',
  'implot_items.cpp'
)

imgui_proj = subproject('imgui')
imgui_dep = imgui_proj.get_variable('imgui_dep')

implot = library(
    'implot',
    sources,
    dependencies: [imgui_dep],
    include_directories: include_dirs
)

implot_dep = declare_dependency(include_directories:include_dirs, link_with: implot)
