# CSC494 - Login Instructions

## Machines

- Each group gets 2 types of machines swift-XX and mel-XX.
- swift-XX is the client. this is where you would install the benchmark (YCSB or SparkBench or TPCC+).
- mel-XX is the server. this is where you would install the application. (mysql or Spark or Cassandra or RocksDB)

- login to tomlin.syslab.sandbox
- login to mel-XX.syslab.sandbox
- login to swift-XX.syslab.sandbox (when it is available)

## Disk configuration

Some disk related commands that should be helpful

- lsblk
- lspci
- df -a

## Installing the benchmark/applications

- swift machines (benchmark machines) will have Ubuntu. mel machines (app machines) will have CentOS. If you find an application / benchmark that *needs* a particular OS, please let us know. 

## Applications

### TPCC+ and mysql

Group : Bryan and KC

mel-13

swift-XX

Read about TPC+ and mysql.<br/>
https://github.com/oltpbenchmark/oltpbench<br/>
https://github.com/Percona-Lab/tpcc-mysql<br/>
https://www.percona.com/blog/2010/02/08/introducing-tpce-like-workload-for-mysql/<br/>

Install and run OLTPBench with MySQL on the VM.
Document Instructions to install MySQL.

### Spark + SparkBench

Group : Yuhan and Fukka

mel-14

swift-XX

Install Spark on your VM. Install different workloads that exist for the application. <br/>
https://codait.github.io/spark-bench/workloads/<br/>
Document installation and run instructions.<br/>
Talk about this in class for a few minutes. <br/>

### YCSB + Cassandra/RocksDB

Group : Jialun and Tony

mel-12

swift-XX

Install and run YCSB with Cassandra and/or RocksDB. YCSB contains 6 (or more?) workloads.<br/>

https://github.com/brianfrankcooper/YCSB/tree/master/cassandra<br/>
https://github.com/brianfrankcooper/YCSB/wiki/Core-Workloads<br/>
https://github.com/brianfrankcooper/YCSB/wiki/Running-a-Workload<br/>

Read about Cassandra and/or RocksDB, install and run YCSB and document setup instructions.<br/>
