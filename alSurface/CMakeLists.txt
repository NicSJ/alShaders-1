set(SHADER alSurface)        
set(SRC ${SHADER}.cpp sss.cpp ../common/alUtil.cpp ../common/Color.cpp ../common/fresnel.cpp ../cryptomatte/MurmurHash3.cpp)
set(UI ${CMAKE_CURRENT_SOURCE_DIR}/${SHADER}.ui)
set(MTD ${CMAKE_CURRENT_BINARY_DIR}/${SHADER}.mtd)
set(AE ${CMAKE_CURRENT_BINARY_DIR}/${SHADER}Template.py)
set(AEXML ${CMAKE_CURRENT_BINARY_DIR}/AE${SHADER}Template.xml)
set(NEXML ${CMAKE_CURRENT_BINARY_DIR}/NE${SHADER}Template.xml)
set(SPDL ${CMAKE_CURRENT_BINARY_DIR}/${SHADER}.spdl)
set(KARGS ${CMAKE_CURRENT_BINARY_DIR}/${SHADER}.args)
set(C4DRES ${CMAKE_CURRENT_BINARY_DIR}/C4DtoA)
set(HTML ${CMAKE_SOURCE_DIR}/docs/${SHADER}.html)

add_library(${SHADER} SHARED ${SRC})

target_link_libraries(${SHADER} ai)
set_target_properties(${SHADER} PROPERTIES PREFIX "")

add_custom_command(OUTPUT ${MTD} COMMAND ${PYTHON_EXECUTABLE} ARGS ${CMAKE_SOURCE_DIR}/uigen.py ${UI} ${MTD} ${AE} ${AEXML} ${NEXML} ${SPDL} ${KARGS} ${CMAKE_CURRENT_BINARY_DIR} ${HTML} DEPENDS ${UI})
add_custom_target(${SHADER}UI ALL DEPENDS ${MTD})

install(TARGETS ${SHADER} DESTINATION ${DSO_INSTALL_DIR})
install(FILES ${MTD} DESTINATION ${MTD_INSTALL_DIR})
install(FILES ${AE} DESTINATION ${AE_INSTALL_DIR})
install(FILES ${AEXML} DESTINATION ${AEXML_INSTALL_DIR})
install(FILES ${NEXML} DESTINATION ${NEXML_INSTALL_DIR})
install(FILES ${SPDL} DESTINATION ${SPDL_INSTALL_DIR})
install(FILES ${KARGS} DESTINATION ${ARGS_INSTALL_DIR})
install(DIRECTORY ${C4DRES} DESTINATION ${INSTALL_DIR})

#add_executable(coltable coltable.cpp ../common/alUtil.cpp)
#add_executable(ddint ddint.cpp sss.cpp ../common/alUtil.cpp)
#target_link_libraries(ddint ai)

