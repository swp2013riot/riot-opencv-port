# ----------------------------------------------------------------------------
#  Detect 3rd-party GUI libraries
# ----------------------------------------------------------------------------

#--- Win32 UI ---
ocv_clear_vars(HAVE_WIN32UI)
if(WITH_WIN32UI)
  TRY_COMPILE(HAVE_WIN32UI
    "${OPENCV_BINARY_DIR}/CMakeFiles/CMakeTmp"
    "${OpenCV_SOURCE_DIR}/cmake/checks/win32uitest.cpp"
    CMAKE_FLAGS "\"user32.lib\" \"gdi32.lib\""
    OUTPUT_VARIABLE OUTPUT)
endif(WITH_WIN32UI)

# --- QT4 ---
ocv_clear_vars(HAVE_QT)
if(WITH_QT)
  find_package(Qt4)
  if(QT4_FOUND)
    set(HAVE_QT TRUE)
    add_definitions(-DHAVE_QT) # We need to define the macro this way, using cvconfig.h does not work
  endif()
endif()

# --- GTK ---
ocv_clear_vars(HAVE_GTK HAVE_GTHREAD HAVE_GTKGLEXT)
if(WITH_GTK AND NOT HAVE_QT)
  CHECK_MODULE(gtk+-2.0 HAVE_GTK)
  CHECK_MODULE(gthread-2.0 HAVE_GTHREAD)
  if(WITH_OPENGL)
    CHECK_MODULE(gtkglext-1.0 HAVE_GTKGLEXT)
  endif()
endif()

# --- OpenGl ---
ocv_clear_vars(HAVE_OPENGL HAVE_QT_OPENGL)
if(WITH_OPENGL)
  if(WITH_WIN32UI OR (HAVE_QT AND QT_QTOPENGL_FOUND) OR HAVE_GTKGLEXT)
    find_package (OpenGL QUIET)
    if(OPENGL_FOUND)
      set(HAVE_OPENGL TRUE)
      list(APPEND OPENCV_LINKER_LIBS ${OPENGL_LIBRARIES})
      if(QT_QTOPENGL_FOUND)
        set(HAVE_QT_OPENGL TRUE)
        add_definitions(-DHAVE_QT_OPENGL)
      else()
        ocv_include_directories(${OPENGL_INCLUDE_DIR})
      endif()
    endif()
  endif()
endif(WITH_OPENGL)
