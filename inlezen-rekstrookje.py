from qwiicscale import QwiicScale
import time
import matplotlib.pyplot as plt 
import matplotlib.animation as animation
from matplotlib import style
from itertools import count


import cayenne.client #Cayenne MQTT client
MQTT_USERNAME = "e0abbbc0-b0d0-11ec-a681-73c9540e1265"
MQTT_PASSWORD = "2d5434e6253fd493bb519a9a0627b1464ef40c4f"
MQTT_CLIENT_ID = "f190dee0-cbc2-11ec-9f5b-45181495093e"

client = cayenne.client.CayenneMQTTClient()

client.begin(MQTT_USERNAME, MQTT_PASSWORD, MQTT_CLIENT_ID)




qwiic = QwiicScale()

qwiic.begin()
qwiic.getReading()
time.sleep(1)
waarde = qwiic.getReading()
Zero_offset = waarde
print(waarde)

gewicht = int( input( 'gewicht in gram '))

time.sleep(1)
waarde = qwiic.getReading()
calibration_factor = (waarde-Zero_offset)/gewicht 
print(waarde)
print(calibration_factor)

 

    
style.use('fivethirtyeight')

fig = plt.figure()
ax1 = fig.add_subplot(1,1,1)

xs = []
ys = []
index = count()

client.loop()

def animate(i):
    
    som = 0
    for i in range (10):
        som += qwiic.getReading()
    gemiddelde = som / 10
    weight = (gemiddelde-Zero_offset)/calibration_factor
    kracht = weight * 9.81 /1000
    
    print('kracht', kracht)
    
    
    xs.append(next(index))
    ys.append(kracht)
    ax1.clear()
    plt.title('belasting in fuctie van de tijd')
    plt.xlabel('tijd')
    plt.ylabel('kracht')
    ax1.plot(xs,ys)
    
    client.virtualWrite(1, kracht,"analog_sensor","Analog")
    
ani = animation.FuncAnimation(fig, animate, interval=1000)
plt.show()






