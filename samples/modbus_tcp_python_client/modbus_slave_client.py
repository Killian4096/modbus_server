from pymodbus.client import ModbusTcpClient

client = ModbusTcpClient('127.0.0.1', port=8080)       # Create client object
client.connect()                               # connect to device
result = client.read_coils(address=0, count=8)
print(result.bits)
client.write_coil(0, True)        # set information in device
result = client.read_coils(address=0, count=8)
print(result.bits)
client.close()                                 # Disconnect device
