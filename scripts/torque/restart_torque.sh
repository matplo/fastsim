#!/bin/bash

/etc/init.d/torque-server stop
/etc/init.d/torque-scheduler stop
/etc/init.d/torque-mom stop

/etc/init.d/torque-server start
/etc/init.d/torque-scheduler start
/etc/init.d/torque-mom start
