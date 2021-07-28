#!/bin/bash
FIFO="/tmp/cgminer-fifo"

set -e 

# 2Do: also check for running process...
if [ -e "${FIFO}" ]
then
	echo "# removing exisitng fifo ${FIFO}..."
	rm "${FIFO}"
	echo "# ok"
fi
mkfifo ${FIFO}
exec 3<>${FIFO}
#cgminer -o stratum+tcp://sha256.eu.nicehash.com:3334 -u 3MbhM9BC7XjrwM3hriAizzj2qtnmEydi5p -p x --gekko-compac-freq 150
#cgminer -o stratum+tcp://mmpool.org:3333 -u x_ample -p SHUTUP --gekko-compac-freq 150
#cgminer -o stratum+tcp://stratum.slushpool.com:3333 -u jaysoftdevel -p x --gekko-2pac-freq 200| tee > ${FIFO} &
#cgminer -o stratum+tcp://sha256.eu.nicehash.com:3334 -u 3MbhM9BC7XjrwM3hriAizzj2qtnmEydi5p -p x --gekko-compac-freq 200| tee > ${FIFO} &
cgminer -o stratum+tcp://sha256asicboost.eu.nicehash.com:3368 -u 3MbhM9BC7XjrwM3hriAizzj2qtnmEydi5p -p x --gekko-compac-freq 200| tee > ${FIFO} &
