# - Try to find MPSSE_SPI
# Once done these will define
#  MPSSE_SPI_FOUND  flag
#  MPSSE_SPI_INCLUDE_DIR
#  MPSSE_SPI_LIB_DIR
#  MPSSE_STATIC_LIB
#  MPSSE_DYNAMIC_LIB

IF (NOT MPSSE_SPI_PATH)
    MESSAGE(FATAL_ERROR "Please specify libmpsse path by setting MPSSE_PATH. ")
ELSE ()
    IF (NOT EXISTS ${MPSSE_SPI_PATH})
        MESSAGE(FATAL_ERROR "Not find MPSSE_SPI_PATH:\n ${MPSSE_SPI_PATH}\t\t   ")
    ENDIF ()
ENDIF ()

find_path(MPSSE_SPI_INCLUDE_DIR
        NAMES libMPSSE_spi.h windows/ftd2xx.h linux/ftd2xx.h linux/WinTypes.h
        PATHS ${MPSSE_SPI_PATH}/include ${MPSSE_SPI_PATH}/release/include
        NO_DEFAULT_PATH
        NO_CMAKE_FIND_ROOT_PATH
        )
if (MPSSE_SPI_INCLUDE_DIR_NOTFOUND)
    MESSAGE(FATAL_ERROR "MPSSE_SPI include dir not found")
ELSE ()
    IF(WIN32)
        LIST(APPEND MPSSE_SPI_INCLUDE_DIR ${MPSSE_SPI_INCLUDE_DIR}/windows/)
    ELSE()
        LIST(APPEND MPSSE_SPI_INCLUDE_DIR ${MPSSE_SPI_INCLUDE_DIR}/linux/)
    ENDIF()
    MESSAGE(STATUS "MPSSE_SPI include dir found: ${MPSSE_SPI_INCLUDE_DIR}")
ENDIF ()

IF (WIN32)
    find_path(MPSSE_SPI_LIB_DIR
            NAMES libMPSSE.lib libMPSSE.dll
            PATHS ${MPSSE_SPI_PATH}/lib/windows/x64 ${MPSSE_SPI_PATH}/release/lib/windows/x64
            NO_DEFAULT_PATH
            NO_CMAKE_FIND_ROOT_PATH
            )
    if (MPSSE_SPI_LIB_DIR_NOTFOUND)
        MESSAGE(FATAL_ERROR "MPSSE_SPI lib dir not found")
    ELSE ()
        FIND_LIBRARY(MPSSE_SPI_STATIC_LIB NAMES libMPSSE.lib PATHS ${MPSSE_SPI_LIB_DIR})
        FIND_LIBRARY(MPSSE_SPI_DYNAMIC_LIB NAMES libMPSSE.dll PATHS ${MPSSE_SPI_LIB_DIR})
        MESSAGE(STATUS "MPSSE_SPI lib dir found: ${MPSSE_SPI_LIB_DIR}")
    ENDIF ()
ELSEIF (UNIX)
    find_path(MPSSE_SPI_LIB_DIR
            NAMES libMPSSE.a libMPSSE.so
            PATHS ${MPSSE_SPI_PATH}/lib/linux/i386 ${MPSSE_SPI_PATH}/release/lib/linux/i386
            NO_DEFAULT_PATH
            NO_CMAKE_FIND_ROOT_PATH
            )
    if (MPSSE_SPI_LIB_DIR_NOTFOUND)
        MESSAGE(FATAL_ERROR "MPSSE_SPI lib dir not found")
    ELSE ()
        FIND_LIBRARY(MPSSE_SPI_STATIC_LIB NAMES libMPSSE.a PATHS ${MPSSE_SPI_LIB_DIR})
        FIND_LIBRARY(MPSSE_SPI_DYNAMIC_LIB NAMES libMPSSE.so PATHS ${MPSSE_SPI_LIB_DIR})
        MESSAGE(STATUS "MPSSE_SPI lib dir found: ${MPSSE_SPI_LIB_DIR}")
    ENDIF ()
ENDIF ()

SET(MPSSE_SPI_FOUND)


