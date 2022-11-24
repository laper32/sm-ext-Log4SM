#
# Purpose: Determine compiler.
#
if(MSVC)
    add_compile_options(-DCOMPILER_MSVC)
    if(TARGET_ARCH MATCHES "x64")
        add_compile_options(-DCOMPILER_MSVC64)
    else()
        add_compile_options(-DCOMPILER_MSVC32)
    endif()
else()
    add_compile_options(-DCOMPILER_GCC) ## clang or gcc
endif()

#
# Purpose: Check stdint.h
#
include(CheckIncludeFile)
check_include_file(stdint.h HAVE_STDINT_H)
if (HAVE_STDINT_H)
    add_compile_options(-DHAVE_STDINT_H)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    add_compile_options(-DNDEBUG)
else()
    add_compile_options(-DDEBUG -D_DEBUG)
endif()

if (WIN32)
    add_definitions(-DWIN32 -D_WINDOWS)
elseif (UNIX)
    add_definitions(-DLINUX -D_LINUX)
    string(APPEND CMAKE_SHARED_LINKER_FLAGS
        " -Wl,--exclude-libs,ALL"
        " -lm"
    )
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU") #gcc
        string(APPEND CMAKE_SHARED_LINKER_FLAGS
            " -static-libgcc"
        )
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        string(APPEND CMAKE_SHARED_LINKER_FLAGS
            " -lgcc_eh"
        )
    endif()
endif()

# For gaming, nobody use compiler except MSVC
if (MSVC)
    add_compile_options(/wd4819 /wd4828 /wd5033 /permissive- /utf-8 /wd4005)
    if (ENABLE_DEBUG)
        string(APPEND CMAKE_C_FLAGS
            " /MDd"
        )
        string(APPEND CMAKE_SHARED_LINKER_FLAGS
            " /NODEFAULTLIB:libcmt"
        )
    else ()
        string(APPEND CMAKE_C_FLAGS
            " /MD"
        )
    endif()

    add_compile_definitions(
        _CRT_SECURE_NO_WARNINGS=1 _CRT_SECURE_NO_DEPRECATE=1
        _CRT_NONSTDC_NO_DEPRECATE=1 _ITERATOR_DEBUG_LEVEL=0
    )

    string(APPEND CMAKE_C_FLAGS
        " /W3"
    )
    # /EHsc has already been included
    string(APPEND CMAKE_CXX_FLAGS
        #" /GR-" # In this case /GR- need to disabled since they are using dynamic cast.
        " /TP"
    )

    if (ENABLE_OPTIMIZE)
        string(APPEND CMAKE_C_FLAGS
            " /Ox"
            " /Zo"
        )
        string(APPEND CMAKE_SHARED_LINKER_FLAGS
            " /OPT:ICF"
            " /OPT:REF"
        )
    endif()

    if (ENABLE_DEBUG)
        string(APPEND CMAKE_C_FLAGS
            " /Od"
            " /RTC1"
        )
    endif()
    
    string(APPEND CMAKE_C_FLAGS
        " /Oy-"
    )
    
    #string(APPEND CMAKE_SHARED_LINKER_FLAGS
    #    " /MACHINE:x86"
    #)

else()
# Work for both
    if (HL2SDK_ENGINE_NAME NOT MATCHES "sdk2013" OR HL2SDK_ENGINE_NAME NOT MATCHES "bms" OR HL2SDK_ENGINE_NAME NOT MATCHES "pvkii")
        add_definitions(
            -Dstricmp=strcasecmp -D_stricmp=strcasecmp
            -D_snprintf=snprintf -D_vsnprintf=vsnprintf
        )
    endif()
    add_definitions(
        -DGNUC -DCOMPILER_GCC
    )
    # for better visibility, we separate it onto two lines
    string(APPEND CMAKE_C_FLAGS
        " -pipe"
        " -fno-strict-aliasing"
        " -Wall"
        " -Werror"
        " -Wno-unused"
        " -Wno-switch"
        " -Wno-array-bounds"
        " -msse"
        " -fvisibility=hidden"
    )
    if (TARGET_ARCH STREQUAL "x86")
        string(APPEND CMAKE_C_FLAGS
            " -m32"
        )
        string(APPEND CMAKE_SHARED_LINKER_FLAGS
            " -m32"
        )

    endif()
    string(APPEND CMAKE_CXX_FLAGS
        " -fno-exceptions"
        " -fno-threadsafe-statics"
        " -Wno-non-virtual-dtor"
        " -Wno-overloaded-virtual"
        " -fvisibility-inlines-hidden"
        " -Wno-delete-non-virtual-dtor"
    )
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU") #gcc
        string(APPEND CMAKE_C_FLAGS
            " -Wno-narrowing"
            " -Wno-unused-result"
            " -mfpmath=sse"
        )
        if (ENABLE_OPTIMIZE)
            string(APPEND CMAKE_C_FLAGS
                " -O3"
            )
        endif()
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        string(APPEND CMAKE_C_FLAGS
            " -Wno-sometimes-uninitialized"
        )
        string(APPEND CMAKE_CXX_FLAGS
            " -Wno-inconsistent-missing-override"
            " -Wno-implicit-exception-spec-mismatch"
            " -Wno-deprecated-register"
        )
    endif()
endif()

if (
    HL2SDK_ENGINE_NAME MATCHES "csgo" OR
    HL2SDK_ENGINE_NAME MATCHES "blade" OR
    HL2SDK_ENGINE_NAME MATCHES "insurgency" OR
    HL2SDK_ENGINE_NAME MATCHES "doi")
    add_compile_definitions(-DNETWORK_VARS_ENABLED)
