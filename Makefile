APP_NAME := test

BUILD_DIR := build
LSP_CONFIG := .misc
CMAKE_FLAGS := -DAPP_NAME=$(APP_NAME)

all: 
	@if [ ! -f $(BUILD_DIR)/CMakeCache.txt ]; then \
		echo "==> Initial CMake configure"; \
		cmake -S . -B $(BUILD_DIR) $(CMAKE_FLAGS); \
	else \
		echo "==> CMake already configured."; \
	fi; \
	mkdir -p $(LSP_CONFIG); \
	cp -f $(BUILD_DIR)/compile_commands.json $(LSP_CONFIG)
	cmake --build $(BUILD_DIR)
	@mv $(BUILD_DIR)/$(APP_NAME) .
	@./$(APP_NAME)

run: 
	@./$(APP_NAME)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -rf $(APP_NAME)

lclean: fclean
	rm -rf $(LSP_CONFIG)

.PHONY: all run clean fclean lclean
