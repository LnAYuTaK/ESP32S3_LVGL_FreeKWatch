file(GLOB_RECURSE SOURCES 	
                    "lv_fs_fatfs.c"
                    "lv_fs_pc.c"
                    "lv_fs_posix.c"
                    "lv_fs_if.c")
idf_component_register(SRCS	${SOURCES}
                     INCLUDE_DIRS "./"
                     REQUIRES  
                     lvgl
                     fatfs
                     sd_fat)
