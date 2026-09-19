SRC_DIR = ../src
include $(SRC_DIR)/Makefile_shared

TARGET = ../run_testpager ../run_testschema
EXAMPLE_HEADERS = test_data_gen.h testpager.h testschema.h
EXAMPLE_OBJS = $(addprefix $(OBJ_DIR)/,handle_input_options.o \
                 test_data_gen.o testpager.o testschema.o)

all: $(TARGET)

../run_%: $(EXAMPLE_OBJS) %_main.c
	cd $(SRC_DIR) && $(MAKE) objs
	$(CC) $(CFLAGS) $(LIBS) $(OBJS) $^ -o $@

$(OBJ_DIR)/%.o: %.c $(EXAMPLE_HEADERS) $(OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

.PHONY: clean

clean:
	rm -f $(TARGET)
	rm -f $(OBJS) $(EXAMPLE_OBJS)
