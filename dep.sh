#!/bin/bash

# Vérifiez si Boost est installé
if ! dpkg-query -W -f='${Status}' libboost-dev 2>/dev/null | grep -q "install ok installed"; then
    echo "Boost n'est pas installé. Installation en cours..."
    sudo apt install -y libboost-dev libboost-test-dev
fi

# Vérifiez si gtkmm est installé
if ! dpkg-query -W -f='${Status}' libgtkmm-3.0-dev 2>/dev/null | grep -q "install ok installed"; then
    echo "gtkmm n'est pas installé. Installation en cours..."
    sudo apt install -y libgtkmm-3.0-dev
fi

# Vérifiez si gcovr est installé
if ! dpkg-query -W -f='${Status}' gcovr 2>/dev/null | grep -q "install ok installed"; then
    echo "gcovr n'est pas installé. Installation en cours..."
    sudo apt install -y gcovr
fi