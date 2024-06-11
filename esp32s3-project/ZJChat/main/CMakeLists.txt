set(UI_DIR ./ui)
file(GLOB_RECURSE UI_SRCS ${UI_DIR}/*.c)

set(UI_CUSTOM ./ui/custom)
file(GLOB_RECURSE UI_CUSTOM_SRCS ${UI_DIR}/*.c)

set(UI_GENERATED ./ui/generated)
file(GLOB_RECURSE UI_GENERATED_SRCS ${UI_DIR}/*.c)


set(APP_DIR ./app)
file(GLOB_RECURSE APP_SRCS ${APP_DIR}/*.c)

idf_component_register(
    SRCS
        "main.c"
        ${UI_SRCS}
        ${UI_CUSTOM_SRCS}
        ${UI_GENERATED_SRCS}
        ${APP_SRCS}
    INCLUDE_DIRS
        "."
        ${UI_DIR}
        ${UI_CUSTOM}
        ${UI_GENERATED}
        ${APP_DIR}
)

spiffs_create_partition_image(storage ../spiffs)
