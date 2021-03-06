set(CPACK_PACKAGE_NAME ${PROJECT_NAME}
	CACHE STRING "The resulting package name"
)

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Simple calculator"
	CACHE STRING "Package description for the package metadata"
)
set(CPACK_PACKAGE_VENDOR "CSU")

set(CPACK_VERBATIM_VARIABLES YES)

set(CPACK_PACKAGE_INSTALL_DIRECTORY ${CPACK_PACKAGE_NAME})
SET(CPACK_OUTPUT_FILE_PREFIX "${CMAKE_SOURCE_DIR}/_packages")

set(CPACK_PACKAGEING_INSTALL_PREFIX "/opt/some")

set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

set(CPACK_PACKAGE_CONTACT "chikangxi@hotmail.com")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "chikangxi")

set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)

set(CPACK_COMPONENTS_GROUPING ALL_COMPONENTS_IN_ONE)

set(CPACK_DEB_COMPONENT_INSTALL YES)

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)
