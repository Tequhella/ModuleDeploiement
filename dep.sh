#!/bin/bash

# Vérifiez si Boost est installé
if ! dpkg-query -W -f='${Status}' libboost-dev 2>/dev/null | grep -q "install ok installed"; then
    echo "Boost n'est pas installé. Installation en cours..."
    sudo apt-get install -y libboost-dev
fi

# Vérifiez si gtkmm est installé
if ! dpkg-query -W -f='${Status}' libgtkmm-3.0-dev 2>/dev/null | grep -q "install ok installed"; then
    echo "gtkmm n'est pas installé. Installation en cours..."
    sudo apt-get install -y libgtkmm-3.0-dev
fi