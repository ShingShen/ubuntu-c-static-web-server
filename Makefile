OUT = bin
EXEC = $(OUT)/server
OBJS = \
	main.o

$(EXEC): $(OBJS)
	mkdir -p $(OUT)
	$(CC) $(OBJS) -o $@ -pthread

run: $(EXEC)
	@echo "Starting Server..."
	@./$(EXEC) 8181

clean:
	$(RM) $(OBJS) $(EXEC)