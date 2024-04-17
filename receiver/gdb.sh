#!/bin/sh
JLinkGDBServer -select USB -device nRF5340_xxAA_APP -endian little -if SWD -speed 8000 -noir -noLocalhostOnly -nologtofile -port 2331 -SWOPort 2328 -TelnetPort 2339
