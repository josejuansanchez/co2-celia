#!/bin/bash
set -x

# Deshabilitamos la paginación de la salida de los comandos de AWS CLI
# Referencia: https://docs.aws.amazon.com/es_es/cli/latest/userguide/cliv2-migration.html#cliv2-migration-output-pager
export AWS_PAGER=""

# Variables de configuración
AMI_ID=ami-09d56f8956ab235b3
COUNT=1
INSTANCE_TYPE=t2.micro
KEY_NAME=vockey
SECURITY_GROUP=iot-sg
INSTANCE_NAME=iot-ec2

# Creamos una intancia EC2
aws ec2 run-instances \
    --image-id $AMI_ID \
    --count $COUNT \
    --instance-type $INSTANCE_TYPE \
    --key-name $KEY_NAME \
    --security-groups $SECURITY_GROUP \
    --tag-specifications "ResourceType=instance,Tags=[{Key=Name,Value=$INSTANCE_NAME}]"
