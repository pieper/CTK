project(${PROJECT_NAME}Plugins)

#
# See CTK/CMake/ctkMacroBuildQtPlugin.cmake for details
#

set(PLUGIN_export_directive "CTK_COMMAND_LINE_MODULES_WIDGETS_PLUGINS_EXPORT")

# Source files
set(PLUGIN_SRCS
  )

# Headers that should run through moc
set(PLUGIN_MOC_SRCS
  )

# Resources
set(PLUGIN_resources
)

# Target libraries
set(PLUGIN_target_libraries
  CTKCommandLineModulesWidgets
  )

ctkMacroBuildQtDesignerPlugin(
  NAME ${PROJECT_NAME}
  EXPORT_DIRECTIVE ${PLUGIN_export_directive}
  SRCS ${PLUGIN_SRCS}
  MOC_SRCS ${PLUGIN_MOC_SRCS}
  RESOURCES ${PLUGIN_resources}
  TARGET_LIBRARIES ${PLUGIN_target_libraries}
)
