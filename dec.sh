#!/bin/bash

if [ $# -lt 3 ]
then
  echo "enc.sh [iter] [file in] [file out]"
  exit 1
fi

echo "openssl enc -aes-256-cbc -d -iter $1 -in $2 -out $3"
openssl enc -aes-256-cbc -d -iter $1 -in $2 -out $3
