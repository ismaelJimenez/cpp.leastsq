# Allow the source files to find headers in src/
include_directories(${PROJECT_SOURCE_DIR}/src)

# Define the source files
set(SOURCE_FILES "minimal_leastsq.cpp")

add_library(minimal-leastsq ${SOURCE_FILES} ${RE_FILES})


set_target_properties(minimal-leastsq PROPERTIES
  OUTPUT_NAME "minimal-leastsq"
  VERSION ${GENERIC_LIB_VERSION}
  SOVERSION ${GENERIC_LIB_SOVERSION}
)

# Link threads.
target_link_libraries(minimal-leastsq ${CMAKE_THREAD_LIBS_INIT})

# We need extra libraries on Windows
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  target_link_libraries(minimal-leastsq Shlwapi)
endif()

# Expose public API
target_include_directories(minimal-leastsq PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Install target (will install the library to specified CMAKE_INSTALL_PREFIX variable)
install(
  TARGETS minimal-leastsq
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  COMPONENT library)

install(
  DIRECTORY "${PROJECT_SOURCE_DIR}/include"
  DESTINATION include
  FILES_MATCHING PATTERN "*.*h")
