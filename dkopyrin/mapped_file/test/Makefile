all:

test:
	$(CC) $(CFLAGS) -o "$(MAKE_DIR)/test-mf" test_simple.c "$(MAKE_DIR)/libmappedfile.a" -I../../../include/
	$(CC) $(CFLAGS) -o "$(MAKE_DIR)/test_map" test_simple_map.c "$(MAKE_DIR)/libmappedfile.a" -I../../../include/
	$(CC) $(CFLAGS) -o "$(MAKE_DIR)/test_ht" test_ht.c "$(MAKE_DIR)/libmappedfile.a" -I../../../include/
	$(CC) $(CFLAGS) -o "$(MAKE_DIR)/test_ladder" test_ladder.c "$(MAKE_DIR)/libmappedfile.a" -I../../../include/
	$(CC) $(CFLAGS) -o "$(MAKE_DIR)/test_stairs" test_stairs.c "$(MAKE_DIR)/libmappedfile.a" -I../../../include/

clean:
	rm -f "$(MAKE_DIR)/test-mf" "$(MAKE_DIR)/test_map" "$(MAKE_DIR)/test_ladder" "$(MAKE_DIR)/test_stairs" "$(MAKE_DIR)/test_ht" "$(MAKE_DIR)/*.o"
