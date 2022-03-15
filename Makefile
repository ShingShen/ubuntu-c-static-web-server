CFLAGS = -O2 -g -std=c99 -Wall -I include

CFLAGS += -D_POSIX_C_SOURCE=199506L

OUT = bin
EXEC = $(OUT)/server
OBJS = \
	src/main.o

deps := $(OBJS:%.o=%.o.d)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ -MMD -MF $@.d -c $<

$(EXEC): $(OBJS)
	mkdir -p $(OUT)
	$(CC) $(OBJS) -o $@ -pthread

run: $(EXEC)
	@echo "Starting Server..."
	@./$(EXEC) 7070

clean:
	$(RM) $(OBJS) $(EXEC) $(deps)

-include $(deps)