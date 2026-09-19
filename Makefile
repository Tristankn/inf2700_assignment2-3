SRC_DIR = src
EXAMPLE_DIR = examples
DOC_DIR = doc
TEST_DIR = tests

.PHONY: all db2700 example doc cleanall clean cleandoc cleantest

all:
	cd $(SRC_DIR) && $(MAKE) $@
	cd $(EXAMPLE_DIR) && $(MAKE) $@

db2700:
	cd $(SRC_DIR) && $(MAKE) $@

examples:
	cd $(EXAMPLE_DIR) && $(MAKE) $@

doc:
	cd $(SRC_DIR) && $(MAKE) $@

cleanall: clean cleandoc cleantest

clean:
	cd $(EXAMPLE_DIR) && $(MAKE) $@
	cd $(SRC_DIR) && $(MAKE) $@

cleandoc:
	cd $(SRC_DIR) && $(MAKE) $@

cleantest:
	rm -f $(TEST_DIR)/testdb/*
