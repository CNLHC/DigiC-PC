# - Try to find D2XX
# Once done this will define
#  D2XX_FOUND - System has LibXml2
#  D2XX_INCLUDE_DIRS - The LibXml2 include directories
#  D2XX_LIBRARIES - The libraries needed to use LibXml2
#  D2XX_LIB_DIR - The libraries needed to use LibXml2

IF(NOT D2XX_PATH)
    MESSAGE( FATAL_ERROR 
        "Please specify D2XX path by setting D2XX_PATH variable. " 
        "You can download it at: \n" 
        "https://www.ftdichip.com/Drivers/D2XX.htm"
        )
ELSE()
    IF(EXISTS ${D2XX_PATH})
        MESSAGE(STATUS "D2XX_PATH: ${D2XX_PATH}")
    ELSE()
        MESSAGE( FATAL_ERROR "Not find D2XX_PATH:\n ${D2XX_PATH}\t\t   " )
    ENDIF()
ENDIF()


IF(EXISTS ${D2XX_PATH}/ftd2xx.h)
    MESSAGE(STATUS "ftd2xx.h found")
ELSE()
    MESSAGE(FATAL_ERROR "ftd2xx.h not found")
ENDIF()


IF(EXISTS ${D2XX_PATH}/amd64/ftd2xx.lib)
    FIND_LIBRARY(D2XX_STATIC_LIB NAMES ftd2xx.lib PATHS ${D2XX_PATH}/amd64)
    MESSAGE(STATUS "D2XX ftd2xx.lib found: ${D2XX_STATIC_LIB}")
ELSE()
    MESSAGE(FATAL_ERROR "ftd2xx.lib not found")
ENDIF()

SET(D2XX_FOUND True)
SET(D2XX_INCLUDE_DIRS ${D2XX_PATH})
