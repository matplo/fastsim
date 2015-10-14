#!/bin/bash

#from https://jabriffa.wordpress.com/2015/02/11/installing-torquepbs-job-scheduler-on-ubuntu-14-04-lts/

if [[ $1 == "install" ]]; then
	apt-get install torque-server torque-client torque-mom torque-pam
fi

#server=$HOSTNAME.cern.ch
server=localhost.localdomain

if [[ $1 == "create" ]]; then
	/etc/init.d/torque-mom stop
	/etc/init.d/torque-scheduler stop
	/etc/init.d/torque-server stop

	pbs_server -t create

	killall pbs_server

	echo $server > /etc/torque/server_name
	echo $server > /var/spool/torque/server_priv/acl_svr/acl_hosts
	echo root@$server > /var/spool/torque/server_priv/acl_svr/operators
	echo root@$server > /var/spool/torque/server_priv/acl_svr/managers

	echo "$server np=10" > /var/spool/torque/server_priv/nodes
	echo $server > /var/spool/torque/mom_priv/config

	/etc/init.d/torque-server start
	/etc/init.d/torque-scheduler start
	/etc/init.d/torque-mom start
fi

if [[ $1 == "setup" ]]; then
	# set scheduling properties
	qmgr -c 'set server scheduling = true' $server
	qmgr -c 'set server keep_completed = 300' $server
	qmgr -c 'set server mom_job_sync = true' $server
	# was 600
	qmgr -c 'set server scheduler_iteration = 60' $server 
	# create default queue
	qmgr -c 'create queue batch' $server
	qmgr -c 'set queue batch queue_type = execution' $server
	qmgr -c 'set queue batch started = true' $server
	qmgr -c 'set queue batch enabled = true' $server
	qmgr -c 'set queue batch resources_default.walltime = 48:00:00' $server
	qmgr -c 'set queue batch resources_default.nodes = 1' $server
	qmgr -c 'set server default_queue = batch' $server

	# configure submission pool
	qmgr -c 'set server submit_hosts = localhost' $server
	qmgr -c 'set server allow_node_submit = true' $server
	
	#qsub -I

fi

#in /etc/hosts
#127.0.0.1	lbnl3core.cern.ch
#127.0.1.1	localhost
