from distutils.core import setup, Extension
from Cython.Build import cythonize

modules = [
    Extension(
        "mgeanttrack",
        sources=[
            "/home/rafal/projects/MAPT-clean/python/mgeanttrack.pyx",
        ],
        language="c++",              # generate C++ code
        extra_compile_args=["-std=c++14"],
        include_dirs=["/usr/lib64/root/6.14/include"],
        library_dirs=["/home/rafal/projects/MAPT-clean/build/lib"],
        libraries=["GeantSim", "MAPT"],
    ),
    Extension(
        "mgeantfibersraw",
        sources=[
            "/home/rafal/projects/MAPT-clean/python/mgeantfibersraw.pyx",
        ],
        language="c++",              # generate C++ code
        extra_compile_args=["-std=c++14"],
        include_dirs=["/usr/lib64/root/6.14/include"],
        library_dirs=["/home/rafal/projects/MAPT-clean/build/lib"],
        libraries=["GeantSim", "MAPT"],
    ),
    Extension(
        "mfibersstackcalsim",
        sources=[
            "/home/rafal/projects/MAPT-clean/python/mfibersstackcalsim.pyx",
        ],
        language="c++",              # generate C++ code
        extra_compile_args=["-std=c++14"],
        include_dirs=["/usr/lib64/root/6.14/include"],
        library_dirs=["/home/rafal/projects/MAPT-clean/build/lib"],
        libraries=["FibersStack", "MAPT"],
    ),
    Extension(
        "mfibersstackcal",
        sources=[
            "/home/rafal/projects/MAPT-clean/python/mfibersstackcal.pyx",
        ],
        language="c++",              # generate C++ code
        extra_compile_args=["-std=c++14"],
        include_dirs=["/usr/lib64/root/6.14/include"],
        library_dirs=["/home/rafal/projects/MAPT-clean/build/lib"],
        libraries=["FibersStack", "MAPT"],
    ),
    Extension(
        "mapt_python",
        sources=[
            "/home/rafal/projects/MAPT-clean/python/mapt_python.pyx",
            "/home/rafal/projects/MAPT-clean/python/MAPT.cpp",
        ],
        language="c++",              # generate C++ code
        extra_compile_args=["-std=c++14"],
        include_dirs=[
            "/home/rafal/projects/MAPT-clean/lib/base",
            "/home/rafal/projects/MAPT-clean/lib/geant",
            "/home/rafal/projects/MAPT-clean/lib/fibers_stack",
            "/usr/lib64/root/6.14/include"
        ],
        library_dirs=["/home/rafal/projects/MAPT-clean/build/lib"],
        libraries=["FibersStack", "GeantSim", "MAPT"],
    ),
]

setup(
    name='pyMAPT',
    package_dir={'' : '/home/rafal/projects/MAPT-clean/python' },
    ext_modules=cythonize(modules, build_dir="/home/rafal/projects/MAPT-clean/build/python")
)
