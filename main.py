import serial.tools.list_ports

ports = serial.tools.list_ports.comports()
serialInst = serial.Serial()

portList = []

# Cela met dans le terminal tous les serial port disponibles
for onePort in ports:
    portList.append(str(onePort))
    print(str(onePort))

# On met le numéro de COM correspondant au PIC
val = input("Port: ")

portVar = None

for x in range(0, len(portList)):
    if portList[x].startswith("COM" + str(val)):
        portVar = "COM" + str(val)
        print(portList[x])

serialInst.baudrate = 9600
serialInst.port = portVar
serialInst.open()

# L'idée c'est d'envoyer un nombre pour définir la limite au niveau de la distance ici et il est géré dans le C
# command = input("SEND TO PIC: ")
# serialInst.write(command.encode('utf'))

while True:
    # La boucle qui affiche toutes les données envoyées par le PIC dans le terminal
    if serialInst.in_waiting:
        packet = serialInst.readline()
        print(packet.decode('utf'))

