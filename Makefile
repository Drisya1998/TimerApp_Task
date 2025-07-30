CC ?= gcc
CROSS_CC = aarch64-linux-gnu-gcc
SRC_DIR =.
APP_SRC = $(SRC_DIR)/main.c appTimer/appTimer.c LED/LED.c

RELEASE_DIR = release
DEBUG_DIR = debug

EXEC_LINUX = $(RELEASE_DIR)/TimerApp
EXEC_RPI = $(RELEASE_DIR)/TimerApp_rpi
EXEC_DEBUG = $(DEBUG_DIR)/TimerApp_debug

FLAGS = -Wall -Wextra -I. -I./appTimer -I./LED
RPI_CFLAGS = -I/opt/gpiod-v1-arm/include -D_RPIBOARD
RPI_LFLAGS = -L/opt/gpiod-v1-arm/lib -Wl,-rpath=/opt/gpiod-v1-arm/lib -lgpiod
DEBUG_FLAGS = -g
LINKER_FLAGS = -Wl,-Map=output.map

SOURCES = main appTimer/appTimer LED/LED

dirs:
	@mkdir -p $(RELEASE_DIR)
	@mkdir -p $(RELEASE_DIR)/appTimer
	@mkdir -p $(RELEASE_DIR)/LED


all:linux rpi debug
linux: dirs
	$(CC) $(FLAGS) $(APP_SRC) -o $(EXEC_LINUX)
	@$(foreach file, $(SOURCES), \
		$(CC) $(FLAGS) -S $(file).c -o $(RELEASE_DIR)/$(file).s && \
		$(CC) $(FLAGS) -c $(file).c -o $(RELEASE_DIR)/$(file).o ;)

rpi: dirs
	$(CROSS_CC) $(FLAGS) $(RPI_CFLAGS) $(APP_SRC) $(RPI_LFLAGS) -o $(EXEC_RPI)
	@$(foreach file, $(SOURCES), \
		$(CROSS_CC) $(FLAGS) -S $(file).c -o $(RELEASE_DIR)/$(file).s && \
		$(CROSS_CC) $(FLAGS) -c $(file).c -o $(RELEASE_DIR)/$(file).o ;)

debug:
	@mkdir -p $(DEBUG_DIR)
	$(CC) $(FLAGS) $(DEBUG_FLAGS) $(LINKER_FLAGS) $(APP_SRC) -o $(EXEC_DEBUG)

clean:
	rm -rf $(RELEASE_DIR) $(DEBUG_DIR)