endif()

if (
    HL2SDK_ENGINE_NAME MATCHES "css" OR HL2SDK_ENGINE_NAME MATCHES "hl2dm" OR HL2SDK_ENGINE_NAME MATCHES "dods" OR
    HL2SDK_ENGINE_NAME MATCHES "sdk2013" OR HL2SDK_ENGINE_NAME MATCHES "bms" OR HL2SDK_ENGINE_NAME MATCHES "tf2" OR
    HL2SDK_ENGINE_NAME MATCHES "l4d" OR HL2SDK_ENGINE_NAME MATCHES "nucleardawn" OR HL2SDK_ENGINE_NAME MATCHES "l4d2" OR
    HL2SDK_ENGINE_NAME MATCHES "pvkii")
    if (UNIX)
        add_compile_definitions(-DNO_HOOK_MALLOC -DNO_MALLOC_OVERRIDE)
    endif()
endif()

if (HL2SDK_ENGINE_NAME MATCHES "csgo" AND UNIX)
    string(APPEND CMAKE_SHARED_LINKER_FLAGS " -lstdc++")
endif()

#[[
#
# Purpose: Determine basic macro for UNIX System
#
if(NOT WIN32)
    if (HL2SDK_ENGINE_NAME MATCHES "sdk2013" OR HL2SDK_ENGINE_NAME MATCHES "bms" AND CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        add_compile_options(
            -DPOSIX                 -DVPROF_LEVEL=1             -DSWDS                  -D_finite=finite
            -D_strnicmp=strncasecmp -Dstrnicmp=strncasecmp      -D_alloca=alloca        -Dstrcmpi=strcasecmp
            -DGNUC
        )
    else()
        add_compile_options(
            -DPOSIX                 -DVPROF_LEVEL=1             -DSWDS                  -D_finite=finite
            -Dstricmp=strcasecmp    -D_stricmp=strcasecmp       -D_strnicmp=strncasecmp -Dstrnicmp=strncasecmp
            -D_vsnprintf=vsnprintf  -D_alloca=alloca            -Dstrcmpi=strcasecmp    -D_snprintf=snprintf
            -DGNUC
        )
    endif()

    if (TARGET_ARCH MATCHES "x86")
        add_compile_options(-m32)
        add_link_options(-m32)
    endif()

    # add_compile_options will add these options to all related compilers,
    # for example, if gcc then add to both gcc and g++, clang also.
    # And...If we do such thing, if the compiler does not manipulate this case, 
    # it will throw a warning to us, and you don't want to see these warnings.
    # Again, if you don't mind then you will see a massive of shit.
    # So we need to add compile options separatly.
    if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        # CMAKE_CXX_FLAGS will add flags to C++ compilers.
        # CMAKE_C_FLAGS do such things, but C.
        set(CMAKE_CXX_FLAGS "-Wno-register -Wno-non-virtual-dtor -Wno-overloaded-virtual ${CMAKE_CXX_FLAGS}")
        set(CMAKE_CXX_FLAGS "-fvisibility-inlines-hidden -Wno-delete-non-virtual-dtor ${CMAKE_CXX_FLAGS}")
    endif()

    add_compile_options(-Wno-narrowing -O3 -pipe -Wno-uninitialized -Wno-unused -Wno-switch -msse -fPIC 
    -Wno-unused-result -Wno-ignored-attributes -fno-strict-aliasing -fvisibility=hidden
    )
    if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        set(CMAKE_CXX_FLAGS "-Wno-volatile ${CMAKE_CXX_FLAGS}")
        add_compile_options(-mfpmath=sse)
    endif()
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        add_compile_options(
            -Wno-implicit-int-float-conversion -Wno-tautological-overlap-compare -Wno-deprecated-volatile
            -Wno-implicit-exception-spec-mismatch -Wno-expansion-to-defined -Wno-inconsistent-missing-override -Wno-deprecated-register
            -Wno-ambiguous-reversed-operator -Wno-tautological-undefined-compare -Wno-enum-compare-switch -Wno-c++11-narrowing
            -fvisibility-inlines-hidden -Wno-delete-non-virtual-dtor -Wno-register -Wno-non-virtual-dtor -Wno-overloaded-virtual
        )
    endif()
endif()

#
# Purpose: Configure MSVC compiler options
#
if (MSVC)
    if (ENABLE_DEBUG)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MTd /Od /RTC1")
        set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /NODEFAULTLIB:libcmt")
    else()
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MT")
    endif()

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W3 /Zi /Oy-")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /TP")

    if (ENABLE_OPTIMIZE)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /Ox /Zo")
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /OPT:REF /OPT:ICF")
    endif()

    add_compile_options(/wd4819 /wd4828 /wd5033 /permissive- /utf-8 /wd4005)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS=1 _CRT_SECURE_NO_DEPRECATE=1 _CRT_NONSTDC_NO_DEPRECATE=1)
endif()

if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    set(OSX ON)
    add_compile_options(-DOSX -D_OSX)
elseif (CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(LINUX ON)
    add_compile_options(-DLINUX -D_LINUX -D_FILE_OFFSET_BITS=64)

    if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        add_link_options(-static-libgcc)
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        add_link_options(-lgcc_eh)
    endif()

elseif(WIN32)
    add_compile_options(-DWIN32 -D_WINDOWS)
endif()
]]