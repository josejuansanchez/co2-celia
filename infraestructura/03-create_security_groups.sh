#!/bin/bash
set -x

# Deshabilitamos la paginación de la salida de los comandos de AWS CLI
# Referencia: https://docs.aws.amazon.com/es_es/cli/latest/userguide/cliv2-migration.html#cliv2-migration-output-pager
export AWS_PAGER=""

# Creamos el grupo de seguridad: iot-sg
aws ec2 create-security-group \
    --group-name iot-sg \
    --description "Reglas para el grupo de seguridad iot-sg"

# Creamos una regla de accesso SSH
aws ec2 authorize-security-group-ingress \
    --group-name iot-sg \
    --protocol tcp \
    --port 22 \
    --cidr 0.0.0.0/0

# Creamos una regla de accesso HTTP (Grafana)
aws ec2 authorize-security-group-ingress \
    --group-name iot-sg \
    --protocol tcp \
    --port 80 \
    --cidr 0.0.0.0/0

# Creamos una regla de accesso MQTT
aws ec2 authorize-security-group-ingress \
    --group-name iot-sg \
    --protocol tcp \
    --port 1883 \
    --cidr 0.0.0.0/0