# co2-celia

Proyecto experimental de IoT para monitorizar el CO2.

Este proyecto se ha realizado en el módulo profesional **Implantación de aplicaciones web** del **CFGS ASIR** del **IES Celia Viñas (Almería)**, durante el curso escolar 2020/2021.

Puede encontrar una descripción detallada en la página web del proyecto: [«IoT Dashboard - Sensores, MQTT, Telegraf, InfluxDB y Grafana»](https://josejuansanchez.org/iot-dashboard/).

## Descripción

En cada aula del instituto vamos a tener un [Wemos D1 mini](https://wemos.cc), un [sensor de CO2](https://wiki.keyestudio.com/KS0457_keyestudio_CCS811_Carbon_Dioxide_Air_Quality_Sensor) y un [sensor de temperatura/humedad DHT11](https://learn.adafruit.com/dht/overview) que van a ir tomando medidas de forma constante y las van a ir publicando en un *topic* de un [*broker* MQTT](http://mqtt.org). Podríamos seguir la siguiente estructura de nombres para los *topics* del edificio:

```
iescelia/aula<número>/temperature
iescelia/aula<número>/humidity
iescelia/aula<número>/co2
```

Por ejemplo para el `aula20` tendríamos los siguientes *topics*:

```
iescelia/aula20/temperature
iescelia/aula20/humidity
iescelia/aula20/co2
```

También existirá un agente de [Telegraf](https://www.influxdata.com/time-series-platform/telegraf/) que estará suscrito a los  *topics* del [*broker* MQTT](http://mqtt.org) donde se publican los valores recogidos por los sensores.  El agente de [Telegraf](https://www.influxdata.com/time-series-platform/telegraf/) insertará los valores que recoge del [*broker* MQTT](http://mqtt.org) en una base de datos [InfluxDB](https://www.influxdata.com/), que es un sistema gestor de bases de datos diseñado para almacenar series temporales de datos.Finalmente tendremos un servicio web [Grafana](https://grafana.com) que nos permitirá visualizar los datos en un panel de control.

## Diagrama

![](images/diagram.png)

## Panel de control en Grafana

![](images/dashboard.png)

## Referencias

- http://josejuansanchez.org/iot-dashboard/
- https://github.com/maarten-pennings/CCS811
