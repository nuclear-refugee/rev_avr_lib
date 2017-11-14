PORT = 8
BAUD = 38400

serial_test: serial_test.hex
	@make -f m128.make $<
	@cmd_ASA_loader -p $(PORT) -h $<
	@terminal -p $(PORT) -b $(BAUD)
