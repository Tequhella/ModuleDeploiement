#!/bin/bash

# Vérifiez si Boost est installé
dpkg -s libboost-dev &> /dev/null
if [ $? -ne 0 ]; then
    echo "Boost n'est pas installé. Installation en cours..."
    sudo apt-get install libboost-dev
fi

# Vérifiez si gtkmm est installé
dpkg -s libgtkmm-3.0-dev &> /dev/null
if [ $? -ne 0 ]; then
    echo "gtkmm n'est pas installé. Installation en cours..."
    sudo apt-get install libgtkmm-3.0-dev
fi