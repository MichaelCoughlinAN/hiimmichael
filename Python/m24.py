import smbus2

# Set up I2C bus and device address
bus = smbus2.SMBus(1)  # 1 indicates /dev/i2c-1
device_address = 0x50  # Example address, check your EEPROM's datasheet

def write_byte(addr, data):
    bus.write_byte_data(device_address, addr, data)

def read_byte(addr):
    return bus.read_byte_data(device_address, addr)

# Example usage
write_byte(0x00, 0xff)  # Write 0xff to address 0x00
data = read_byte(0x00)  # Read from address 0x00
print("Data read from EEPROM:", data)
