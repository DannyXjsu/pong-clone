# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

#from clang.cindex import Config
#Config.set_library_path("/usr/bin/clang")

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'Pong Clone'
copyright = '2025, DannyXjsu'
author = 'DannyXjsu'
release = 'v1.0'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = ['hawkmoth', 'hawkmoth.ext.napoleon' , 'sphinx_rtd_theme']

templates_path = ['_templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']



# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'sphinx_rtd_theme'
#html_css_files = ['css/dark.css'] # Crude dark mode
html_static_path = ['_static']

import os
hawkmoth_root = os.path.abspath('../src/')
hawkmoth_compiler = 'gcc'
hawkmoth_clang = ['-lSDL3', '-O2']
