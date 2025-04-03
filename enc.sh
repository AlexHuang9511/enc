#!/usr/bin/bash

if [ $# -lt 3 ]
then
  echo "enc.sh [iter] [file in] [file out]"
  exit 1
fi

echo "openssl enc -aes-256-cbc -e -iter $1 -salt -in $2 -out $3"
openssl enc -aes-256-cbc -e -iter $1 -salt -in $2 -out $3
