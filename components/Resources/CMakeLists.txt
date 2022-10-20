file(GLOB_RECURSE SOURCES 	./img_cogwheel_argb.c 
							)

idf_component_register(SRCS	${SOURCES}
                   INCLUDE_DIRS 
								.
                    REQUIRES  lvgl
                             )
