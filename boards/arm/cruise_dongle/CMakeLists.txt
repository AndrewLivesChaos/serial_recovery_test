if(CONFIG_GPIO)
	zephyr_library()
	zephyr_library_sources(cruise_dongle_init.c)
endif()