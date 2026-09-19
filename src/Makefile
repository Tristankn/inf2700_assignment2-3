include Makefile_shared

TARGET = ../run_db2700
DOC_DIR = ../doc

all: $(TARGET)

$(TARGET): $(OBJS) front.c
	$(CC) $(CFLAGS) $(LIBS) $^ -o $@

objs: $(OBJS)

$(OBJ_DIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

.PHONY: doc clean cleandoc
doc:
	doxygen Doxyfile

clean:
	rm -f $(TARGET)
	rm -f $(OBJS)

cleandoc:
	rm -fr $(DOC_DIR)/html
