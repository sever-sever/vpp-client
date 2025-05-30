CC = gcc
SOURCES = vpp_client.c
CFLAGS = -Wall -Wextra -I.
BIN_DIR = build

TARGET = vpp_client

all: $(TARGET)

$(TARGET): $(SOURCES)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $(SOURCES)

clean:
	rm -f $(BIN_DIR)/$(TARGET)

.PHONY: all clean

