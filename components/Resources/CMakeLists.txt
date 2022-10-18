file(GLOB_RECURSE SOURCES 	./background.c 
							)

idf_component_register(SRCS	${SOURCES}
                   INCLUDE_DIRS 
								.
                    REQUIRES  lvgl
                             )
