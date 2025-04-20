if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CONFIG_NAME "gcc")
    set(OUTPUT_DIRECTORY "gcc")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CONFIG_NAME "msvc")
    set(OUTPUT_DIRECTORY "msvc")
endif()

if(BUILD_SHARED_LIBS)
    set(CONFIG_NAME "${CONFIG_NAME}-dll")
    set(OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY}/dll")
else()
    set(CONFIG_NAME "${CONFIG_NAME}-lib")
    set(OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY}/lib")
endif()

if((CMAKE_CXX_FLAGS MATCHES "-m32") OR (CMAKE_C_FLAGS MATCHES "-m32"))

    set(RC_EXTRA_FLAG "--target=pe-i386")

    set(CONFIG_NAME "${CONFIG_NAME}-x32")
    set(OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY}/x32")
else()
    set(CONFIG_NAME "${CONFIG_NAME}-x64")
    set(OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY}/x64")
endif()

if(CMAKE_BUILD_TYPE MATCHES "Debug")
    set(CONFIG_NAME "${CONFIG_NAME}-debug")
	# set(OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY}/debug")
else()
    set(CONFIG_NAME "${CONFIG_NAME}-release")
	# set(OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY}/release")
endif()

# ------------------------------------------------------------------------

foreach(ITEM ${INSTALL_HEADER_FILES})

    get_filename_component(ITEM_PATH ${ITEM} DIRECTORY)

	install(
        FILES ${ITEM}
        DESTINATION ${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}/${ITEM_PATH}
    )
endforeach()

# Путь для библиотек
install(
        TARGETS ${INSTALL_TARGET_FILES}
        DESTINATION ${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}/lib/${PROJECT_NAME}/${OUTPUT_DIRECTORY}
        EXPORT ${PROJECT_NAME}-targets
)

# Путь для автоматически генерируемых cmake файлов
install(
        EXPORT ${PROJECT_NAME}-targets
        DESTINATION ${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}/lib/${PROJECT_NAME}/${OUTPUT_DIRECTORY}/target
)

# Создание файлов конфигурации и версии пакета для GLOBAL SPACE
configure_file(
        ${CMAKE_SOURCE_DIR}/config/template-main-config.cmake.in
        ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}-config.cmake @ONLY
)

configure_file(
        ${CMAKE_SOURCE_DIR}/config/template-main-config-version.cmake.in
        ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}-config-version.cmake @ONLY
)

# Создание файлов конфигурации и версии пакета для текущей сборки CURRENT BUILD
configure_file(
        ${CMAKE_SOURCE_DIR}/config/template-config.cmake.in
        ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/config/${PROJECT_NAME}-${CONFIG_NAME}-config.cmake @ONLY
)

configure_file(
        ${CMAKE_SOURCE_DIR}/config/template-config-version.cmake.in
        ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/config/${PROJECT_NAME}-${CONFIG_NAME}-config-version.cmake @ONLY
)

# Создание файлов конфигурации и версии пакета для всех сборок ALL BUILD
configure_file(
        ${CMAKE_SOURCE_DIR}/config/template-base-config.cmake.in
        ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/config/${PROJECT_NAME}-config.cmake @ONLY
)

configure_file(
        ${CMAKE_SOURCE_DIR}/config/template-config-version.cmake.in
        ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/config/${PROJECT_NAME}-config-version.cmake @ONLY
)

# Установка файлов конфигурации и версии пакета.
install(FILES

        # GLOBAL SPACE
        ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}-config.cmake
        ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}-config-version.cmake

        # ALL BUILD
        ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/config/${PROJECT_NAME}-config.cmake
        ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/config/${PROJECT_NAME}-config-version.cmake

        # CURRENT BUILD
        ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/config/${PROJECT_NAME}-${CONFIG_NAME}-config.cmake
        ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/config/${PROJECT_NAME}-${CONFIG_NAME}-config-version.cmake

        DESTINATION ${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}/share/${CMAKE_PROJECT_NAME}/cmake
)