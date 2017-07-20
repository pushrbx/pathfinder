if( UNIX OR MINGW )
    # You need a c++11 Compiler to build CC
    # When we require cmake 3.1, we can use a cleaner method:
    #   CXX_STANDARD & CXX_STANDARD_REQUIRED
    #   https://cmake.org/cmake/help/v3.1/prop_tgt/CXX_STANDARD.html
    include(CheckCXXCompilerFlag)

    CHECK_CXX_COMPILER_FLAG("-std=gnu++14" COMPILER_SUPPORTS_CXX14)

    if (NOT COMPILER_SUPPORTS_CXX14)
        message(ERROR "--- Your compiler does not support C++14")
    endif()

    set( CXX11_FLAG "-std=gnu++14")
    set( GCC6_FLAGS "")

    # MinGW doesn't use fPIC
    if( UNIX )
        set( FPIC_FLAG  "-fPIC")
    endif()

    if( MINGW )
        set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
    endif()

    # check if the GCC version is greater than 6. In that case we have to add the -fpermissive flag.
    if(CMAKE_COMPILER_IS_GNUCXX)
        exec_program(${CMAKE_CXX_COMPILER} ARGS --version OUTPUT_VARIABLE _compiler_output)
        string(REGEX REPLACE ".* ([0-9]\\.[0-9]\\.[0-9])" "\\1" gcc_compiler_version ${_compiler_output})
        message(STATUS "GNU C++ compiler version: ${gcc_compiler_version} [${CMAKE_CXX_COMPILER}]")

        if(gcc_compiler_version VERSION_GREATER "6.0.0")
            message(STATUS "Adding -fpermissive and -Wint-to-pointer-cast flags to the compiler flags, because it's version greater than 6.")
            set( GCC6_FLAGS "-fpermissive -Wint-to-pointer-cast")
        endif()
    endif()

    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX11_FLAG} ${FPIC_FLAG} ${GCC6_FLAGS} -masm=intel -fvisibility=hidden -Wwrite-strings")
    set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${FPIC_FLAG} ${GCC6_FLAGS} -masm=intel -fvisibility=hidden -Wwrite-strings")
elseif( MSVC )
    add_definitions(-DNOMINMAX -D_CRT_SECURE_NO_WARNINGS)

    OPTION( OPTION_MP_BUILD "Check to activate multithreaded compilation with MSVC" OFF )
    if( ${OPTION_MP_BUILD} )
        set( CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}\ /MP)
    endif()

    #disable SECURE_SCL (see http://channel9.msdn.com/shows/Going+Deep/STL-Iterator-Debugging-and-Secure-SCL/)
    list( APPEND CCMAKE_CXX_FLAGS_RELEASE _SECURE_SCL=0 ) # disable checked iterators

    #use VLD for mem leak checking
    OPTION( OPTION_USE_VISUAL_LEAK_DETECTOR "Check to activate compilation (in debug) with Visual Leak Detector" OFF )
    if( ${OPTION_USE_VISUAL_LEAK_DETECTOR} )
        list( APPEND CCMAKE_CXX_FLAGS_DEBUG USE_VLD )
    endif()
endif()
